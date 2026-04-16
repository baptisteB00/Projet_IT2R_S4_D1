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
File        : ID_SCREEN_VITESSE.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_VITESSE.h"

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
    ID_SCREEN_VITESSE, 0,
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
    ID_BOX_03, ID_SCREEN_VITESSE,
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
    ID_TEXT_00, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 152, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      177, 32, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_NEXT, ID_SCREEN_VITESSE,
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
    ID_BUTTON_ACCUEIL, ID_SCREEN_VITESSE,
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
    ID_BUTTON_PREVIOUS, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 330, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 222, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_PROGBAR_Create,
    ID_HUILE_JAUGE, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 414, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 64, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 50, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 62, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_01, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 405, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 16, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      40, 25, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_02, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 211, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 50, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 109, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 62, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_03, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 278, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 117, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      26, 26, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_00, ID_SCREEN_VITESSE,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 80, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      200, 100, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_03,          APPW_SET_PROP_COLOR,        { ARG_V(GUI_WHITE) } },
  { ID_TEXT_00,         APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_00,         APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(0) } },
  { ID_TEXT_00,         APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_32_Normal_EXT_AA4) } },
  { ID_TEXT_00,         APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_3) } },
  { ID_TEXT_00,         APPW_SET_PROP_UNTOUCHABLE,  { ARG_V(0) } },
  { ID_BUTTON_NEXT,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acUNPRESS_right),
                                                      ARG_VP(0, acPRESS_right), } },
  { ID_BUTTON_NEXT,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                      ARG_V(0xffc0c0c0),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_ACCUEIL,  APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acUNPRESS_home),
                                                      ARG_VP(0, acPRESS_home), } },
  { ID_BUTTON_ACCUEIL,  APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                      ARG_V(0xffc0c0c0),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PREVIOUS, APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acUNPRESS_left),
                                                      ARG_VP(0, acPRESS_left), } },
  { ID_BUTTON_PREVIOUS, APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                      ARG_V(0xffc0c0c0),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                      ARG_V(100) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_VERTICAL,     { ARG_V(0) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_RADIUS,       { ARG_V(5) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_FRAME,        { ARG_V(2) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_COLOR,        { ARG_V(0xff2c2c30) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acDARK_Progbar_Tile_V_Blue_16x1),
                                                      ARG_VP(0, acDARK_Progbar_Tile_V_Gray_16x1), } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_HUILE_JAUGE,     APPW_SET_PROP_VALUE,        { ARG_V(0) } },
  { ID_IMAGE_01,        APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acICONE_HUILE),
                                                      ARG_V(1568), } },
  { ID_IMAGE_02,        APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acviseur_nunchuk),
                                                      ARG_V(6039), } },
  { ID_IMAGE_02,        APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_02,        APPW_SET_PROP_OPAQUE,       { ARG_V(0) } },
  { ID_IMAGE_03,        APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_03,        APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acDARK_Switch_Thumb_26x26),
                                                      ARG_V(1172), } },
  { ID_GAUGE_00,        APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_00,        APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                      ARG_V(1800) } },
  { ID_GAUGE_00,        APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(100) } },
  { ID_GAUGE_00,        APPW_SET_PROP_RADIUS,       { ARG_V(80) } },
  { ID_GAUGE_00,        APPW_SET_PROP_COLORS,       { ARG_V(0xff2c2c30),
                                                      ARG_V(0xff2777b3),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_00,        APPW_SET_PROP_VALUES,       { ARG_V(19),
                                                      ARG_V(13) } },
  { ID_GAUGE_00,        APPW_SET_PROP_ROUNDEDVAL,   { ARG_V(0) } },
  { ID_GAUGE_00,        APPW_SET_PROP_ROUNDEDEND,   { ARG_V(0) } },
  { ID_GAUGE_00,        APPW_SET_PROP_VALUE,        { ARG_V(1) } },
};

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_ACCUEIL,  WM_NOTIFICATION_CLICKED,          0,                  APPW_JOB_SHIFTSCREEN,    ID_SCREEN_VITESSE__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_ACCUEIL),
      ARG_V(APPW_EDGE_TOP),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_NEXT,     WM_NOTIFICATION_CLICKED,          0,                  APPW_JOB_SHIFTSCREEN,    ID_SCREEN_VITESSE__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_FEUX),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PREVIOUS, WM_NOTIFICATION_CLICKED,          0,                  APPW_JOB_SHIFTSCREEN,    ID_SCREEN_VITESSE__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_PORTE),
      ARG_V(APPW_EDGE_RIGHT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_PositionViseurX, WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_03,        APPW_JOB_SETX0,          ID_SCREEN_VITESSE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_03__APPW_JOB_SETX0,
    { ARG_V(4096),
    }, 65537, NULL
  },
  { ID_PositionViseurY, WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_03,        APPW_JOB_SETY0,          ID_SCREEN_VITESSE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_03__APPW_JOB_SETY0,
    { ARG_V(4097),
    }, 65537, NULL
  },
  { ID_Var_ClignoD,     WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_03,        APPW_JOB_SETX0,          ID_SCREEN_VITESSE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_03__APPW_JOB_SETX0_0,
    { ARG_V(0),
    }, 0, NULL
  },
  { ID_VAR_HUILE,       WM_NOTIFICATION_VALUE_CHANGED,    0,                  APPW_JOB_NULL,           ID_SCREEN_VITESSE__WM_NOTIFICATION_VALUE_CHANGED,
  },
  { ID_VAR_vitesse,     WM_NOTIFICATION_VALUE_CHANGED,    0,                  APPW_JOB_NULL,           ID_SCREEN_VITESSE__WM_NOTIFICATION_VALUE_CHANGED_0,
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
*       ID_SCREEN_VITESSE_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_VITESSE_RootInfo = {
  ID_SCREEN_VITESSE,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_VITESSE,
  0
};

/*************************** End of file ****************************/
