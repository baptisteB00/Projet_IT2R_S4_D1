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
File        : ID_SCREEN_MOTEUR_ACCUEIL.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_MOTEUR_ACCUEIL.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aCreate
*/
static APPW_CREATE_ITEM _aCreate[] = {
  { WM_OBJECT_WINDOW_Create,
    ID_SCREEN_MOTEUR_ACCUEIL, 0,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BOX_Create,
    ID_BOX_MOTEUR, ID_SCREEN_MOTEUR_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_PROGBAR_Create,
    ID_PROGBAR_VITESSE, ID_SCREEN_MOTEUR_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 23, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 72, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      16, 200, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_PROGBAR_Create,
    ID_PROGBAR_CARBURANT, ID_SCREEN_MOTEUR_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 135, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 72, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      16, 200, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_PROGBAR_Create,
    ID_PROGBAR_, ID_SCREEN_MOTEUR_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 81, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 72, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      16, 200, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_NEXT_MOTEUR, ID_SCREEN_MOTEUR_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 430, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 222, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_PREVIOUS_MOTEUR, ID_SCREEN_MOTEUR_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 380, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 222, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_MOTEUR,             APPW_SET_PROP_COLOR,        { ARG_V(GUI_DARKGRAY) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_VERTICAL,     { ARG_V(0) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_RADIUS,       { ARG_V(5) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_FRAME,        { ARG_V(2) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_COLOR,        { ARG_V(0xff2c2c30) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_VALUE,        { ARG_V(40) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Progbar_Tile_V_Blue_16x1),
                                                             ARG_VP(0, acDARK_Progbar_Tile_V_Gray_16x1), } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                             ARG_V(100) } },
  { ID_PROGBAR_VITESSE,        APPW_SET_PROP_COLORS,       { ARG_V(0xff681dff),
                                                             ARG_V(0xffff2b6e),
                                                             ARG_V(GUI_INVALID_COLOR) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_VERTICAL,     { ARG_V(0) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_RADIUS,       { ARG_V(5) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_FRAME,        { ARG_V(2) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_COLOR,        { ARG_V(0xff2c2c30) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_VALUE,        { ARG_V(40) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Progbar_Tile_V_Blue_16x1),
                                                             ARG_VP(0, acDARK_Progbar_Tile_V_Gray_16x1), } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                             ARG_V(100) } },
  { ID_PROGBAR_CARBURANT,      APPW_SET_PROP_COLORS,       { ARG_V(0xff681dff),
                                                             ARG_V(0xffff2b6e),
                                                             ARG_V(GUI_INVALID_COLOR) } },
  { ID_PROGBAR_,               APPW_SET_PROP_VERTICAL,     { ARG_V(0) } },
  { ID_PROGBAR_,               APPW_SET_PROP_RADIUS,       { ARG_V(5) } },
  { ID_PROGBAR_,               APPW_SET_PROP_FRAME,        { ARG_V(2) } },
  { ID_PROGBAR_,               APPW_SET_PROP_COLOR,        { ARG_V(0xff2c2c30) } },
  { ID_PROGBAR_,               APPW_SET_PROP_VALUE,        { ARG_V(40) } },
  { ID_PROGBAR_,               APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Progbar_Tile_V_Blue_16x1),
                                                             ARG_VP(0, acDARK_Progbar_Tile_V_Gray_16x1), } },
  { ID_PROGBAR_,               APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_PROGBAR_,               APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                             ARG_V(100) } },
  { ID_PROGBAR_,               APPW_SET_PROP_COLORS,       { ARG_V(0xff681dff),
                                                             ARG_V(0xffff2b6e),
                                                             ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_NEXT_MOTEUR,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acANALOG_Button_Up_50px50),
                                                             ARG_VP(0, acANALOG_Button_Down_50px50), } },
  { ID_BUTTON_NEXT_MOTEUR,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                             ARG_V(0xffc0c0c0),
                                                             ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PREVIOUS_MOTEUR, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acANALOG_Button_Up_50px50),
                                                             ARG_VP(0, acANALOG_Button_Down_50px50), } },
  { ID_BUTTON_PREVIOUS_MOTEUR, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                             ARG_V(0xffc0c0c0),
                                                             ARG_V(GUI_INVALID_COLOR) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_NEXT_MOTEUR,     WM_NOTIFICATION_CLICKED,          0,                         APPW_JOB_SHIFTSCREEN,    ID_SCREEN_MOTEUR__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_ACCUEIL),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PREVIOUS_MOTEUR, WM_NOTIFICATION_CLICKED,          0,                         APPW_JOB_SHIFTSCREEN,    ID_SCREEN_MOTEUR__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_ACCUEIL),
      ARG_V(APPW_EDGE_RIGHT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
};

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       ID_SCREEN_MOTEUR_ACCUEIL_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_MOTEUR_ACCUEIL_RootInfo = {
  ID_SCREEN_MOTEUR_ACCUEIL,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_MOTEUR_ACCUEIL,
  0
};

/*************************** End of file ****************************/
