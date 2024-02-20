/*external interrupt*/

#include"header.h"

/*switch1 interrupt--p0.14*/
/*
  GPIO Port-0.14 ----> EINT1 --> 15 number
  PINSEL0-->2<<28
*/

//for alarm
extern int left;
void  EINT1ISR(void)__irq
{

	left=!left;
	 // Clear the interrupt flag
    EXTINT |= (1 << 1);
	  VICVectAddr=0X0;
}

void configVicExt1(void)
{
	PINSEL0|=(2<<28);
	
 	VICIntSelect=0;
	VICVectCntl2=15|(1<<5);
	VICVectAddr2=(int)EINT1ISR;
	VICIntEnable|=(1<<15);
}

void enableExtIntr1(void)
{
	  EXTINT|=(1<<1);  //clearing  EXTERNAL INTERRUPT 1	 flag
	  EXTMODE|=(1<<1);//MAKING IT EDGE SENSITIVE
	  EXTPOLAR|=0;//making it for falling edge

}

void disableVicExt1(void)
{
 	PINSEL0&=~(2<<28);
	VICVectCntl2&=~(1<<5);
	VICIntEnable&=~(1<<15);
}

