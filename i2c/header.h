#include <LPC21xx.H>

/*Time datatype*/

#define setAmPm(pa)  ((pa<<5)&1)
#define setHMode(pa)  ((pa<<6)&1)

#define dth(n) (((n/10)<<4)|(n%10))

 typedef struct Time
 {
	 unsigned char h;
	 unsigned char m;
	 unsigned char s;
     unsigned char aP;
     unsigned char H12h24;
 }Time;

 /*Date DataType*/
 typedef struct Date
 {
   	unsigned char day;
	 unsigned char date;
	 unsigned char month;
	 unsigned char year;
 }Date;


void uart0init(unsigned int baud);
void uart0tx(unsigned char data);
unsigned char uart0rx(void);
void uart0rxString(unsigned char*p,unsigned int bytes );
 void uart0txString(unsigned char *p);
 void uart0Tx(unsigned char data);

 void lcd_data(unsigned char data);
 void lcd_cmd(unsigned char data);
 void init(void);
 void String(char *ptr);
 void cgram1(void);
 void cgram2(void);

 void delayms(unsigned int ms);
 void delaysec(unsigned int s);

 void spi0init(void);
 unsigned char spi0(unsigned char data);

 void strrev2(char *p,char *q);
 void sprintf2(char *s,float n);
 int sprintf1(char *s,int num);

 void clearstr(unsigned char *s,int n);

unsigned short int mcp3204AdcRead(unsigned char chnum);
void uart0txString(unsigned char *p);


 void i2c_init(void);
 void i2c_byte_write_frame(unsigned char sa,unsigned char mr,unsigned char data);
 unsigned char i2c_byte_read_frame(unsigned char sa,unsigned char mr);

void uart0printTD(Time t,Date d);
void lcdprintTD(Time t,Date d)	;
void setDate(Date d1);
void setTime(Time t1);


 
int modeSetting(void);
int hourSetting(void);
int AmPmSetting(void);
int minSetting(void);
int dateSetting(void);
int  monthSetting(void);
int  yearSetting(void);
int  daySetting(void);

void configVicExt0(void);
void enableExtIntr0(void);
void  EINT0ISR(void)__irq;
void disableVicExt0(void);

#define SW1 ((IOPIN0>>14)&1)//SW1--P0.14
#define SW2 ((IOPIN0>>15)&1)//SW2--P0.15


#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
#define BUZ  (1<<21)


void disableVicExt2(void);
void enableExtIntr2(void);
void configVicExt2(void);



void disableVicExt1(void);
void enableExtIntr1(void);
void configVicExt1(void);


int minSettingAlarm(void);
int AmPmSettingAlarm(void);
int hourSettingAlarm(void);
int modeSettingAlarm(void);
void checkAlarm(Time t,Time Alarm);


void configVicTimer(void);

void delayms(unsigned int ms);  

void scrollPrint(char *p,char *q);

void callSetting(int option);


