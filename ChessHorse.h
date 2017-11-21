/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2011. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                           1       /* callback function: FUNC_PANEL */
#define  PANEL_TABLE                     2
#define  PANEL_COMMANDBUTTON             3       /* callback function: FUNC_BUTTON */
#define  PANEL_COMMANDBUTTON_2           4       /* callback function: QUIT_BUTTON */
#define  PANEL_NUMERIC_1                 5
#define  PANEL_NUMERIC_2                 6
#define  PANEL_TEXTBOX                   7


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK FUNC_BUTTON(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FUNC_PANEL(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QUIT_BUTTON(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
