/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2026  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : ID_SCREEN_PORTE.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef ID_SCREEN_PORTE_H
#define ID_SCREEN_PORTE_H

#include "AppWizard.h"

/*********************************************************************
*
*       Objects
*/
#define ID_BOX_02          (GUI_ID_USER + 1)
#define ID_IMAGE_00        (GUI_ID_USER + 6)
#define ID_TEXT_00         (GUI_ID_USER + 2)
#define ID_BUTTON_NEXT     (GUI_ID_USER + 3)
#define ID_BUTTON_ACCUEIL  (GUI_ID_USER + 4)
#define ID_BUTTON_PREVIOUS (GUI_ID_USER + 5)
#define ID_GAUGE_1AD       (GUI_ID_USER + 9)
#define ID_GAUGE_2AD       (GUI_ID_USER + 10)
#define ID_GAUGE_3AD       (GUI_ID_USER + 12)
#define ID_GAUGE_1AG       (GUI_ID_USER + 8)
#define ID_GAUGE_2AG       (GUI_ID_USER + 11)
#define ID_GAUGE_3AG       (GUI_ID_USER + 13)
#define ID_GAUGE_1DD       (GUI_ID_USER + 14)
#define ID_GAUGE_2DD       (GUI_ID_USER + 15)
#define ID_GAUGE_3DD       (GUI_ID_USER + 16)
#define ID_GAUGE_1DG       (GUI_ID_USER + 17)
#define ID_GAUGE_2DG       (GUI_ID_USER + 18)
#define ID_GAUGE_3DG       (GUI_ID_USER + 19)
#define ID_BUTTON_00       (GUI_ID_USER + 20)

/*********************************************************************
*
*       Slots
*/
void ID_SCREEN_PORTE__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_PORTE__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED    (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_PORTE__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);

/*********************************************************************
*
*       Callback
*/
void cbID_SCREEN_PORTE(WM_MESSAGE * pMsg);

#endif  // ID_SCREEN_PORTE_H

/*************************** End of file ****************************/
