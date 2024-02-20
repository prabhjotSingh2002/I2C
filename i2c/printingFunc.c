#include"header.h"


/*PRINTING VALUES */

void uart0printTD(Time t,Date d)
{
    
	 	uart0Tx((t.h/0x10)+'0');
		uart0Tx((t.h%0x10)+'0');
		uart0Tx(':');

		uart0Tx((t.m/0x10)+'0');
		uart0Tx((t.m%0x10)+'0');
		uart0Tx(':');

		uart0Tx((t.s/0x10)+'0');
		uart0Tx((t.s%0x10)+'0');

         if(t.H12h24==1) //if 12mode is active
        {
                if(t.aP==1)
                {
                      uart0txString("PM") ;
                }
                else
                {
                      uart0txString("AM") ;
                }
        }
        else         //for 24mode
        {
                //nothing  to print
                 uart0txString("24hr mode  ") ;
        }

		uart0txString("  ");
		uart0txString("DATE-");
		
		uart0Tx((d.date/0x10)+'0');
		uart0Tx((d.date%0x10)+'0');
		uart0Tx('/');

		uart0Tx((d.month/0x10)+'0');
		uart0Tx((d.month%0x10)+'0');
		uart0Tx('/');

		uart0Tx((d.year/0x10)+'0');
		uart0Tx((d.year%0x10)+'0');
		
		uart0txString("  ");

		switch(d.day)
		{
			 case 0x1: uart0txString("SUN");break;
			 case 0x2: uart0txString("MON");break;
			 case 0x3: uart0txString("TUE");break;
			 case 0x4: uart0txString("WED");break;
			 case 0x5: uart0txString("THUR");break;
			 case 0x6: uart0txString("FRI");break;
			 case 0x7: uart0txString("SAT");break;
		}

 		uart0txString("\r\n");
}


void lcdprintTD(Time t,Date d)
{
		lcd_cmd(0x01);
		lcd_cmd(0x80);

	 	lcd_data((t.h/0x10)+'0');
		lcd_data((t.h%0x10)+'0');
		lcd_data(':');

		lcd_data((t.m/0x10)+'0');
		lcd_data((t.m%0x10)+'0');
		lcd_data(':');

		lcd_data((t.s/0x10)+'0');
		lcd_data((t.s%0x10)+'0');

        if(t.H12h24==1) //if 12mode is active
        {
                if(t.aP==1)
                {
                      String("PM") ;
                }
                else
                {
                      String("AM") ;
                }
        }
        else         //for 24mode
        {
                //nothing  to print

        }

		 lcd_cmd(0xC0);
		
		
		lcd_data((d.date/0x10)+'0');
		lcd_data((d.date%0x10)+'0');
		lcd_data('/');

		lcd_data((d.month/0x10)+'0');
		lcd_data((d.month%0x10)+'0');
		lcd_data('/');

		lcd_data((d.year/0x10)+'0');
		lcd_data((d.year%0x10)+'0');
		
		String("  ");

		switch(d.day)
		{
			 case 0x1: String("SUN");break;
			 case 0x2: String("MON");break;
			 case 0x3: String("TUE");break;
			 case 0x4: String("WED");break;
			 case 0x5: String("THUR");break;
			 case 0x6: String("FRI");break;
			 case 0x7: String("SAT");break;
		}

 		
}


void setTime(Time t1)
{
 	i2c_byte_write_frame(0XD0,0x0,t1.s);  //set sec
	i2c_byte_write_frame(0XD0,0x1,t1.m);  //set min
    /////if 12hour mode is activated 
    if(t1.H12h24==1)
    {
	    i2c_byte_write_frame(0XD0,0x2,t1.h| setAmPm(t1.aP)|setHMode(t1.H12h24));  //set hour
    }
    else ////// 24hour mode is activated
    {
        i2c_byte_write_frame(0XD0,0x2,t1.h|setHMode(t1.H12h24));  //set hour
    }
}

void setDate(Date d1)
{
	i2c_byte_write_frame(0XD0,0x3,d1.day);  //set day
	i2c_byte_write_frame(0XD0,0x4,d1.date);  //set date
	i2c_byte_write_frame(0XD0,0x5,d1.month);  //set month
	i2c_byte_write_frame(0XD0,0x6,d1.year);  //set year

}
