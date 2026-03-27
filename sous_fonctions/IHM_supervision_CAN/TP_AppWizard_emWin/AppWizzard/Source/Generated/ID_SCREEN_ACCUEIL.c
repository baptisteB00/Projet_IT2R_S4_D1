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
  { WM_OBJECT_LISTBOX_Create,
    ID_LISTBOX_00, ID_SCREEN_ACCUEIL,
    { { { DISPOSE_MODE_REL_PARENT, 76, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 36, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      150, 200, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_00,         APPW_SET_PROP_COLOR,        { ARG_V(GUI_DARKGRAY) } },
  { ID_LISTBOX_00,     APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_WHITE),
                                                     ARG_V(0xff2777b3),
                                                     ARG_V(0xff2777b3) } },
  { ID_LISTBOX_00,     APPW_SET_PROP_COLORS,       { ARG_V(0xff2c2c30),
                                                     ARG_V(GUI_WHITE),
                                                     ARG_V(GUI_WHITE) } },
  { ID_LISTBOX_00,     APPW_SET_PROP_FRAME,        { ARG_V(2) } },
  { ID_LISTBOX_00,     APPW_SET_PROP_COLOR,        { ARG_V(0xff2c2c30) } },
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
  NULL,  0,
  cbID_SCREEN_ACCUEIL,
  0
};

/*************************** End of file ****************************/
