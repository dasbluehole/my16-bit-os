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

#include "video.h"
#include "pio.h"
#include "stdarg.h"
#include "flags.h"

#define byte unsigned char
#define ushort unsigned short
#define ulong unsigned long
//#define video VIDEO_MEMORY
static byte attr = 7;		/* attribute of the text */
long pos;

int c_x=0, c_y=0;

#define CRTC_COMMAND	0x3D4
#define CRTC_DATA	0x3D5
#define CRTC_CURLO	0x0F
#define CRTC_CURHI	0x0E




void kprint(char *string)		/* Print text to the screen	*/
{
   unsigned int curchar, vidmem_off, i;
//   VIDEO_MEMORY=(char far *)( (void _seg * )( 0xb000 ) +( void near * )( 0x8000 ));
   outportb(0x3d4, 0x0e);		/* Get cursor Y position	*/
   vidmem_off = inportb(0x3d5);
   vidmem_off <<= 8;
   outportb(0x3d4, 0x0f);		/* And add cursor X position	*/
   vidmem_off += inportb(0x3d5);
   vidmem_off <<= 1;

   while((curchar=*string++))		/* Loop through the string	*/
   {
      switch(curchar)			/* Is it a special character ?  */
      {
         case '\n':			/* Newline found		*/
	    vidmem_off = (vidmem_off/160)*160 + 160;
            break;

         case '\r':			/* Carriage return found	*/
            vidmem_off = (vidmem_off/160)*160;
	    break;

	case '\t':
	    vidmem_off += 8;
	    break;
	 
	case 8:/* Delete */
	    vidmem_off-=2;
	    VIDEO_MEMORY[vidmem_off] = 0x20;
	    break;

         default:			/* Normal character             */
            VIDEO_MEMORY[vidmem_off++] = curchar;
	    VIDEO_MEMORY[vidmem_off++] = 0x07;
            break;
      }

      if(vidmem_off >= 160*25)		/* Are we off-screen ?		*/
      {
         for(i = 0; i < 160*24; i++)	/* Scroll the screen up		*/
         {
	    VIDEO_MEMORY[i] = VIDEO_MEMORY[i+160];
         }
         for(i = 0; i < 80; i++)	/* Empty the bottom row		*/
         {
            VIDEO_MEMORY[(160*24)+(i*2)] = 0x20;
	    VIDEO_MEMORY[(160*24)+(i*2)+1] = 0x07;
         }
         vidmem_off -= 160;		/* We're on the bottom row	*/
      }
   }

   vidmem_off >>= 1;			/* Set the new cursor position  */
   outportb(0x3d4, 0x0f);
   outportb(0x3d5, vidmem_off & 0x0ff);
   outportw(0x3d4, 0x0e);
   outportb(0x3d5, vidmem_off >> 8);
}

void cls(void)				/* Clear the screen		*/
{
   unsigned int i;

   for(i = 0; i < (80*25); i++)         /* Fill the screen with         */
   {					/* background color		*/
      VIDEO_MEMORY[i*2] = 0x20;
      VIDEO_MEMORY[i*2+1] = 0x07;
   }

   outportb(0x3d4, 0x0f);		/* Set the cursor to the	*/
   outportb(0x3d5, 0);			/* upper-left corner of the	*/
   outportw(0x3d4, 0x0e);		/* screen			*/
   outportb(0x3d5, 0);
}

void printlong(unsigned long i)  /* Convert a dword to a string  */
{
   unsigned char backstr[11], j=0, l=0, m=0;
   unsigned char str[255];

   do					/* Convert string one digit at	*/
   {					/* a time			*/
      backstr[j++] = (i % 10) + '0';	/* Put a digit in backstr	*/
      i /= 10;				/* Next digit			*/
   }					/* And continue until there are */
   while(i);				/* no more digits left		*/

   backstr[j] = '\0';			/* End of the string		*/

   for(l=j-1; m<j; l--)			/* Backstr is backwards (last   */
   {					/* digit first.)  Now we flip   */
      str[m++] = backstr[l];		/* it around...			*/
   }					/* ... and it's ready !!!	*/

   str[j] = '\0';			/* Put the string end on it	*/

   kprint(str);
}

/*Modification by Ashok Shankar Das*/
/*Reads a character from the keyboard and returns it*/
char readkey()
{
/*implement it here*/
	char c;
	asm{
		mov ah,00;
		int 0x16;
		mov c,al;
	}
	return (c);
}
//reads the cursor x position on current page, page 0 assumed???
//returns row number
int get_x_pos()
{
/*implement it here*/
	char x;
	asm{
		mov ah,03;
		mov bh,0;
		int 0x10;
		mov x,dh;
	}
	return (x);
}
//reads the cursor y position on current page, page 0 assumed???
//returns column number

int get_y_pos()
{
/*implement it here*/
	char y;
	asm{
		mov ah,03;
		mov bh,0;
		int 0x10;
		mov y,dl;
	}
	return(y);
}
//sets the cursor position on current page, page 0 assumed???
//takes row and column

void put_cursor(char row,char column)
{
/*implement it here*/
	asm{
		mov ah,02;
		mov bh,0;
		mov dh,row;
		mov dl,column;
		int 0x10;
	}
}
void printat(char row,char column, char *string)
{
/* Implement it here*/
	put_cursor(row,column);
	kprint(string);
}
/*from little os*/
void gotoxy(int x, int y)
{
	c_x = x;
        c_y = y;

	pos = c_y * NR_COLUMNS + c_x;

        outportb(CRTC_COMMAND, CRTC_CURLO);
        outportb(CRTC_DATA, (unsigned char) pos);

        outportb(CRTC_COMMAND, CRTC_CURHI);
        pos >>= 8;
        outportb(CRTC_DATA, (unsigned char) pos);
}

int sound_delay = 0;

void sound(int freq)
{
	if (freq>0) {	/* activate speaker */
                outportb(0x42, (unsigned char) freq);
                outportb(0x42, (unsigned char) (freq >> 8));
                outportb(0x61, inportb(0x61) | 3);
        }
        else
        {	/* stop speaker */
        	outportb(0x61, inportb(0x61) & !3);
        }
}

void beep(void)
{
        sound_delay = 10;
        sound(500);
}

static char buf[512];

int printk(const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
        i = vsprintf(buf, fmt, args);
        va_end(args);

        kprint(buf);
        return i;
}
