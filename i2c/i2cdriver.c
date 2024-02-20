#include"header.h"

void i2c_init(void)
{
 	PINSEL0|=0x50;	//p0.2->scl,p0.3->sda
	I2SCLH=I2SCLL=75;//FOR 100KBPS
	I2CONSET=(1<<6);//ENABLE I2C PERIPHERALS
}

#define SI ((I2CONSET>>3)&1)

void i2c_byte_write_frame(unsigned char sa,unsigned char mr,unsigned char data)
{
 	/*generate start condition*/
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);

	if(I2STAT!=0X08)
	{
	 	uart0txString("ERR.start condition\r\n");
		goto exit;
	}

	/*send sa+w*/
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x20)
	{
	 uart0txString("ER: SA+W\r\n");
	 goto exit;
	}

	/*send m/r addr*/
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x30)
	{
	 	uart0txString("ERR. memory address\r\n");
		goto exit;
	}

	/*send data*/
	I2DAT=data;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x30)
	{
	 	uart0txString("ERR. data\r\n");
		goto exit;
	}
	exit:
		/*generate stop condition*/
		I2CONSET=(1<<4);
		I2CONCLR=(1<<3);
}

unsigned char i2c_byte_read_frame(unsigned char sa,unsigned char mr)
{
 	unsigned char temp;

	/*generate start condition*/
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);
	if(I2STAT!=0x08)
	{
	 	uart0txString("ERR. start condition\r\n");
		goto exit;	
	}

	/*send SA+W */
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x20)
	{
	 	uart0txString("ERR. SA + W\r\n");
		goto exit;
	}

	/*send memory address*/
	I2DAT=mr;
	 I2CONCLR=(1<<3);
	 while(SI==0);
	 if(I2STAT==0x30)
	 {
	  	uart0txString("ERR. MEMORY ADDR\r\n");
		goto exit;
	 }

	 /*restart condition*/
	 I2CONSET=(1<<5);
	 I2CONCLR=(1<<3);
	 while(SI==0);
	 I2CONCLR=(1<<5);
	 if(I2STAT!=0x10)
	 {
		uart0txString("ERR. START CONDITION\r\n");
		goto exit;
	 }

	 /*send SA+R*/
	 I2DAT=sa|1;
	 I2CONCLR=(1<<3);
	 while(SI==0);
	 if(I2STAT==0x48)
	 {
		 uart0txString("ERR. SA+R\r\n");
		goto exit;
	 }

	 /*read data from slave*/

	 I2CONCLR=(1<<3);
	 while(SI==0);
	 temp=I2DAT;

	 /*generate stop condition */
	 exit:
	 	I2CONSET=(1<<4);
		I2CONCLR=(1<<3);

	/*return received data */
	return temp;
}



