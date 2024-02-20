#include"header.h"

int ab[]={15,60,30,0,15};//PCLK changes for timer1
extern int stage1;

extern Time Alarm;
unsigned char m1=0;
unsigned char h1=0;
unsigned char mode1=0;//12hrmode---1 |||||| 24hrmode---0
unsigned char aP1=0;//am--0 & pm==1

int modeSettingAlarm(void)
{
	
	lcd_cmd(0x01);
	String("ALARM SETTING-");
	lcd_cmd(0xC0);
	
    

	while(1)
	{
		uart0txString("in mode loop\r\n");
		lcd_cmd(0xC0);
		
        if(mode1==1)
        {
          String("Enter Mode: 12HR MODE");  
        }
        else
        {
          String("Enter Mode: 24HR MODE");  
        }		
				
				if(SW2==0)
				{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					//save setting would be made in hour section i2c_byte_write_frame(0XD0,0x2,);
					stage1++;
					return 0;
				}


	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);
				mode1=!mode1;		
		}

	}
}

int hourSettingAlarm(void)
{
	
	unsigned char hhex=dth(h1);
	lcd_cmd(0x01);
	String("Enter Hour: ");

	while(1)
	{
		uart0txString("in hour loop\r\n");
		lcd_cmd(0xC0);
		lcd_data((hhex/0x10)+'0');
		lcd_data((hhex%0x10)+'0');
		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);

					if(mode1==0) //24hr mode
					{
						//add hour in 24hr mode
                        //clearing 6th bit--24hr mode
                         hhex=hhex & ~(1<<6) ;
                        
                        if((hhex>>5)&1)//check if 5th bit is 1 
                        {
								   Alarm.h=hhex;
                          // i2c_byte_write_frame(0XD0,0x2,hhex);
                        }
                        else
                        {
                            //clear the 5th bit
                            hhex=hhex & ~(1<<5);
							Alarm.h=hhex;
//                            i2c_byte_write_frame(0XD0,0x2,hhex);
                        }  
						 stage1=stage1+2;;
				       	 return 0;
					}
					else if(mode1==1)    //12hr mode
					{
					 	//temp1=i2c_byte_read_frame(0xD0,0x2);
						//i2c_byte_write_frame(0XD0,0x2,hhex);//activating 12hr mode set 6th bit
      /////////////////////////////////////////////////////////////////////////////                  
                   /*   for the 12 hr mode store hour data in Am-Pm setting   

                   */
      //////////////////////////////////////////////////////////////////////////////
                        stage1++;
					    return 0;
					}
					
		}

	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

					   h1++;
                  if(mode1==1)//12hr mode
                  {
						   h1=h1%12;    
                   }
                   else if(mode1==0)
                   {
							h1=h1%24;
                   }
                   hhex=dth(h1);
		}

	}
}

int AmPmSettingAlarm()
{
    unsigned char hhex=dth(h1);
	lcd_cmd(0x01);
	String("Enter AM-PM: ");
	lcd_cmd(0xC0);
    if(aP1==0)
    {
        String("AM");
    }
    else if(aP1==1)
    {
        String("PM");
    }

	while(1)
	{
		uart0txString("in amPm loop\r\n");
		lcd_cmd(0xC0);
		if(aP1==0)
        {
            String("AM");
        }
        else if(aP1==1)
        {
            String("PM");
        }
		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
                    ////it is operated in 12 hr mode -- set bit 6//
                     hhex=hhex|(1<<6);

                    if(aP1==0)//am
                    {
                       //clear 5th bit
                       hhex=hhex & ~(1<<5);
                    }
                    else if(aP1==1)
                    {
                       //set 5th bit
                        hhex=hhex|(1<<5);
                    }

			  		Alarm.h=hhex;	
			//		i2c_byte_write_frame(0XD0,0x2,hhex);
					stage1++;
					return 0;
		}
	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

				///have to make changes toggleing am to pm & VICE VERSA//////
				if(aP1==0)//am to pm
                {
                    aP1=1;
                }
                else if(aP1==1)//pm to am
                {
                    aP1=0;
                }
		}


	}
}

int minSettingAlarm(void)
{
	
	unsigned char mhex=dth(m1);
	lcd_cmd(0x01);
	String("Enter Min: ");

	while(1)
	{
		uart0txString("in min loop\r\n");
		lcd_cmd(0xC0);
		lcd_data((mhex/0x10)+'0');
		lcd_data((mhex%0x10)+'0');		
				
				if(SW2==0)
				{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					Alarm.m=mhex;
					stage1++;
					return 0;
				}


	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);
				m1++;
				m1=m1%60;
                mhex=dth(m1);			
		}

	}
}
 int flag=0;
void checkAlarm(Time t,Time Alarm)
{
		
	   if((t.m==Alarm.m)&&((Alarm.aP * Alarm.H12h24 * 12+ Alarm.h)==(t.aP * t.H12h24 * 12 +t.h)))
	   {
			///////////////////timer interrupt config///////////
			T1PR=ab[VPBDIV]*1000000-1;	//setting timer1
			T1MR0=3;					 //after 3sec  delay generated
			T1MCR=0X03;					  //Interrupt on MR0 & Reset on MR0
			T1TCR=1;
			/////////////////////////////////////////////////////
			flag=1 ;
			IODIR0|=BUZ;
			IOCLR0|=BUZ;
	   }
	   else if((t.m==Alarm.m)&&(t.h==Alarm.h))
	   {
		   	///////////////////timer interrupt config///////////
			T1PR=ab[VPBDIV]*1000000-1;	//setting timer1
			T1MR0=3;					 //after 3sec  delay generated
			T1MCR=0X03;					  //Interrupt on MR0 & Reset on MR0
			T1TCR=1;
			/////////////////////////////////////////////////////
			flag=1 ;
			IODIR0|=BUZ;
			IOCLR0|=BUZ;
	   }
	   else
	   {
	   		IOSET0=LED1|LED2|LED3;
			T1TCR=0;
		   flag=0;
	   }

}
