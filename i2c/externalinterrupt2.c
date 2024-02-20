/*external interrupt*/

#include"header.h"

/*switch2 interrupt--p0.15*/
/*
  GPIO Port-0.15 ----> EINT2 --> 16 number
  PINSEL0-->2<<30
*/
extern int right;
void  EINT2ISR(void)__irq
{
  
	   right=!right;
	 // Clear the interrupt flag
    EXTINT |= (1 << 2);
	  VICVectAddr=0X0;
}

void configVicExt2(void)
{
	PINSEL0|=(unsigned int)(1<<31);//(2<<30);
	
 	VICIntSelect=0;
	VICVectCntl3=16|(1<<5);
	VICVectAddr3=(int)EINT2ISR;
	VICIntEnable|=(1<<16);
}

void enableExtIntr2(void)
{
	  EXTINT|=(1<<2);  //clearing  EXTERNAL INTERRUPT 1	 flag
	  EXTMODE|=(1<<2);//MAKING IT EDGE SENSITIVE
	  EXTPOLAR|=0;//making it for falling edge

}

void disableVicExt2(void)
{
 	PINSEL0&=~(1<<31);//(2<<30)
	VICVectCntl3&=~(1<<5);
	VICIntEnable&=~(1<<16);
}

