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
/*****************************************/
/******Modified by Ashok S Das************/
/*****************************************/

unsigned char inportb_p(unsigned int port)		/* Input a byte from a port	*/
{
   unsigned char r;

//   asm volatile {"inb %%dx,%%al;outb %%al,$0x80":"=a" (ret):"d" (port));
   asm{
	mov dx,port;
	in al,dx;
	mov r,al;
	mov dx,0x80;
	out dx,al;
   }
   return r;
}

void outportb_p(unsigned int port,unsigned char value)	/* Output a byte to a port	*/
{
//   asm volatile ("outb %%al,%%dx;outb %%al,$0x80"::"d" (port), "a" (value));
   asm{
	mov dx,port;
	mov al,value;
	out dx,al;
	mov dx,0x80;
	out dx,al;
   }
}

void outportw_p(unsigned int port,unsigned int value)	/* Output a word to a port	*/
{
//   asm volatile ("outw %%ax,%%dx;outb %%al,$0x80"::"d" (port), "a" (value));
   asm{
	mov dx,port;
	mov ax,value;
	out dx,ax;
	mov dx,0x80;
	out dx,ax;
   }
}

unsigned char inportb(unsigned int port)		/* Input a byte from a port	*/
{
   unsigned char r;

//   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   asm{
	mov dx,port;
	in al,dx;
	mov r,al;
   }
   return r;
}

void outportb(unsigned int port,unsigned char value)	/* Output a byte to a port	*/
{
  // asm volatile ("outb %%al,%%dx"::"d" (port), "a" (value));
  asm{
	mov dx,port;
	mov al,value;
	out dx,al;
  }
}

void outportw(unsigned int port,unsigned int value)	/* Output a word to a port	*/
{
  // asm volatile ("outw %%ax,%%dx"::"d" (port), "a" (value));
  asm{
	mov dx,port;
	mov ax,value;
	out dx,ax;
  }
}