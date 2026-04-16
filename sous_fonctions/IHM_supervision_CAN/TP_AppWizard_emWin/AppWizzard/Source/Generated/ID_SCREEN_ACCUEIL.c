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
static APPW_CREATE_ITEM _aCreate[] = {
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
    ID_BOX_00, ID_SCREEN_ACCUEIL,
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
    ID_TEXT_00, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 148, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      184, 32, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_FEUX, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 190, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 56, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      100, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_PORTE, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 183, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 121, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      115, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_VITESSE, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 190, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 183, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      100, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_SON, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 577, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 175, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      100, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_PANNEAU, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 577, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 242, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
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
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_00,         APPW_SET_PROP_COLOR,        { ARG_V(GUI_WHITE) } },
  { ID_TEXT_00,        APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_00,        APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                     ARG_V(0),
                                                     ARG_V(0) } },
  { ID_TEXT_00,        APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_32_Normal_EXT_AA4) } },
  { ID_TEXT_00,        APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_1) } },
  { ID_TEXT_00,        APPW_SET_PROP_UNTOUCHABLE,  { ARG_V(0) } },
  { ID_BUTTON_FEUX,    APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                     ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_FEUX,    APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                     ARG_V(GUI_BLACK),
                                                     ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_FEUX,    APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_2) } },
  { ID_BUTTON_PORTE,   APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                     ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_PORTE,   APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                     ARG_V(GUI_BLACK),
                                                     ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PORTE,   APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_5) } },
  { ID_BUTTON_VITESSE, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                     ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_VITESSE, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                     ARG_V(GUI_BLACK),
                                                     ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_VITESSE, APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_3) } },
  { ID_BUTTON_SON,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                     ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_SON,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                     ARG_V(GUI_BLACK),
                                                     ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_SON,     APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_0) } },
  { ID_BUTTON_PANNEAU, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Button_Up_100x30),
                                                     ARG_VP(0, acDARK_Button_Down_100x30), } },
  { ID_BUTTON_PANNEAU, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                     ARG_V(GUI_BLACK),
                                                     ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PANNEAU, APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_4) } },
  { ID_BUTTON_PANNEAU, APPW_SET_PROP_COLOR,        { ARG_V(GUI_WHITE) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_FEUX,    WM_NOTIFICATION_CLICKED,          0,                 APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_00__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_FEUX),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PORTE,   WM_NOTIFICATION_CLICKED,          0,                 APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_00_Copy1__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_PORTE),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_VITESSE, WM_NOTIFICATION_CLICKED,          0,                 APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_00_Copy2__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_VITESSE),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_SON,     WM_NOTIFICATION_CLICKED,          0,                 APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_00_Copy3__WM_NOTIFICATION_CLICKED,
    { ARG_V(0),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PANNEAU, WM_NOTIFICATION_CLICKED,          0,                 APPW_JOB_SHIFTSCREEN,    ID_SCREEN_ACCUEIL__ID_BUTTON_VITESS__WM_NOTIFICATION_CLICKED,
    { ARG_V(0),
      ARG_V(APPW_EDGE_LEFT),
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
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_ACCUEIL,
  0
};

/*************************** End of file ****************************/
