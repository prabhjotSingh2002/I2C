#include"header.h"

  Time t,Alarm;
  Date d;
  int switching=0;

	

   
char settings[3][10]={"time Date","Alarm set","stopwatch"};
int option=0;


main()
{
	 Date d1;
	 Time t1;
	/*set time t1 11:59:55*/
	
    t1.h=0x11;
    t1.m=0x59;
    t1.s=0x55;
    t1.aP=1;     //pm
    t1.H12h24=1;//12hr mode	
	
	/*set date day month and year ---saturday 27/1/24*/
	
     d1.day=0x7;
     d1.date=0x26;
	 d1.month=0x01;
	 d1.year=0x24;
  ////////////////////////////////////////////////////
	init();
	uart0init(9600);
	i2c_init();
	uart0txString("I2C \r\n");

	///////////external interrupt0 activation //////////////
	configVicExt0();
	enableExtIntr0();	//sw3
	///////////////////////////////////////////////

    ///////////external interrupt1 activation //////////////
				configVicExt1();
				enableExtIntr1();	//sw1
	///////////////////////////////////////////////

    ///////////external interrupt2 activation //////////////
//				configVicExt2();
//				enableExtIntr2();	//sw2
	///////////////////////////////////////////////

	//////////timer intrupption activation//////
	configVicTimer();
	////////////////////////////////////////////
	
//	set rtc time 11:59:55  
	setTime(t1);
	

//	set date day month and year ---friday 26/1/24
	 setDate(d1);
	
	
	/*read rtc time & print on serial terminal*/
	 while(1)
	 {
		while(switching==0)
		{

			t.h=i2c_byte_read_frame(0xD0,0x2);
			t.m=i2c_byte_read_frame(0xD0,0x1);
			t.s=i2c_byte_read_frame(0xD0,0x0);
          	t.aP=(t.h>>5)&1;
           	t.H12h24=(t.h>>6)&1;
          	t.h=(t.h&0x1f);

			d.day=i2c_byte_read_frame(0xD0,0x3);
			d.date=i2c_byte_read_frame(0xD0,0x4);
			d.month=i2c_byte_read_frame(0xD0,0x5);
			d.year=i2c_byte_read_frame(0xD0,0x6);

			checkAlarm(t,Alarm);

 			uart0printTD(t,d);
			lcdprintTD(t,d);
			delayms(500);
	 	}

		if(switching==1)
		{
				lcd_cmd(0x01);
		  	while(switching==1)
			{
					String("Enter Settings: ");
					lcd_cmd(0xC0);
							
					String(settings[option]);
				if(SW2==0)
				{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					callSetting(option);
					option=0;
				}


	 			while(SW1==0)
				{
					uart0txString("sw1 pressed\r\n");
		 			while(SW1==0);
					option++;
					option=option%3;			
				}
				lcd_cmd(0x80);
			}	 	
	 	}
	   } //end of while 1 loop
	   
	
	
}//end of main

