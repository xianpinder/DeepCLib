#include <sys/agon.h>
#include <conio.h>

struct text_info _conio_info;

void _textmode(int mode)
{
	int w,h;
	
	if (mode == 255)
		mode = _conio_info.currmode;

	_ac_vdu_mode (mode);
	
	_conio_info.screenwidth = _sysvars->scrCols;
	_conio_info.screenheight = _sysvars->scrRows;
	_conio_info.currmode = _sysvars->scrMode;
	_conio_info.curx = 1;
	_conio_info.cury = 1;
	_conio_info.winleft = 1;
    _conio_info.wintop = 1;
    _conio_info.winright = _conio_info.screenwidth;
    _conio_info.winbottom = _conio_info.screenheight;
	_conio_info.attribute = _sysvars->scrColours;
	_conio_info.normattr = _sysvars->scrColours;	
}