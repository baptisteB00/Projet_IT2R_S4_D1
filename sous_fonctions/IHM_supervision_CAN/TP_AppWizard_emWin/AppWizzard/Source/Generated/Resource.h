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
extern GUI_CONST_STORAGE unsigned char acUNPRESS_right[];
extern GUI_CONST_STORAGE unsigned char acPRESS_right[];
extern GUI_CONST_STORAGE unsigned char acUNPRESS_home[];
extern GUI_CONST_STORAGE unsigned char acPRESS_home[];
extern GUI_CONST_STORAGE unsigned char acUNPRESS_left[];
extern GUI_CONST_STORAGE unsigned char acPRESS_left[];
extern GUI_CONST_STORAGE unsigned char acsoleil[];
extern GUI_CONST_STORAGE unsigned char acPHARE[];
extern GUI_CONST_STORAGE unsigned char acANALOG_Button_Up_50px50[];
extern GUI_CONST_STORAGE unsigned char acANALOG_Button_Down_50px50[];
extern GUI_CONST_STORAGE unsigned char acVoiture_Dessus[];
extern GUI_CONST_STORAGE unsigned char acCadenas_FERME[];
extern GUI_CONST_STORAGE unsigned char acDARK_Progbar_Tile_V_Blue_16x1[];
extern GUI_CONST_STORAGE unsigned char acDARK_Progbar_Tile_V_Gray_16x1[];
extern GUI_CONST_STORAGE unsigned char acICONE_BATTERIE[];
extern GUI_CONST_STORAGE unsigned char acICONE_HUILE[];
extern GUI_CONST_STORAGE unsigned char acviseur_nunchuk[];
extern GUI_CONST_STORAGE unsigned char acDARK_Switch_Thumb_26x26[];
extern GUI_CONST_STORAGE unsigned char acCadenas_ouvert[];

/*********************************************************************
*
*       Movies
*/
extern GUI_CONST_STORAGE unsigned char acCligno_DROIT_60x60[];
extern GUI_CONST_STORAGE unsigned char acCligno_GAUCHE_60x60[];

/*********************************************************************
*
*       Variables
*/
#define ID_PositionViseurX (GUI_ID_USER + 2048)
#define ID_PositionViseurY (GUI_ID_USER + 2049)
#define ID_Var_ClignoG (GUI_ID_USER + 2050)
#define ID_Var_ClignoD (GUI_ID_USER + 2051)
#define ID_VAR_MODE_LUMIERE (GUI_ID_USER + 2052)
#define ID_VAR_Cadena (GUI_ID_USER + 2053)
#define ID_VAR_Phare (GUI_ID_USER + 2054)
#define ID_VAR_HUILE (GUI_ID_USER + 2055)

/*********************************************************************
*
*       Drawings
*/
#define ID_PointViseur (GUI_ID_USER + 0)

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

extern APPW_ROOT_INFO ID_SCREEN_ACCUEIL_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_FEUX_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_PORTE_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_VITESSE_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_SON_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_ACCUEIL_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "C:/Etudiants/git/Projet_IT2R_S4_D1/sous_fonctions/IHM_supervision_CAN/TP_AppWizard_emWin/AppWizzard"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
