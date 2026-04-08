#include <agon/mos.h>
#include <curses.h>

/* The start_color() function must be called in order to enable use of colours and before any colour manipulation function is called.
 * The function initialises eight basic colours (black, blue, green, cyan, red, magenta, yellow, and white) that can be specified by
 * the colour macros (such as COLOR_BLACK) defined in <curses.h>.
 */
 
/*
 * The function also initialises two global external variables:
 *
 * COLORS defines the number of colours that the terminal supports.
 * If COLORS is 0, the terminal does not support redefinition of colours (and can_change_color() will return FALSE).
 * 
 * COLOR_PAIRS defines the maximum number of colour-pairs that the terminal supports.
 */

/* The start_color() function also restores the colours on the terminal to terminal-specific initial values.
 * The initial background colour is assumed to be black for all terminals.
 */

int	start_color(void)
{
	//COLORS = 16;
	//COLOR_PAIRS = 31;

	vdp_set_text_colour( COLOR_WHITE );
	vdp_set_text_colour( COLOR_BLACK + COLOR_BG);

	return OK;
}
