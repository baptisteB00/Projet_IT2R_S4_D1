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
File        : ID_SCREEN_ACCUEIL.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_ACCUEIL.h"

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
static APPW_CREATE_ITEM _aCreate2[] = {
  { WM_OBJECT_WINDOW_Create,
    ID_SCREEN_ACCUEIL, 0,
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
    ID_BOX_ACCUEIL, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    ID_TEXT_01, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      480, 28, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_NEXT, ID_SCREEN_ACCUEIL,
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
    ID_BUTTON_PREVIOUS_ACCUEIL, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 380, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 222, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_00, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 196, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 207, 0, 0 },
        { DISPOSE_MODE_NULL, 480, 0, 0 },
        { DISPOSE_MODE_NULL, 272, 0, 0 },
      },
      100, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup2[] = {
  { ID_BOX_ACCUEIL,             APPW_SET_PROP_COLOR,        { ARG_V(0xff1d004f) } },
  { ID_BOX_ACCUEIL,             APPW_SET_PROP_UNTOUCHABLE,  { ARG_V(0) } },
  { ID_TEXT_01,                 APPW_SET_PROP_COLOR,        { ARG_V(0xffc0c0c0) } },
  { ID_TEXT_01,                 APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                              ARG_V(0),
                                                              ARG_V(0) } },
  { ID_TEXT_01,                 APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_24_Normal_EXT_AA4) } },
  { ID_TEXT_01,                 APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_0) } },
  { ID_TEXT_01,                 APPW_SET_PROP_UNTOUCHABLE,  { ARG_V(0) } },
  { ID_BUTTON_NEXT,             APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acANALOG_Button_Up_50px50),
                                                              ARG_VP(0, acANALOG_Button_Down_50px50), } },
  { ID_BUTTON_NEXT,             APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                              ARG_V(0xffc0c0c0),
                                                              ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PREVIOUS_ACCUEIL, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acMINIBLUE_Button_Up_101x52),
                                                              ARG_VP(0, acMINIBLUE_Button_Up_101x52), } },
  { ID_BUTTON_PREVIOUS_ACCUEIL, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                              ARG_V(0xffc0c0c0),
                                                              ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PREVIOUS_ACCUEIL, APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_INVALID_COLOR),
                                                              ARG_V(GUI_INVALID_COLOR),
                                                              ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_00,               APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                              ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_00,               APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                              ARG_V(0xffc0c0c0),
                                                              ARG_V(GUI_INVALID_COLOR) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction2[] = {
  { ID_BUTTON_NEXT,             WM_NOTIFICATION_CLICKED,          0,                          APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_00__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_MOTEUR_ACCUEIL),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PREVIOUS_ACCUEIL, WM_NOTIFICATION_CLICKED,          0,                          APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_MOTEUR_ACCUEIL),
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
*       ID_SCREEN_ACCUEIL_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_ACCUEIL_RootInfo = {
  ID_SCREEN_ACCUEIL,
  _aCreate2, GUI_COUNTOF(_aCreate2),
  _aSetup2,  GUI_COUNTOF(_aSetup2),
  _aAction2, GUI_COUNTOF(_aAction2),
  cbID_SCREEN_ACCUEIL,
  0
};

/*************************** End of file ****************************/
