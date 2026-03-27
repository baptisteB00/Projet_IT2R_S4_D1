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
#define ID_RTEXT_0 0
#define ID_RTEXT_1 1
#define ID_RTEXT_2 2
#define ID_RTEXT_3 3
#define ID_RTEXT_4 4
#define ID_RTEXT_5 5

#define APPW_MANAGE_TEXT APPW_MANAGE_TEXT_EXT
extern GUI_CONST_STORAGE unsigned char acAPPW_Language_0[];

/*********************************************************************
*
*       Fonts
*/
extern GUI_CONST_STORAGE unsigned char acRoboto_32_Normal_EXT_AA4[];

/*********************************************************************
*
*       Images
*/
extern GUI_CONST_STORAGE unsigned char acDARK_Button_Up_100x30[];
extern GUI_CONST_STORAGE unsigned char acDARK_Button_Down_100x30[];
extern GUI_CONST_STORAGE unsigned char acANALOG_Button_Up_50px50[];
extern GUI_CONST_STORAGE unsigned char acANALOG_Button_Down_50px50[];
extern GUI_CONST_STORAGE unsigned char acDARK_Angle_Arrow_Down_Gray_24x14[];

/*********************************************************************
*
*       Content
*/
extern GUI_CONST_STORAGE APPW_CONTENT ID_CONTENT_000_Data;

/*********************************************************************
*
*       Screens
*/
#define ID_SCREEN_ACCUEIL (GUI_ID_USER + 4096)
#define ID_SCREEN_FEUX (GUI_ID_USER + 4097)
#define ID_SCREEN_PORTE (GUI_ID_USER + 4098)
#define ID_SCREEN_VITESSE (GUI_ID_USER + 4099)
#define ID_SCREEN_SON (GUI_ID_USER + 4100)
#define ID_SCREEN_PANNEAU (GUI_ID_USER + 4101)

extern APPW_ROOT_INFO ID_SCREEN_ACCUEIL_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_FEUX_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_PORTE_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_VITESSE_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_SON_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_PANNEAU_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_ACCUEIL_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "C:/Etudiants/git/Projet_IT2R_S4_D1/sous_fonctions/IHM_supervision_CAN/TP_AppWizard_emWin/AppWizzard"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
