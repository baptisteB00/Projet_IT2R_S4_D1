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

#define APPW_MANAGE_TEXT APPW_MANAGE_TEXT_EXT
extern GUI_CONST_STORAGE unsigned char acAPPW_Language_0[];

/*********************************************************************
*
*       Fonts
*/
extern GUI_CONST_STORAGE unsigned char acRoboto_24_Normal_EXT_AA4[];

/*********************************************************************
*
*       Images
*/
extern GUI_CONST_STORAGE unsigned char acANALOG_Button_Up_50px50[];
extern GUI_CONST_STORAGE unsigned char acANALOG_Button_Down_50px50[];
extern GUI_CONST_STORAGE unsigned char acMINIBLUE_Button_Up_101x52[];
extern GUI_CONST_STORAGE unsigned char acDARK_Progbar_Tile_V_Blue_16x1[];
extern GUI_CONST_STORAGE unsigned char acDARK_Progbar_Tile_V_Gray_16x1[];
extern GUI_CONST_STORAGE unsigned char acDARK_Button_Up_100x30[];
extern GUI_CONST_STORAGE unsigned char acDARK_Button_Down_100x30[];

/*********************************************************************
*
*       Screens
*/
#define ID_SCREEN_ACCUEIL (GUI_ID_USER + 4096)
#define ID_SCREEN_MOTEUR_ACCUEIL (GUI_ID_USER + 4097)

extern APPW_ROOT_INFO ID_SCREEN_ACCUEIL_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_MOTEUR_ACCUEIL_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_ACCUEIL_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "C:/Etudiants/git/Projet_IT2R_S4_D1/sous_fonctions/IHM_supervision_CAN/TP_AppWizard_emWin/AppWizard"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
