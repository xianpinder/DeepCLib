#ifndef _AGON_VDP_H
#define _AGON_VDP_H
#include <stdint.h>
#include <stdbool.h>
#include <agon/mos.h>

void vdp_clear_screen (void);
void vdp_cursor_behaviour (int setting, int mask);
void vdp_cursor_enable (int flag);
void vdp_cursor_tab (int x, int y);
void vdp_define_colour(int l, int p, int r, int g, int b);
void vdp_get_scr_dims (bool wait);
void vdp_load_bitmap (int w, int h, void *bitmap);
void vdp_logical_scr_dims (int is_on);
int vdp_mode (int mode);
void vdp_point (int x, int y);
void vdp_redefine_character (int ch, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8);
void vdp_reset_system_font (void);
void vdp_select_bitmap (int n);
void vdp_set_graphics_colour (int mode, int colour);
void vdp_set_text_colour (int c);
SYSVAR *vdp_vdu_init (void);

#endif