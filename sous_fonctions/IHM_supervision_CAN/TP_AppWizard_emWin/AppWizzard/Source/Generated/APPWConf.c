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
File        : APPWConf.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "AppWizard.h"
#include "Resource.h"

#ifdef WIN32
  #include "GUIDRV_Win32R.h"
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define XSIZE_PHYS       480
#define YSIZE_PHYS       272
#define COLOR_CONVERSION GUICC_M8888I
#define DISPLAY_DRIVER   GUIDRV_WIN32R
#define NUM_BUFFERS      2
#define _aScrollerList   NULL
#define _NumScrollers    0

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _apRootList
*/
static APPW_ROOT_INFO * _apRootList[] = {
  &ID_SCREEN_ACCUEIL_RootInfo,
  &ID_SCREEN_FEUX_RootInfo,
  &ID_SCREEN_PORTE_RootInfo,
  &ID_SCREEN_VITESSE_RootInfo,
};

/*********************************************************************
*
*       _NumScreens
*/
static unsigned _NumScreens = GUI_COUNTOF(_apRootList);

/*********************************************************************
*
*       _aVarList
*/
static APPW_VAR_OBJECT _aVarList[] = {
  { ID_PositionViseurX, 0, 270, NULL },
  { ID_PositionViseurY, 0, 130, NULL },
  { ID_Var_ClignoG, 0, 1, NULL },
  { ID_Var_ClignoD, 0, 1, NULL },
  { ID_VAR_MODE_LUMIERE, 0, 0, NULL },
  { ID_VAR_Cadena, 0, 0, NULL },
  { ID_VAR_Phare, 0, 0, NULL },
  { ID_VAR_HUILE, 0, 0, NULL },
  { ID_VAR_vitesse, 0, 0, NULL },
  { ID_VAR_1AD, 0, 0, NULL },
  { ID_VAR_1AG, 0, 0, NULL },
  { ID_VAR_2AD, 0, 0, NULL },
  { ID_VAR_2AG, 0, 0, NULL },
  { ID_VAR_3AD, 0, 0, NULL },
  { ID_VAR_3AG, 0, 0, NULL },
};

/*********************************************************************
*
*       _NumVars
*/
static unsigned _NumVars = GUI_COUNTOF(_aVarList);

/*********************************************************************
*
*       ID_PointViseur
*/
APPW_DRAWING_ITEM_DEF_X(_aID_PointViseur_Item_0, 3) {
  APPW_ID_DRAW_CIRCLE,
  (GUI_CONST_STORAGE APPW_DRAWING_ITEM *)NULL,
  { { 0x00001000, 0, ATOM_VARIABLE, 0 },
    { 0x00001001, 0, ATOM_VARIABLE, 0 },
    { 0x00000014, 0, ATOM_CONSTANT, 0 }
  }
};

/*********************************************************************
*
*       _appDrawing
*/
static GUI_CONST_STORAGE APPW_DRAWING_ITEM * _appDrawing[] = {
  (GUI_CONST_STORAGE APPW_DRAWING_ITEM *)&_aID_PointViseur_Item_0
};

/*********************************************************************
*
*       _NumDrawings
*/
static unsigned _NumDrawings = GUI_COUNTOF(_appDrawing);

/*********************************************************************
*
*       Multibuffering
*/
static U8 _MultibufEnable = 1;

/*********************************************************************
*
*       _ShowMissingCharacters
*/
static U8 _ShowMissingCharacters = 1;

/*********************************************************************
*
*       _apLang
*/
static GUI_CONST_STORAGE char * _apLang[] = {
  (GUI_CONST_STORAGE char *)acAPPW_Language_0,
};

/*********************************************************************
*
*       _TextInit
*/
static GUI_CONST_STORAGE APPW_TEXT_INIT _TextInit = {
  _apLang,
  GUI_COUNTOF(_apLang),
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _InitText
*/
static void _InitText(void) {
  APPW_TextInitMem(&_TextInit);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       APPW_X_Setup
*/
void APPW_X_Setup(void) {
  APPW_SetpfInitText(_InitText);
  APPW_X_FS_Init();
  APPW_MULTIBUF_Enable(_MultibufEnable);
  APPW_SetData(_apRootList, _NumScreens, _aVarList, _NumVars, _aScrollerList, _NumScrollers, (APPW_DRAWING_ITEM **)_appDrawing, _NumDrawings);
  APPW_SetSupportScroller(0);
  GUI_ShowMissingCharacters(_ShowMissingCharacters);
}

/*********************************************************************
*
*       APPW_X_Config
*/
#ifdef WIN32
void APPW_X_Config(void) {
  GUI_MULTIBUF_Config(NUM_BUFFERS);
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);
  }
}
#endif

/*************************** End of file ****************************/
