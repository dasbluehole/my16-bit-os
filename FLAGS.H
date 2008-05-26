/*
 *  LittleOS
 *  Copyright (C) 1998 Lacroix Pascal (placr@mygale.org)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/*Modified by Ashok shankar Das*/
#ifndef _FLAGS_H_
#define _FLAGS_H_

extern int get_flags() {int r;asm{pushf; pop ax;mov r,ax;}return (r);}

extern void set_flags(x) {asm{push x; popf;}}

/* disable interrupts */
extern void cli() {asm cli;}

/* enable interrupts */
extern void sti() {asm sti;}

#endif
