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
File        : ID_SCREEN_FEUX.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef ID_SCREEN_FEUX_H
#define ID_SCREEN_FEUX_H

#include "AppWizard.h"

/*********************************************************************
*
*       Objects
*/
#define ID_BOX_01          (GUI_ID_USER + 1)
#define ID_TEXT_00         (GUI_ID_USER + 2)
#define ID_BUTTON_NEXT     (GUI_ID_USER + 3)
#define ID_BUTTON_ACCUEIL  (GUI_ID_USER + 4)
#define ID_BUTTON_PREVIOUS (GUI_ID_USER + 5)
#define ID_SWITCH_00       (GUI_ID_USER + 7)
#define ID_SWITCH_01       (GUI_ID_USER + 8)
#define ID_IMAGE_00        (GUI_ID_USER + 9)
#define ID_MOVIE_00        (GUI_ID_USER + 6)
#define ID_MOVIE_01        (GUI_ID_USER + 10)
#define ID_IMAGE_01        (GUI_ID_USER + 11)
#define ID_BUTTON_clignoG  (GUI_ID_USER + 12)
#define ID_BUTTON_clignoD  (GUI_ID_USER + 13)
#define ID_BUTTON_Phare    (GUI_ID_USER + 14)

/*********************************************************************
*
*       Slots
*/
void ID_SCREEN_FEUX__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED                                  (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_FEUX__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED                                     (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_FEUX__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED                                 (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_FEUX__ID_SWITCH_00__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_FEUX__ID_SWITCH_01__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);

/*********************************************************************
*
*       Callback
*/
void cbID_SCREEN_FEUX(WM_MESSAGE * pMsg);

#endif  // ID_SCREEN_FEUX_H

/*************************** End of file ****************************/
