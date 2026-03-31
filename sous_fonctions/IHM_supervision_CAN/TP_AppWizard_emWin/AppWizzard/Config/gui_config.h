// gui_config.h - align GUI_CONST_STORAGE on 4 bytes
#ifndef GUI_CONFIG_H
#define GUI_CONFIG_H

#undef GUI_CONST_STORAGE
#define GUI_CONST_STORAGE const __attribute__((aligned(4)))

#endif // GUI_CONFIG_H
