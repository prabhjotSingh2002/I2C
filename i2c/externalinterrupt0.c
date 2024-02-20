/*external interrupt*/

#include"header.h"

/*switch3 interrupt--p0.16*/
/*
  GPIO Port-0.16 ----> EINT0 --> 14 number
  PINSEL1-->0x1
*/
extern int head;
void  EINT0ISR(void)__irq
{

	head=!head;
	 // Clear the interrupt flag
    EXTINT |= (1 << 0);
	  VICVectAddr=0X0;
}

void configVicExt0(void)
{
	PINSEL1|=0x1;
 	VICIntSelect=0;
	VICVectCntl1=14|(1<<5);
	VICVectAddr1=(int)EINT0ISR;
	VICIntEnable|=(1<<14);
}

void enableExtIntr0(void)
{
	  EXTINT|=(1<<0);  //clearing  EXTERNAL INTERRUPT 0	 flag
	  EXTMODE|=(1<<0);//MAKING IT EDGE SENSITIVE
	  EXTPOLAR|=0;//making it for falling edge

}

void disableVicExt0(void)
{
 	PINSEL1&=~(3<<0);
	VICVectCntl1&=~(1<<5);
	VICIntEnable&=~(1<<14);
}

