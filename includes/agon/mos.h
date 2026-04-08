#ifndef _AGON_MOS_H
#define _AGON_MOS_H

#include <sys/agon.h>

#define vdp_pflag_cursor        1
#define vdp_pflag_scrchar       2
#define vdp_pflag_point         4
#define vdp_pflag_audio         8
#define vdp_pflag_mode          16
#define vdp_pflag_rtc           32
#define vdp_pflag_mouse			64

#define mos_getkey		_mos_getkey
#define mos_del			_mos_del
#define mos_ren			_mos_ren
#define mos_editline	_mos_editline
#define mos_fopen		_mos_fopen
#define mos_fclose		_mos_fclose
#define mos_feof		_mos_feof
#define mos_oscli		_mos_oscli
#define mos_getfil		_mos_getfil
#define mos_fread		_mos_fread
#define mos_fwrite		_mos_fwrite
#define mos_unpackrtc	_mos_unpackrtc 
#define mos_flseek_p	_mos_flseek_p
#define ffs_ftell		_ffs_ftell
#define ffs_fsize		_ffs_fsize

#endif