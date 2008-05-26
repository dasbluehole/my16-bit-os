@echo off
tcc -I. -c io.c
tcc -I. -c video.c
tcc -I. -c vsprintf.c
tcc -I. -c test.c
tlib /C klib.lib -+io.obj-+video.obj-+vsprintf.obj,klib.lst
tcc test.obj klib.lib
exeflat test.exe kernel.sys 0x60
echo
echo deleting .obj files
@del *.obj
echo Done making kernel.sys
echo do a install by typing sys a: with a dos formated floppy in a: drive

