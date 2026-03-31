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
File        : ID_SCREEN_FEUX.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_FEUX.h"

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
    ID_SCREEN_FEUX, 0,
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
    ID_BOX_01, ID_SCREEN_FEUX,
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
    ID_TEXT_00, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 170, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      140, 32, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_NEXT, ID_SCREEN_FEUX,
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
    ID_BUTTON_ACCUEIL, ID_SCREEN_FEUX,
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
    ID_BUTTON_PREVIOUS, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 330, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 222, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_Mode_lumiere, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 416, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 16, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 51, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_MOVIE_Create,
    ID_MOVIE_00, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 120, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 85, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      60, 60, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_MOVIE_Create,
    ID_MOVIE_01, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 51, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 92, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      60, 60, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_Phare, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 228, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 98, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 40, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_clignoG, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 56, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 152, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      55, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_clignoD, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 120, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 152, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      55, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_Phare, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_REL_PARENT, 228, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 152, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      55, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TIMER_Create,
    ID_TIMER_00, ID_SCREEN_FEUX,
    { { { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_01,             APPW_SET_PROP_COLOR,        { ARG_V(GUI_WHITE) } },
  { ID_TEXT_00,            APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_00,            APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                         ARG_V(0),
                                                         ARG_V(0) } },
  { ID_TEXT_00,            APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_32_Normal_EXT_AA4) } },
  { ID_TEXT_00,            APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_2) } },
  { ID_TEXT_00,            APPW_SET_PROP_UNTOUCHABLE,  { ARG_V(0) } },
  { ID_BUTTON_NEXT,        APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acUNPRESS_right),
                                                         ARG_VP(0, acPRESS_right), } },
  { ID_BUTTON_NEXT,        APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                         ARG_V(0xffc0c0c0),
                                                         ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_ACCUEIL,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acUNPRESS_home),
                                                         ARG_VP(0, acPRESS_home), } },
  { ID_BUTTON_ACCUEIL,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                         ARG_V(0xffc0c0c0),
                                                         ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_PREVIOUS,    APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acUNPRESS_left),
                                                         ARG_VP(0, acPRESS_left), } },
  { ID_BUTTON_PREVIOUS,    APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                         ARG_V(0xffc0c0c0),
                                                         ARG_V(GUI_INVALID_COLOR) } },
  { ID_IMAGE_Mode_lumiere, APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_Mode_lumiere, APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acsoleil),
                                                         ARG_V(2536), } },
  { ID_MOVIE_00,           APPW_SET_PROP_MOVIE,        { ARG_VP(0, acCligno_DROIT_60x60),
                                                         ARG_V(14989) } },
  { ID_MOVIE_00,           APPW_SET_PROP_ENDLESS,      { ARG_V(0) } },
  { ID_MOVIE_01,           APPW_SET_PROP_MOVIE,        { ARG_VP(0, acCligno_GAUCHE_60x60),
                                                         ARG_V(14998) } },
  { ID_MOVIE_01,           APPW_SET_PROP_ENDLESS,      { ARG_V(0) } },
  { ID_IMAGE_Phare,        APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acPHARE),
                                                         ARG_V(2614), } },
  { ID_BUTTON_clignoG,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acANALOG_Button_Up_50px50),
                                                         ARG_VP(0, acANALOG_Button_Down_50px50), } },
  { ID_BUTTON_clignoG,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                         ARG_V(0xffc0c0c0),
                                                         ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_clignoD,     APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acANALOG_Button_Up_50px50),
                                                         ARG_VP(0, acANALOG_Button_Down_50px50), } },
  { ID_BUTTON_clignoD,     APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                         ARG_V(0xffc0c0c0),
                                                         ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_Phare,       APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acANALOG_Button_Up_50px50),
                                                         ARG_VP(0, acANALOG_Button_Down_50px50), } },
  { ID_BUTTON_Phare,       APPW_SET_PROP_COLORS,       { ARG_V(0xffc0c0c0),
                                                         ARG_V(0xffc0c0c0),
                                                         ARG_V(GUI_INVALID_COLOR) } },
  { ID_TIMER_00,           APPW_SET_PROP_PERIOD,       { ARG_V(1000) } },
};

/*********************************************************************
*
*       Comparison(s)
*/
static APPW_COND_COMP _aComparison_06[] = {
  { { { 0x00001002, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_07[] = {
  { { { 0x00001002, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_08[] = {
  { { { 0x00001002, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_09[] = {
  { { { 0x00001003, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_0a[] = {
  { { { 0x00001004, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_0b[] = {
  { { { 0x00001004, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_0c[] = {
  { { { 0x00001006, 0, ATOM_VARIABLE, 0 }, { 0x00000002, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_0d[] = {
  { { { 0x00001006, 0, ATOM_VARIABLE, 0 }, { 0x00000002, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsNotEqual },
};

/*********************************************************************
*
*       Condition(s)
*/
static GUI_CONST_STORAGE APPW_COND _Condition_06 = { "A", _aComparison_06, GUI_COUNTOF(_aComparison_06) };
static GUI_CONST_STORAGE APPW_COND _Condition_07 = { "A", _aComparison_07, GUI_COUNTOF(_aComparison_07) };
static GUI_CONST_STORAGE APPW_COND _Condition_08 = { "A", _aComparison_08, GUI_COUNTOF(_aComparison_08) };
static GUI_CONST_STORAGE APPW_COND _Condition_09 = { "A", _aComparison_09, GUI_COUNTOF(_aComparison_09) };
static GUI_CONST_STORAGE APPW_COND _Condition_0a = { "A", _aComparison_0a, GUI_COUNTOF(_aComparison_0a) };
static GUI_CONST_STORAGE APPW_COND _Condition_0b = { "A", _aComparison_0b, GUI_COUNTOF(_aComparison_0b) };
static GUI_CONST_STORAGE APPW_COND _Condition_0c = { "A", _aComparison_0c, GUI_COUNTOF(_aComparison_0c) };
static GUI_CONST_STORAGE APPW_COND _Condition_0d = { "A", _aComparison_0d, GUI_COUNTOF(_aComparison_0d) };

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_ACCUEIL,     WM_NOTIFICATION_CLICKED,          0,                     APPW_JOB_SHIFTSCREEN,    ID_SCREEN_FEUX__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_ACCUEIL),
      ARG_V(APPW_EDGE_TOP),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_NEXT,        WM_NOTIFICATION_CLICKED,          0,                     APPW_JOB_SHIFTSCREEN,    ID_SCREEN_FEUX__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_PORTE),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PREVIOUS,    WM_NOTIFICATION_CLICKED,          0,                     APPW_JOB_SHIFTSCREEN,    ID_SCREEN_FEUX__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_PANNEAU),
      ARG_V(APPW_EDGE_RIGHT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_clignoG,     WM_NOTIFICATION_CLICKED,          ID_MOVIE_01,           APPW_JOB_START,          ID_SCREEN_FEUX__ID_BUTTON_clignoG__WM_NOTIFICATION_CLICKED,
  },
  { ID_BUTTON_clignoD,     WM_NOTIFICATION_CLICKED,          ID_MOVIE_00,           APPW_JOB_START,          ID_SCREEN_FEUX__ID_BUTTON_clignoD__WM_NOTIFICATION_CLICKED,
  },
  { ID_BUTTON_Phare,       WM_NOTIFICATION_CLICKED,          0,                     APPW_JOB_NULL,           ID_SCREEN_FEUX__ID_BUTTON_Phare__WM_NOTIFICATION_CLICKED,
  },
  { ID_Var_ClignoG,        WM_NOTIFICATION_VALUE_CHANGED,    ID_MOVIE_00,           APPW_JOB_START,          ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_MOVIE_00__APPW_JOB_START,
    { 0 }, 65536, &_Condition_06
  },
  { ID_Var_ClignoG,        WM_NOTIFICATION_VALUE_CHANGED,    ID_MOVIE_00,           APPW_JOB_STOP,           ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_MOVIE_00__APPW_JOB_STOP,
    { 0 }, 0, &_Condition_07
  },
  { ID_Var_ClignoD,        WM_NOTIFICATION_VALUE_CHANGED,    ID_MOVIE_01,           APPW_JOB_START,          ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_MOVIE_01__APPW_JOB_START,
    { 0 }, 65536, &_Condition_08
  },
  { ID_Var_ClignoD,        WM_NOTIFICATION_VALUE_CHANGED,    ID_MOVIE_01,           APPW_JOB_STOP,           ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_MOVIE_01__APPW_JOB_STOP,
    { 0 }, 0, &_Condition_09
  },
  { ID_VAR_MODE_LUMIERE,   WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_Mode_lumiere, APPW_JOB_SETBITMAP,      ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_Mode_lumiere__APPW_JOB_SETBITMAP,
    { ARG_V(0),
      ARG_VP(0, acsoleil),
      ARG_V(2536),
    }, 0, &_Condition_0a
  },
  { ID_VAR_MODE_LUMIERE,   WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_Mode_lumiere, APPW_JOB_SETBITMAP,      ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_MOVIE_00__APPW_JOB_SETBITMAP,
    { ARG_V(0),
      ARG_VP(0, aclune),
      ARG_V(4782),
    }, 0, &_Condition_0b
  },
  { ID_VAR_Phare,          WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_Phare,        APPW_JOB_SETBITMAP,      ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_BUTTON_Phare__APPW_JOB_SETBITMAP,
    { ARG_V(0),
      ARG_VP(0, acvide),
      ARG_V(119),
    }, 0, &_Condition_0c
  },
  { ID_VAR_Phare,          WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_Phare,        APPW_JOB_SETBITMAP,      ID_SCREEN_FEUX__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_Phare__APPW_JOB_SETBITMAP,
    { ARG_V(0),
      ARG_VP(0, acPHARE),
      ARG_V(2614),
    }, 0, &_Condition_0d
  },
  { ID_BUTTON_Phare,       WM_NOTIFICATION_CLICKED,          ID_VAR_Phare,          APPW_JOB_ADDVALUE,       ID_SCREEN_FEUX__ID_BUTTON_Phare__WM_NOTIFICATION_CLICKED_0,
    { ARG_V(1),
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
*       ID_SCREEN_FEUX_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_FEUX_RootInfo = {
  ID_SCREEN_FEUX,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_FEUX,
  0
};

/*************************** End of file ****************************/
