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
File        : ID_SCREEN_PORTE.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_PORTE.h"

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
    ID_SCREEN_PORTE, 0,
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
    ID_BOX_02, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_Voiture, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 107, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 97, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      238, 101, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    ID_TEXT_00, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 161, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      159, 32, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_NEXT, ID_SCREEN_PORTE,
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
    ID_BUTTON_ACCUEIL, ID_SCREEN_PORTE,
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
    ID_BUTTON_PREVIOUS, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 330, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 222, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      50, 50, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_1AD, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 168, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 45, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_2AD, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 168, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 45, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_3AD, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 168, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 47, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 30, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_1AG, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 195, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 52, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 85, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 120, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_2AG, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 195, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 52, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 85, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 120, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_3AG, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 190, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 32, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 80, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 120, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_1DD, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, -28, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 198, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 128, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_2DD, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, -28, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 198, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 128, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_3DD, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, -28, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 198, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 128, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_1DG, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 198, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 34, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_2DG, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 198, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 34, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_GAUGE_Create,
    ID_GAUGE_3DG, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 58, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 198, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 34, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_00, ID_SCREEN_PORTE,
    { { { DISPOSE_MODE_REL_PARENT, 206, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 116, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      30, 43, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_02,          APPW_SET_PROP_COLOR,        { ARG_V(GUI_WHITE) } },
  { ID_IMAGE_Voiture,   APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acVoiture_Dessus),
                                                      ARG_V(7805), } },
  { ID_IMAGE_Voiture,   APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(0) } },
  { ID_TEXT_00,         APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_00,         APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(0) } },
  { ID_TEXT_00,         APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_32_Normal_EXT_AA4) } },
  { ID_TEXT_00,         APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_5) } },
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
  { ID_GAUGE_1AD,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_1AD,       APPW_SET_PROP_RANGE,        { ARG_V(2850),
                                                      ARG_V(3450) } },
  { ID_GAUGE_1AD,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_1AD,       APPW_SET_PROP_RADIUS,       { ARG_V(60) } },
  { ID_GAUGE_1AD,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xfff72d09),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_1AD,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_1AD,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_RANGE,        { ARG_V(2850),
                                                      ARG_V(3450) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_RADIUS,       { ARG_V(80) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xffffaa00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_2AD,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_RANGE,        { ARG_V(2850),
                                                      ARG_V(3450) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_RADIUS,       { ARG_V(100) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xff55ff00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_3AD,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_RANGE,        { ARG_V(150),
                                                      ARG_V(750) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_RADIUS,       { ARG_V(60) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(GUI_RED),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_1AG,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_RANGE,        { ARG_V(150),
                                                      ARG_V(750) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_RADIUS,       { ARG_V(80) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xffffaa00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_2AG,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_RANGE,        { ARG_V(150),
                                                      ARG_V(750) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_RADIUS,       { ARG_V(100) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xff55ff00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_3AG,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_RANGE,        { ARG_V(1050),
                                                      ARG_V(1650) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_RADIUS,       { ARG_V(60) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(GUI_RED),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_1DD,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_RANGE,        { ARG_V(1050),
                                                      ARG_V(1650) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_RADIUS,       { ARG_V(80) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xffffaa00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_2DD,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_RANGE,        { ARG_V(1050),
                                                      ARG_V(1650) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_RADIUS,       { ARG_V(100) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xff55ff00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_3DD,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_RANGE,        { ARG_V(1850),
                                                      ARG_V(2450) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_RADIUS,       { ARG_V(60) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(GUI_RED),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_1DG,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_RANGE,        { ARG_V(1850),
                                                      ARG_V(2450) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_RADIUS,       { ARG_V(80) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xffffaa00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_2DG,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_ALIGNBITMAP,  { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                      ARG_V(0),
                                                      ARG_V(4294967286) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_RANGE,        { ARG_V(1850),
                                                      ARG_V(2450) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_SPAN,         { ARG_V(0),
                                                      ARG_V(999) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_RADIUS,       { ARG_V(100) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_COLORS,       { ARG_V(GUI_BLACK),
                                                      ARG_V(0xff55ff00),
                                                      ARG_V(GUI_INVALID_COLOR) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_VALUES,       { ARG_V(16),
                                                      ARG_V(16) } },
  { ID_GAUGE_3DG,       APPW_SET_PROP_VALUE,        { ARG_V(999) } },
  { ID_IMAGE_00,        APPW_SET_PROP_SBITMAP,      { ARG_VP(0, acCadenas_FERME),
                                                      ARG_V(1096), } },
};

/*********************************************************************
*
*       Comparison(s)
*/
static APPW_COND_COMP _aComparison_03[] = {
  { { { 0x00001005, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_04[] = {
  { { { 0x00001005, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

/*********************************************************************
*
*       Condition(s)
*/
static GUI_CONST_STORAGE APPW_COND _Condition_03 = { "A", _aComparison_03, GUI_COUNTOF(_aComparison_03) };
static GUI_CONST_STORAGE APPW_COND _Condition_04 = { "A", _aComparison_04, GUI_COUNTOF(_aComparison_04) };

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_ACCUEIL,  WM_NOTIFICATION_CLICKED,          0,                  APPW_JOB_SHIFTSCREEN,    ID_SCREEN_PORTE__ID_BUTTON_ACCUEIL__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_ACCUEIL),
      ARG_V(APPW_EDGE_TOP),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_NEXT,     WM_NOTIFICATION_CLICKED,          0,                  APPW_JOB_SHIFTSCREEN,    ID_SCREEN_PORTE__ID_BUTTON_NEXT__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_VITESSE),
      ARG_V(APPW_EDGE_LEFT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_BUTTON_PREVIOUS, WM_NOTIFICATION_CLICKED,          0,                  APPW_JOB_SHIFTSCREEN,    ID_SCREEN_PORTE__ID_BUTTON_PREVIOUS__WM_NOTIFICATION_CLICKED,
    { ARG_V(ID_SCREEN_FEUX),
      ARG_V(APPW_EDGE_RIGHT),
      ARG_F((void (*)(void))ANIM_LINEAR),
      ARG_V(500),
      ARG_V(0),
    }, 0, NULL
  },
  { ID_VAR_Cadena,      WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_00,        APPW_JOB_SETBITMAP,      ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP,
    { ARG_V(0),
      ARG_VP(0, acCadenas_FERME),
      ARG_V(1096),
    }, 0, &_Condition_03
  },
  { ID_VAR_Cadena,      WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_00,        APPW_JOB_SETBITMAP,      ID_SCREEN_PORTE__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP_0,
    { ARG_V(0),
      ARG_VP(0, acCadenas_ouvert),
      ARG_V(920),
    }, 0, &_Condition_04
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
*       ID_SCREEN_PORTE_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_PORTE_RootInfo = {
  ID_SCREEN_PORTE,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_PORTE,
  0
};

/*************************** End of file ****************************/
