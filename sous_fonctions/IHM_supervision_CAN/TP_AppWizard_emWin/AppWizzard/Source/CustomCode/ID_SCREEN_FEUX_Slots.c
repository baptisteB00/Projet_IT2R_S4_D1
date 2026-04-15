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
File        : ID_SCREEN_FEUX_Slots.c
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_FEUX.h"

/*** Begin of user code area ***/

#include "stm32f7xx.h"                  // Device header
#include "AppWizard.h"
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f7xx_hal.h"              // Device:STM32Cube HAL:Common
#include "Driver_CAN.h"                 // CMSIS Driver:CAN


#include "GUI.h"                        // Graphics:CORE


#include "Resource.h"

#include "stdio.h"
#include "Board_LED.h" 
extern   ARM_DRIVER_CAN        Driver_CAN1;
extern int Init_GUIThread (void);
#define ID_CAN_RADAR 0x010
#define ID_CAN_lidar 0x011
#define ID_CAN_Panneau 0x012
#define ID_CAN_Nunchuk 0x020
#define ID_CAN_Vmoteur 0x021
#define ID_CAN_Phare 0x030
#define ID_CAN_GestionPORTE 0x031
#define ID_CAN_SonDFP 0x032
#define ID_CAN_Capteur 0x033
#define ID_CAN_GPS 0x034

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_FEUX
*/
void cbID_SCREEN_FEUX(WM_MESSAGE * pMsg) {
  GUI_USE_PARA(pMsg);
}

/*********************************************************************
*
*       ID_SCREEN_FEUX__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_FEUX__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_FEUX__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_FEUX__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_FEUX__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_FEUX__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
}

/*********************************************************************
*
*       ID_SCREEN_FEUX__ID_BUTTON_clignoD__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_FEUX__ID_BUTTON_clignoD__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	ARM_CAN_MSG_INFO tx_msg_info;
    uint8_t data_buf[1];

    // Configuration de la trame (ID 0x30)
    tx_msg_info.id  = ARM_CAN_STANDARD_ID(ID_CAN_Phare); 
    tx_msg_info.rtr = 0;
    tx_msg_info.dlc = 1;


        // On récupère l'état de la variable liée au bouton
        // Note : On utilise ID_VAR_Phare car c'est elle qui stocke la valeur (0 ou 1)
        int etat = APPW_GetValue(ID_SCREEN_FEUX, ID_BUTTON_clignoD, 0);

        if (etat == 1) {
            data_buf[0] = 0x01; // Allumé
        } else {
            data_buf[0] = 0x00; // Éteint
        }

        // Envoi sur le bus
        Driver_CAN1.MessageSend(2, &tx_msg_info, data_buf, 1);
}

/*********************************************************************
*
*       ID_SCREEN_FEUX__ID_BUTTON_clignoG__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_FEUX__ID_BUTTON_clignoG__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	ARM_CAN_MSG_INFO tx_msg_info;
    uint8_t data_buf[1];

    // Configuration de la trame (ID 0x30)
    tx_msg_info.id  = ARM_CAN_STANDARD_ID(ID_CAN_Phare); 
    tx_msg_info.rtr = 0;
    tx_msg_info.dlc = 1;


        // On récupère l'état de la variable liée au bouton
        // Note : On utilise ID_VAR_Phare car c'est elle qui stocke la valeur (0 ou 1)
        int etat = APPW_GetValue(ID_SCREEN_FEUX, ID_BUTTON_clignoG, 0);

        if (etat == 1) {
            data_buf[0] = 0x02; // Allumé
        } else {
            data_buf[0] = 0x00; // Éteint
        }

        // Envoi sur le bus
        Driver_CAN1.MessageSend(2, &tx_msg_info, data_buf, 1);
}

/*********************************************************************
*
*       ID_SCREEN_FEUX__ID_BUTTON_Phare__WM_NOTIFICATION_CLICKED
*/
void ID_SCREEN_FEUX__ID_BUTTON_Phare__WM_NOTIFICATION_CLICKED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  GUI_USE_PARA(pAction);
  GUI_USE_PARA(hScreen);
  GUI_USE_PARA(pMsg);
  GUI_USE_PARA(pResult);
	ARM_CAN_MSG_INFO tx_msg_info;
    uint8_t data_buf[1];

    // Configuration de la trame (ID 0x30)
    tx_msg_info.id  = ARM_CAN_STANDARD_ID(ID_CAN_Phare); 
    tx_msg_info.rtr = 0;
    tx_msg_info.dlc = 1;


        // On récupère l'état de la variable liée au bouton
        // Note : On utilise ID_VAR_Phare car c'est elle qui stocke la valeur (0 ou 1)
        int etat = APPW_GetValue(ID_SCREEN_FEUX, ID_BUTTON_Phare, 0);

        if (etat == 1) {
            data_buf[0] = 0x04; // Allumé
        } else {
            data_buf[0] = 0x00; // Éteint
        }

        // Envoi sur le bus
        Driver_CAN1.MessageSend(2, &tx_msg_info, data_buf, 1);
}

/*************************** End of file ****************************/
