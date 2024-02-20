/*call settings*/

#include"header.h"


int stage=0;
int stage1=0;
int min,sec,hr;
int pause=0;
extern int switching;
extern Time Alarm;

void callSetting(int option)
{
	lcd_cmd(0x1);
	disableVicExt0();

	IODIR0|=LED1|LED2|LED3;
	IOCLR0=LED1|LED2|LED3;
	delayms(400);	
	IOSET0=LED1|LED2|LED3;


	 switch(option)
	 {
	  	case 0:
			String("Date time settings");
			delayms(1000);

	    while(stage<8)
	    {
	 	    switch(stage)
		    {
                case 0:modeSetting();break;
		        case 1: hourSetting();break;		  
		        case 2: AmPmSetting();break;
		        case 3: minSetting();break;
                case 4: yearSetting();break; 		        
		        case 5: monthSetting();break;
		        case 6: dateSetting();break; 
				case 7: daySetting();break;  
           
		    }
		    uart0txString("in loop of setting \r\n");
	    }
	      uart0txString("come out of setting loop\r\n");
		  stage=0;
		  switching=0;
		  break;


		case 1:
			String("Alarm settings");
			delayms(1000);


		 while(stage1<4)
	     {
	 	    switch(stage1)
		    {
                case 0: modeSettingAlarm();break;
		        case 1: hourSettingAlarm();break;		  
		        case 2: AmPmSettingAlarm();break;
		        case 3: minSettingAlarm();break;  
           
		    }
		    uart0txString("in loop of alarm setting \r\n");
	     }
	      uart0txString("come out of alarm setting loop\r\n");
		  lcd_cmd(0x01);
		  String("Alarm has been set");
		  lcd_cmd(0xC0);

			lcd_data((Alarm.h/0x10)+'0');
			lcd_data((Alarm.h%0x10)+'0');
			lcd_data(':');

			lcd_data((Alarm.m/0x10)+'0');
			lcd_data((Alarm.m%0x10)+'0');
			lcd_data(' ');

			lcd_data((Alarm.H12h24/0x10)+'0');
			lcd_data((Alarm.H12h24%0x10)+'0');
			lcd_data(' ');

			lcd_data((Alarm.aP/0x10)+'0');
			lcd_data((Alarm.aP%0x10)+'0');
			lcd_data(' ');

		  	delayms(5000);
		  	stage1=0;
		  	switching=0;
		  	lcd_cmd(0x01);	
			break;


		 
		         
		case 2: 
	
			String("Stopwatch settings");
			delayms(1000);

			 //external interrupt1 to chage value of pause
				configVicExt1();
				enableExtIntr1();
				configVicExt0();
				enableExtIntr0();

			lcd_cmd(0x1);
		  	String("sw1 pause/conti");
			lcd_cmd(0xc0);

		  		 			 
				 
			while(1)
			{
				  for(hr=0;hr<100;hr++)
				  {
		 			for(min=0;min<60;min++)
					{
		 				for(sec=0;sec<60;sec++)
						{
					///////////////////////////////////////
							if(switching!=1)
							{	
								goto exit;
							}
							while(pause)
							{
								if(switching!=1)
								{	
									goto exit;
								}
							}			   
			  		///////////////////////////////////////
							lcd_data(hr/10 +48);
							lcd_data(hr%10 +48);
							lcd_data(':');
			 				lcd_data(min/10 +48);
							lcd_data(min%10 +48);
							lcd_data(':');
							lcd_data(sec/10 +48);
							lcd_data(sec%10 +48);
							delayms(980);
							
											
							lcd_cmd(0xc0);
						}
		   
					}
				   }

		
			}		
		   	exit:	disableVicExt1();
		         break;

	 }

	 ///out of switch case/////
	 			configVicExt0();
				enableExtIntr0();
	  return;
}