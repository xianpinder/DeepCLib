#ifndef _SYS_AGON_H
#define _SYS_AGON_H

#include <stdint.h>
#include <stddef.h>

struct _SYSVAR_RTCDATA
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

typedef struct _SYSVAR_RTCDATA SYSVAR_RTCDATA;

struct _SYSVAR
{
    uint32_t time;
    uint8_t vdp_pflags;
    uint8_t keyascii;
    uint8_t keymods;
    uint8_t cursorX;
    uint8_t cursorY;
    uint8_t scrchar;
    union
	{
       uint24_t scrpixel;
        struct
		{
            uint8_t scrpixelR;
            uint8_t scrpixelB;
           uint8_t scrpixelG;
        };
    };
    uint8_t audioChannel;
    uint8_t audioSuccess;
    uint16_t scrWidth;
    uint16_t scrHeight;
    uint8_t scrCols;
    uint8_t scrRows;
    uint8_t scrColours;
    uint8_t scrpixelIndex;
    uint8_t vkeycode;
    uint8_t vkeydown;
    uint8_t vkeycount;
    SYSVAR_RTCDATA rtc;
    uint16_t spare;
    uint16_t keydelay;
    uint16_t keyrate;
    uint8_t keyled;
    uint8_t scrMode;
 	uint8_t rtcEnable;
	uint16_t mouseX;
	uint16_t mouseY;
	uint8_t mouseButtons;
	uint8_t mouseWheel;
	uint16_t mouseXDelta;
	uint16_t mouseYDelta;
};

typedef struct _SYSVAR SYSVAR;

extern SYSVAR *_sysvars;

void _vdu (char ch);
void _vdun (unsigned char n, unsigned char ch, ...);
void _vduw (unsigned int val);
void _vdp_write (void *buf, size_t nbytes);
int _ngetenv (const char *name, char *buf, int len);
int _inkey(int code);
const char *_keyname(int code);

/* asmcall interfaces for internal use */
__asmcall void _ac_vdu (int ch);
__asmcall void _ac_vdp_write (void *data, size_t nbytes);

int _mos_getkey (void);
int _mos_del (char *filename);
int _mos_ren (char *src, char *dst);
int _mos_editline (char *buf, int size, int flags);
int _mos_fopen (char *filename, int mode);
int _mos_fclose (int fhandle);
int _mos_feof (int fhandle);
int _mos_oscli (char *command);
void *_mos_getfil (int fhandle);
int _mos_fread (int fhandle, void *buffer, unsigned int nbytes);
int _mos_fwrite (int fhandle, void *buffer, unsigned int nbytes);
void _mos_unpackrtc (void *rtcbuffer, int flags);
int _mos_flseek_p (int fhandle, void *fil);
int _ffs_ftell (void *fil, void *pos);
int _ffs_fsize (void *fil, void *size);

#endif
