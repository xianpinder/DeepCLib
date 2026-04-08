#include <agon/mos.h>
#include <curses.h>

int initscr(void)
{
	vdp_vdu_init();
    vdp_mode(3);	//Mode 3 is 80x30
    vdp_clear_screen();
	vdp_get_scr_dims(true);
    vdp_logical_scr_dims(false);

    // Replace obelisk with extended "plus"
    vdp_redefine_character( 0x86,0x18,0x18,0x18,0xFF,0x18,0x18,0x18,0x18);

	// technically in CP1252 the vertical line '|' is unbroken, with the 0xA6 being broken.	//vertical line
	vdp_redefine_character( '|',0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18);

	// should return a pointer to stdscr
	// for now we just have to return something that isn't NULL
	return 1;
}