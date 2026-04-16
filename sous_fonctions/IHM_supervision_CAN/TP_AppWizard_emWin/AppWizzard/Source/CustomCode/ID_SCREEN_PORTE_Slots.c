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
File        : ID_SCREEN_PORTE_Slots.c
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_PORTE.h"

/*** Begin of user code area ***/
/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_PORTE
*/
void cbID_SCREEN_PORTE(WM_MESSAGE * pMsg) {
  GUI_USE_PARA(pMsg);
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_PORTE__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_PORTE__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_PORTE__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
 	GUI_USE_PARA(pResult);

}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP_0
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP_0(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	APPW_SetValue(ID_SCREEN_PORTE, ID_GAUGE_1AD, APPW_GetVarData(ID_VAR_1AD, NULL));
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_0
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_0(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	APPW_SetValue(ID_SCREEN_PORTE, ID_GAUGE_1AG, APPW_GetVarData(ID_VAR_1AG, NULL));
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_1
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_1(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	APPW_SetValue(ID_SCREEN_PORTE, ID_GAUGE_2AD, APPW_GetVarData(ID_VAR_2AD, NULL));
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_2
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_2(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	APPW_SetValue(ID_SCREEN_PORTE, ID_GAUGE_2AG, APPW_GetVarData(ID_VAR_2AG, NULL));
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_3
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_3(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	APPW_SetValue(ID_SCREEN_PORTE, ID_GAUGE_3AD, APPW_GetVarData(ID_VAR_3AD, NULL));
}

/*********************************************************************
*
*       ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_4
*/
void ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED_4(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	
	APPW_SetValue(ID_SCREEN_PORTE, ID_GAUGE_3AG, APPW_GetVarData(ID_VAR_3AG, NULL));
	
}

/*************************** End of file ****************************/
