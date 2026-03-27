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
File        : Resource.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include "AppWizard.h"

/*********************************************************************
*
*       Text
*/
#define APPW_MANAGE_TEXT APPW_MANAGE_TEXT_EXT

/*********************************************************************
*
*       Screens
*/
#define ID_SCREEN_ACCUEIL (GUI_ID_USER + 4096)
#define ID_SCREEN_FEUX (GUI_ID_USER + 4097)

extern APPW_ROOT_INFO ID_SCREEN_ACCUEIL_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_FEUX_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_ACCUEIL_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "C:/Etudiants/git/Projet_IT2R_S4_D1/sous_fonctions/IHM_supervision_CAN/TP_AppWizard_emWin/AppWizzard"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
