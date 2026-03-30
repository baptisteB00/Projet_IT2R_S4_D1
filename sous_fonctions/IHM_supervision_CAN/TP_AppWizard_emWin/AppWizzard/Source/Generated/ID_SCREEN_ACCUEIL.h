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
File        : ID_SCREEN_ACCUEIL.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef ID_SCREEN_ACCUEIL_H
#define ID_SCREEN_ACCUEIL_H

#include "AppWizard.h"

/*********************************************************************
*
*       Objects
*/
#define ID_BOX_00         (GUI_ID_USER + 1)
#define ID_TEXT_00        (GUI_ID_USER + 2)
#define ID_BUTTON_FEUX    (GUI_ID_USER + 3)
#define ID_BUTTON_PORTE   (GUI_ID_USER + 5)
#define ID_BUTTON_VITESSE (GUI_ID_USER + 4)
#define ID_BUTTON_SON     (GUI_ID_USER + 6)
#define ID_BUTTON_PANNEAU (GUI_ID_USER + 7)

/*********************************************************************
*
*       Slots
*/
void ID_SCREEN_ACCUEIL__ID_BUTTON_00__WM_NOTIFICATION_CLICKED      (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_ACCUEIL__ID_BUTTON_00_Copy1__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_ACCUEIL__ID_BUTTON_00_Copy2__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_ACCUEIL__ID_BUTTON_00_Copy3__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);
void ID_SCREEN_ACCUEIL__ID_BUTTON_VITESS__WM_NOTIFICATION_CLICKED  (APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);

/*********************************************************************
*
*       Callback
*/
void cbID_SCREEN_ACCUEIL(WM_MESSAGE * pMsg);

#endif  // ID_SCREEN_ACCUEIL_H

/*************************** End of file ****************************/
