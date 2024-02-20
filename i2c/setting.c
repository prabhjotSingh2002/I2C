#include"header.h"


/*sw3 pressed*/

extern int stage;
extern int switching;
int temp1=0,temp2=0;


unsigned char month=1;
unsigned char year=0;
unsigned char date=1;
unsigned char m=0;
unsigned char h=0;
unsigned char mode=0;//12hrmode---1 |||||| 24hrmode---0
unsigned char aP=0;//am--0 & pm==1
unsigned  char day=1;

int modeSetting(void)
{
	
	lcd_cmd(0x01);
	String("Enter Mode: ");
	lcd_cmd(0xC0);
	
    

	while(1)
	{
		uart0txString("in mode loop\r\n");
		lcd_cmd(0xC0);
		
        if(mode==1)
        {
          String("12HR MODE");  
        }
        else
        {
          String("24HR MODE");  
        }		
				
				if(SW2==0)
				{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					//save setting would be made in hour section i2c_byte_write_frame(0XD0,0x2,);
					stage++;
					return 0;
				}


	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);
				mode=!mode;		
		}

	}
}

int hourSetting(void)
{
	
	unsigned char hhex=dth(h);
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

					if(mode==0) //24hr mode
					{
						//add hour in 24hr mode
                        //clearing 6th bit--24hr mode
                         hhex=hhex & ~(1<<6) ;
                        
                        if((hhex>>5)&1)//check if 5th bit is 1 
                        {
                           i2c_byte_write_frame(0XD0,0x2,hhex);
                        }
                        else
                        {
                            //clear the 5th bit
                            hhex=hhex & ~(1<<5);
                            i2c_byte_write_frame(0XD0,0x2,hhex);
                        }  
						 stage=stage+2;;
				       	 return 0;
					}
					else if(mode==1)    //12hr mode
					{
					 	//temp1=i2c_byte_read_frame(0xD0,0x2);
						//i2c_byte_write_frame(0XD0,0x2,hhex);//activating 12hr mode set 6th bit
      /////////////////////////////////////////////////////////////////////////////                  
                   /*   for the 12 hr mode store hour data in Am-Pm setting   

                   */
      //////////////////////////////////////////////////////////////////////////////
                        stage++;
					    return 0;
					}
					
		}

	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

					   h++;
                  if(mode==1)//12hr mode
                  {
						   h=h%12;    
                   }
                   else if(mode==0)
                   {
							h=h%24;
                   }
                   hhex=dth(h);
		}

	}
}
 
int AmPmSetting()
{
    unsigned char hhex=dth(h);
	lcd_cmd(0x01);
	String("Enter AM-PM: ");
	lcd_cmd(0xC0);
    if(aP==0)
    {
        String("AM");
    }
    else if(aP==1)
    {
        String("PM");
    }

	while(1)
	{
		uart0txString("in amPm loop\r\n");
		lcd_cmd(0xC0);
		if(aP==0)
        {
            String("AM");
        }
        else if(aP==1)
        {
            String("PM");
        }
		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
                    ////it is operated in 12 hr mode -- set bit 6//
                     hhex=hhex|(1<<6);

                    if(aP==0)//am
                    {
                       //clear 5th bit
                       hhex=hhex & ~(1<<5);
                    }
                    else if(aP==1)
                    {
                       //set 5th bit
                        hhex=hhex|(1<<5);
                    }


					i2c_byte_write_frame(0XD0,0x2,hhex);
					stage++;
					return 0;
		}
	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

				///have to make changes toggleing am to pm & VICE VERSA//////
				if(aP==0)//am to pm
                {
                    aP=1;
                }
                else if(aP==1)//pm to am
                {
                    aP=0;
                }
		}


	}
}

int minSetting(void)
{
	
	unsigned char mhex=dth(m);
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
					i2c_byte_write_frame(0XD0,0x1,mhex);
					stage++;
					return 0;
				}


	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);
				m++;
				m=m%60;
                mhex=dth(m);			
		}

	}
}

int dateSetting()
{
	
	unsigned char datehex=dth(date);
	unsigned char n;
	lcd_cmd(0x01);
	String("Enter Date: ");
	if((month==1)|(month==3)|(month==5)|(month==7)|(month==8)|(month==10)|(month==12))
	{
				 	n=31;
	}
	else if((month==4)|(month==6)|(month==9)|(month==11))
	{
				 	n=30;
	}
	else if(month==2)
	{
		     if(year%4==0)
			{
				n=29;
			}
			else
			{
				n=28	;
			}
	}

	while(1)
	{
		uart0txString("in date loop\r\n");
		lcd_cmd(0xC0);
		lcd_data((datehex/0x10)+'0');
		lcd_data((datehex%0x10)+'0');

		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					i2c_byte_write_frame(0XD0,0x4,datehex);
					stage++;
					return 0;
		}
	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);
				///have to make changes according to month//////
						date++;	
						date=date%(n+1);

				     	date=(date==0?1:date);
                	datehex=dth(date);
				
		}


	}
}

int yearSetting()
{
	unsigned char yearhex=dth(year);
	
	lcd_cmd(0x01);
	String("Enter Year: ");

	while(1)
	{
		uart0txString("in year loop\r\n");
		lcd_cmd(0xC0);
		lcd_data((yearhex/0x10)+'0');
		lcd_data((yearhex%0x10)+'0');
		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					i2c_byte_write_frame(0XD0,0x6,yearhex);
					stage++;
					return 0;
		}
	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

				///have to make changes according to month//////
			
						year++;
						year=year%100;
				
				yearhex=dth(year);
		}


	}
} 
int  monthSetting()
{
	
	unsigned char monhex=dth(month);
	lcd_cmd(0x01);
	String("Enter Month: ");


	while(1)
	{
		uart0txString("in month loop\r\n");
		lcd_cmd(0xC0);
		lcd_data((monhex/0x10)+'0');
		lcd_data((monhex%0x10)+'0');
		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					i2c_byte_write_frame(0XD0,0x5,monhex);
					stage++;
					return 0;
		}
	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

				///have to make changes according to month//////					
					month++;
					month=month%13;
				 	month=(month==0?1:month);
					
				
                monhex=dth(month);
		}


	}
}
int  daySetting()
{
	
	unsigned char dayhex=dth(day);
	lcd_cmd(0x01);
	String("Enter Day: ");


	while(1)
	{
		uart0txString("in day loop\r\n");
		lcd_cmd(0xC0);
		lcd_data((dayhex/0x10)+'0');
		lcd_data((dayhex%0x10)+'0');
		if(SW2==0)
		{
					uart0txString("sw2 pressed\r\n");
				 	while(SW2==0);
					i2c_byte_write_frame(0XD0,0x3,dayhex);
					stage++;
					return 0;
		}
	 	while(SW1==0)
		{
				uart0txString("sw1 pressed\r\n");
		 		while(SW1==0);

				///have to make changes according to month//////					
					day++;
					day=day%8;
				 	day=(day==0?1:day);
					
				
                dayhex=dth(day);
		}


	}
}






