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

#ifndef IO_INCLUDE
#define IO_INCLUDE

struct WORDREGS {
    unsigned int    ax, bx, cx, dx, si, di, cflag, flags;
};

struct BYTEREGS {
    unsigned char   al, ah, bl, bh, cl, ch, dl, dh;
};

union   REGS    {
    struct  WORDREGS x;
    struct  BYTEREGS h;
};
typedef union REGS REGS;

struct  SREGS   {
    unsigned int    es;
    unsigned int    cs;
    unsigned int    ss;
    unsigned int    ds;
};
typedef struct SREGS SREGS;
struct  REGPACK {
    unsigned    r_ax, r_bx, r_cx, r_dx;
    unsigned    r_bp, r_si, r_di, r_ds, r_es, r_flags;
};


unsigned char inportb(unsigned int port);
void outportb(unsigned int port, unsigned char value);
void outportw(unsigned int port, unsigned int value);
unsigned char inportb_p(unsigned int port);
void outportb_p(unsigned int port, unsigned char value);
void outportw_p(unsigned int port, unsigned int value);

#define setvec(n, isr)  (void)(*(void (interrupt far * far *)())(4 * (n)) = (isr))
unsigned char far *getvec();
#endif
