#include <cvirte.h>
#include <stdio.h>
#include <stdlib.h>
#include <tcpsupp.h>
#include <string.h>
#include <utility.h>
#include <userint.h>

#define TCP_MAX_BYTES 500
#define TCP_TIMEOUT 15000
#define TCP_DEFAULT_ADRESS 127.0.0.1
#define TCP_DEFAULT_PORT 9589

int CVICALLBACK CallbackClient(unsigned handle, int event, int error, void *callbackData);

unsigned handleClient;

char clientBufferIn[TCP_MAX_BYTES];
int x1, x2, y1, y2, color;


int ClientConnect(char adress[256], int port) {
	
	int timeout = TCP_TIMEOUT;
	
	if(adress != "127.0.0.1" && adress != "localhost")
		timeout = 5000;

	return ConnectToTCPServer (&handleClient, port, adress, CallbackClient, NULL, timeout);
	
}

int ClientWrite(char buffer[TCP_MAX_BYTES]) {
	
	return ClientTCPWrite(handleClient, buffer, strlen(buffer) + 1, TCP_TIMEOUT);
		
}

int ClientRead() {
	
	return ClientTCPRead(handleClient, clientBufferIn, TCP_MAX_BYTES, TCP_TIMEOUT);
	
}


int CVICALLBACK CallbackClient(unsigned handle, int event, int error, void *callbackData) {

    switch (event) {
		
        case TCP_DATAREADY:
			
			ClientRead();
			
			sscanf(clientBufferIn, "%d;%d;%d;%d;%d", &x1, &y1, &x2, &y2, &color);
			
			DrawLine(x1, y1, x2, y2, color);
			
            break;
			
        case TCP_DISCONNECT:
           
			
            break;
    }
	
    return 0;
}
