#include <utility.h>
#include <userint.h>
#include <tcpsupp.h>
#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>

#include  "client.h" 
#include "proiect_paint.h"

#define COLOR_ORANGE 1
#define COLOR_PURPLE 2
#define COLOR_GREEN 3  
#define COLOR_BLUE 4
#define COLOR_YELLOW 5 
#define COLOR_RED 6
#define COLOR_BLACK 7 


int mainPanel;

char buffer[512];
int mouseX, mouseY, mouseDown, canvasColor;

int main (int argc, char *argv[])
{

    if(InitCVIRTE(0,argv,0)==0)
	{
		return -1;
	}
	
	mainPanel = LoadPanel(0, "proiect_paint.uir", MAIN_PANEL);
	
	// Set canvas line width
	SetCtrlAttribute (mainPanel, MAIN_PANEL_CANVAS, ATTR_PEN_WIDTH, 4);
	
	// Set canvas line color 
	CanvasColor(COLOR_RED);
	
	DisplayPanel(mainPanel);
	
	int status = ClientConnect("127.0.0.1", 9589);
	
	if(status == 0) {
		MessagePopup ("Test", "Client connected!");
		ClearCanvas();	
	} 
		  				    
	RunUserInterface();
	
	DiscardPanel (mainPanel);
	CloseCVIRTE();
	
    return 0;
}

int TimerStart() {

	return SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 1); 
	
}

int TimerStop() {

	return SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 0);
	
}
   //functia pentru desenare linie

int DrawLine(int x1, int y1, int x2, int y2, int color) {
	
	int tempColor = canvasColor;  //salvez in var temp culoarea initiala
	
	CanvasColor(color);
	
	CanvasSetPenPosition(mainPanel,MAIN_PANEL_CANVAS,MakePoint(x1, y1)); //seta pozitia cursorului
	
	CanvasDrawLineTo(mainPanel, MAIN_PANEL_CANVAS, MakePoint(x2, y2));   //aflam a doua coordonata si deseram
	
	CanvasColor(tempColor);
	
	return 0;
	 
}

int GetPenPosition() {
	
	 return GetRelativeMouseState(mainPanel, MAIN_PANEL_CANVAS, &mouseX, &mouseY, &mouseDown, 0, 0);
	
}

int ClearCanvas() {
	
	 return CanvasClear (mainPanel, MAIN_PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	 
}

int CanvasColor(int constant) {
	
	unsigned color;
	
	switch(constant) {
		
		case COLOR_ORANGE: color = MakeColor(218, 165, 32); break;
		case COLOR_PURPLE: color = MakeColor(147, 112, 219); break;
		case COLOR_GREEN: color = MakeColor(127, 255, 0); break;
		case COLOR_BLUE: color = MakeColor(51, 102, 153); break;
		case COLOR_YELLOW: color = MakeColor(255, 215, 0); break;
		case COLOR_RED: color = MakeColor(178, 34, 34); break;
		case COLOR_BLACK: color = MakeColor(0, 0, 0); break;
		
	}
	
	canvasColor = constant;
	
	return SetCtrlAttribute (mainPanel, MAIN_PANEL_CANVAS, ATTR_PEN_COLOR, color);
	
}


int CVICALLBACK CallbackMain (int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			
			QuitUserInterface(0);
			
			break;
	}
	
	return 0;
}


int CVICALLBACK CallbackCanvas (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_DOUBLE_CLICK:
		case EVENT_LEFT_CLICK:
			
			TimerStart();
			GetPenPosition();
			
			break;
	}
	
	return 0;
}

int CVICALLBACK CallbackTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
		
			if(!mouseDown) {
				TimerStop();
				return 0;								 
			}
				//Salvez pozitiile in variabile temporare
			//pentru trimitere server
			int fromX = mouseX, fromY = mouseY;
			
			GetPenPosition();
			
			if(fromX == mouseX && fromY == mouseY)
				return 0;
			
			//functia care permite desenarea unei linii 
			//pentru simplificarea codului
			DrawLine(fromX, fromY, mouseX, mouseY, canvasColor);
			
			sprintf(buffer, "%d;%d;%d;%d;%d", fromX, fromY, mouseX, mouseY, canvasColor);
			int status = ClientWrite(buffer);
			
			break;		
	}	
			
	
	  	
    return 0;
}


int CVICALLBACK CallbackCanvasClear (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	   switch (event) {
		   
		   case EVENT_COMMIT:
	
				ClearCanvas();
				
				break;
	   }
			
	
	return 0;
}

int CVICALLBACK CallbackColorPurple (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_PURPLE);

			break;
	}
	return 0;
}

int CVICALLBACK CallbackColorGreen (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_GREEN); 

			break;
	}
	return 0;
}

int CVICALLBACK CallbackColorBlack (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_BLACK);  

			break;
	}
	return 0;
}

int CVICALLBACK CallbackColorRed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_RED);

			break;
	}
	return 0;
}

int CVICALLBACK CallbackColorYellow (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_YELLOW); 

			break;
	}
	return 0;
}

int CVICALLBACK CallbackColorBlue (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_BLUE);

			break;
	}
	return 0;
}

int CVICALLBACK CallbackColorOrange (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasColor(COLOR_ORANGE);

			break;
	}
	return 0;
}
