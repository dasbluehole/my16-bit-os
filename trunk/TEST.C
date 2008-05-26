/************************************************/
/*My OS See readme.txt for all other formalities*/
/************************************************/

#include "video.h"
#include "pio.h"
//#include "8259.h"
#define MK_FP(x,y) ((void _seg * )( x ) + ( void near * )( y ))
extern unsigned long _stklen=8192; 
extern void interrupt far reboot();
extern void interrupt far int21_hndl(REGS *r,SREGS *s);
#define VERSION "0.0.1a"
char *msg="************************Hello Tiny Os****************************";

main()
{
	char input;
	unsigned short i=0;
	/*Just see how we can write our Interrupt and set it to like dos does*/
	setvec(0x19,reboot);  		/*reboot interrupt*/
	setvec(0x21,int21_hndl); 	/*dos interrupt (non functional) */
	clrscr(); 		 	/*clear the screen*/

/* Now we will print some texts so that our eyes are satisfied */ 
	printk("\n%s\n",msg);		
	printk("\n\nMyOS Version 0.0.1a Loading......\n");

/*Let us do a loop by goto back jump WHICH IS NEVER GOOD */

p1:     printk("\n\t a)Test 1\n");
	printk("\t b)Test 2\n");
	printk("\n\n\n\n\tEnter your choice >");
	input=readkey();
	if(input=='a')
	{
		printk("\nTest %c\n",input);
	}
	else if(input=='b')
	{
		printk("\nTest %c\n",input);
	}
	else if(input=='q')
	{
		clrscr();
		printk("\n\n\n\t\tWell U need to quit\n");
		goto p2;
	}
	else 
	{
		clrscr();
		printk("invalid choice %c\n",input);
	}
	asm {mov ah,02;
		mov dl,07;
		int 0x21;
	}
	goto p1;
p2:	asm {int 0x19};       /* here we are invoking our int 0x19 routine*/
			      /* Which in turn reboot the PC  :-) */        	
	printk("This should not execute\n");
}
/* Interrupt routine for int 0x19*/

void interrupt far reboot()
{
	int i;
	void (*p)();
	printk("Now Rebooting.....!\n\nPress a key");
	readkey();
	outportb(0x64,0xfe);
	outportb(0x64,0xff);
	asm{cli;hlt};   //This will not execute if we suceed to boot by sending 0xfe to 0x64 port

}

void sto(char c)
{
	printk("%c",c);
}

/*Not implemented at all*/

void interrupt far int21_hndl(REGS *r, SREGS *s)
{
	printk("Got int 21h...%d \n",r->h.ah);
	switch(r->h.ah)
	{
		case 0x02: sto(r->h.dl);break;
		case 0x09: printk("%s\n",(char *)MK_FP(s->ds,r->x.dx));break; 
		default: printk("Not Implemented... Very bad\n");
	}
}
