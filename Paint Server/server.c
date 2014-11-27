#include <userint.h>
#include <tcpsupp.h>
#include <ansi_c.h>
#include <utility.h>
#include <toolbox.h>

#include "proiect_paint.h"


#define TCP_MAX_BYTES 512
#define TCP_TIMEOUT 15000

int CVICALLBACK CallbackServer(unsigned handle, int event, int error, void *callbackData);
static int CVICALLBACK CompareClientInfoPtr (void *item1, void *item2);

int port = 9589;

static ListType clientList = 0;

int clientsNumber = 0;
int mainPanel;

char buffer[256];

typedef struct Client
{
    unsigned int handle;      
    char name[256];
	char address[256];
	char bufferIn[512];
	int fromX, fromY, toX, toY,color;
} Client, *ClientInfoPtr;


int main (int argc, char *argv[])
{
    
    
    if (InitCVIRTE(0, argv, 0) == 0)
        return -1;
	
	
	mainPanel = LoadPanel (0, "proiect_paint.uir", PANEL);
	
	
	DisplayPanel(mainPanel);
	
    clientList = ListCreate (sizeof (ClientInfoPtr));
    
	ServerStart();
    
    RunUserInterface ();


    return 0;
}


int Log(char buffer[256]) {

	return InsertTextBoxLine(mainPanel, PANEL_TEXTBOX, 0, buffer);
	
}

int ServerStart() {
				
	return RegisterTCPServer(port, CallbackServer, NULL);
	
}

int ServerStop() {
	
	return UnregisterTCPServer(port);
	
}

int ClientSend(unsigned clientHandle, char buffer[TCP_MAX_BYTES]) {
	
	return ServerTCPWrite(clientHandle, buffer, strlen(buffer)+1, TCP_TIMEOUT);
	 	
}

int ClientRead(Client *client) {
	
   return ServerTCPRead(client->handle, client->bufferIn, TCP_MAX_BYTES, TCP_TIMEOUT);  
	
}

int ParseClientString(Client *client) {
	
	return sscanf(client->bufferIn, "%d;%d;%d;%d;%d", &client->fromX, &client->fromY, &client->toX, &client->toY, &client->color);
		
}

int ClientSendToAll(char buffer[TCP_MAX_BYTES], unsigned int clientHandle) {	

Client *client;
	
	for(int index = 1; index <= clientsNumber; index++) {
	
		ListGetItem (clientList, &client, index);  
		
		if(client->handle != clientHandle)
			ClientSend(client->handle, buffer);
	}
	
	return 0;
	
}
//****************************************************Copiat de la exemplu tcp*********************************

Client* ClientReturn(unsigned clientHandle) {

	Client clientInfo = {0};
    ClientInfoPtr clientInfoPtr = &clientInfo;
    size_t index; //facem o variabila de tip size_t
    
	clientInfoPtr->handle = clientHandle;
	index = ListFindItem (clientList, &clientInfoPtr, FRONT_OF_LIST, CompareClientInfoPtr);
    
	if (index > 0) {
        
		ListGetItem (clientList, &clientInfoPtr, index);
		
		return clientInfoPtr;
		
	
	}
	
	return clientInfoPtr;
	
}

//****************************************************************************************************************
static int ClientRegister(unsigned int handle)
{
    
	ClientInfoPtr clientInfoPtr = 0; 
    clientInfoPtr = calloc (1, sizeof (Client)); //Creem o structura de tip client info PTR
	
    if (clientInfoPtr == NULL)
        return -1;
	
    clientInfoPtr->handle = handle;// inregistrez conexiunea ca sa pot sti cu ce client comunic
    
    GetTCPPeerName(handle, clientInfoPtr->name, 256);
    GetTCPPeerAddr(handle, clientInfoPtr->address, 256); //inregistrez nume si adresa
	
	clientsNumber++; //incrementez ca sa numar cati clienti se conecteaza
	
	sprintf(buffer, "Client #%d connected! His name is %s and his adress is %s", clientsNumber, clientInfoPtr->name, clientInfoPtr->address);
	Log(buffer);  //Scriem in fereastra de texbox de la server
    
    return ListInsertItem (clientList, &clientInfoPtr, END_OF_LIST);  //plasez in lista mea de clienti structura creata
	
}


int CVICALLBACK CallbackServer(unsigned handle, int event, int error, void *callbackData)
{

    switch (event) {
		
        case TCP_CONNECT:
			
			ClientRegister(handle);
			
            break;
			
        case TCP_DATAREADY:
			
			Client *client = ClientReturn(handle); //verific are dintre clienti a trimis ceva
			
			ClientRead(client); //citesc datele care vin de la client
			
			ParseClientString(client);  //decodam ceea ce ne-a venit pentru a intelege datele trimise
			
			sprintf(buffer, "%s drew a %d line from: X: %d, Y: %d to X: %d, Y: %d.", client->name, client->color, client->fromX, client->fromY, client->toX, client->toY);
			
			Log(buffer);  //pentru a scrie in textbox
			
		 ClientSendToAll(client->bufferIn, client->handle);
 //Client Send To all trimite modificarile la titi clientii
			
            break;
			
        case TCP_DISCONNECT:
			
            ServerStop();
			
            break;
    }
	
    return 0;
	
}

static int CVICALLBACK CompareClientInfoPtr (void *item1, void *item2)	   //-1 se alege primul element...daca 1 se alege al 2-lea
{
    return ((*(ClientInfoPtr *) item1)->handle - (*(ClientInfoPtr *) item2)->handle);
}


