/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2012. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MAIN_PANEL                       1       /* callback function: CallbackMain */
#define  MAIN_PANEL_CANVAS                2       /* control type: canvas, callback function: CallbackCanvas */
#define  MAIN_PANEL_CLEAR_CANVAS          3       /* control type: command, callback function: CallbackCanvasClear */
#define  MAIN_PANEL_TIMER                 4       /* control type: timer, callback function: CallbackTimer */
#define  MAIN_PANEL_PICTURE               5       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_COLLOR_PURPLE         6       /* control type: command, callback function: CallbackColorPurple */
#define  MAIN_PANEL_COLOR_GREEN           7       /* control type: command, callback function: CallbackColorGreen */
#define  MAIN_PANEL_COLOR_BLUE            8       /* control type: command, callback function: CallbackColorBlue */
#define  MAIN_PANEL_COLOR_YELLOW          9       /* control type: command, callback function: CallbackColorYellow */
#define  MAIN_PANEL_COLOR_RED             10      /* control type: command, callback function: CallbackColorRed */
#define  MAIN_PANEL_COLOR_BLACK           11      /* control type: command, callback function: CallbackColorBlack */
#define  MAIN_PANEL_COLOR_ORANGE          12      /* control type: command, callback function: CallbackColorOrange */
#define  MAIN_PANEL_COMMANDBUTTON         13      /* control type: command, callback function: CallbackCanvasClear */


     /* Control Arrays: */

#define  CTRLARRAY                        1
#define  CTRLARRAY_2                      2

     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2


     /* Callback Prototypes: */

int  CVICALLBACK CallbackCanvas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackCanvasClear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorBlack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorBlue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorGreen(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorOrange(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorPurple(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorRed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackColorYellow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackMain(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallbackTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
