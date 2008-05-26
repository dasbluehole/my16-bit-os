/*
GazOS Operating System
Copyright (C) 1999  Gareth Owen <gaz@athene.co.uk>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef INCLUDE_VIDEO
#define INCLUDE_VIDEO

#define KBD_NOMODIFIER   0
#define KBD_SHIFT        1
#define KBD_LEFTSHIFT    2
#define KBD_RIGHTSHIFT   4
#define KBD_CTRL         8
#define KBD_LEFTCTRL    16
#define KBD_RIGHTCTRL   32
#define KBD_ALT         64
#define KBD_ALTGR      128

#define NR_ROWS 	25
#define NR_LINES 	NR_ROWS
#define NR_COLUMNS 	80

extern unsigned char far *VIDEO_MEMORY=(char far *)( (void _seg * )( 0xb000 ) +( void near * )( 0x8000 ));
#define video VIDEO_MEMORY
void kprint(char *string);
void cls();
void printlong(unsigned long i);
char readkey();
int get_x_pos();
int get_y_pos();
void put_cursor(char row,char column);
void printat(char row,char column,char *sring);
void gotoxy(int x, int y);
void sound(int freq);
void beep(void);
int printk(const char *fmt, ...);

#endif

