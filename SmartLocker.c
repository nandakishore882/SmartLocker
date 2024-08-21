#include<reg51.h>
#define lcd P0
sbit sw1=P1^0;
sbit sw2=P1^1;
sbit sw3=P1^2;
sbit sw4=P1^3;
sbit led1=P2^3;
sbit led2=P2^4;
sbit led3=P2^5;
sbit led4=P2^6;
sbit rs=P2^0; 
sbit rw=P2^1;
sbit en=P2^2; 
void lcd_init();
void cmd(unsigned char);
void dat(unsigned char);
void delay();
void lcd_string(char *s);
char pass[4]={'0','0','0','0'};
char passe[4]={'0','0','0','0'};
int tmp=1;
int i,j,k,l;
int count=0;
#define FOSC 12000000
void serial_init(unsigned long int baud)
{
  unsigned long int divisor = 256 - (FOSC/(384*baud));
  SCON = 0x40;                      
  TMOD = 0x20;                           
  TH1 = divisor;			 
  TR1   = 1;                                                  
  TI    = 1;                            
}
void serialWrite(char ch)
	{
	SBUF=ch;
	while(TI==0);
	TI=0;
	delay();
  }
void main()
{
	P1=0xff;
	P2=0x00;
	
	lcd_init();
	cmd(0xc0);
	delay();
  lcd_string("Enter passcode");
	cmd(0xc0);
  delay();
	delay();
	while(tmp)
	{
		for(i=0;i<4;i++){
			passe[0]='1'+i;
			for(j=0;j<4;j++){
				passe[1]='1'+j;
				for (k=0;k<4;k++){
					passe[2]='1'+k;
					for (l=0;l<4;l++){
						passe[3]='1'+l;
						if(sw4==0)
						{
							tmp=0;
							break;
						}
					}
					if(tmp==0)
						break;
				}
				if(tmp==0)
					break;
			}
			if(tmp==0)
				break;
		}
	}
	cmd(0xc0);
	lcd_string(passe);
	serial_init(2400);
	for (i=0;i<4;i++){
		serialWrite(passe[i]);
		delay();
	}
	delay();
	cmd(0xc0);
	lcd_string("           ");
	tmp=0;
	while(1)
	{
		while(1)//p1
		{
			cmd(0xc0);
			if(sw1==0)
			{
				pass[0]='1';
				lcd_string("1        ");
				delay();
				tmp++;
			}
			else if(sw2==0)
			{
				pass[0]='2';
				lcd_string("2        ");
				delay();
				tmp++;
			}
			else if(sw3==0)
			{
				pass[0]='3';
				lcd_string("3        ");
				delay();
				delay();
				tmp++;
			}
			else if(sw4==0)
			{
				pass[0]='4';
				lcd_string("4        ");
				delay();
				tmp++;
			}
			if(tmp)
			{
			cmd(0xc0);
			lcd_string("*        ");
			tmp=0;
			break;
			}
		}
//---------------------------------------
		while(1)//p2
		{
			cmd(0xc0);
			if(sw1==0)
			{
				pass[1]='1';
				lcd_string("*1        ");
				delay();
				tmp++;
			}
			else if(sw2==0)
			{
				pass[1]='2';
				lcd_string("*2        ");
				delay();
				tmp++;
			}
			else if(sw3==0)
			{
				pass[1]='3';
				lcd_string("*3        ");
				delay();
				tmp++;
			}
			else if(sw4==0)
			{
				pass[1]='4';
				lcd_string("*4        ");
				delay();
				tmp++;
			}
			if (tmp)
			{
      cmd(0xc0);
			lcd_string("**        ");
				tmp=0;
				break;
			}
		}
//-----------------------------------
		while(1)//p3
		{
			cmd(0xc0);
			if(sw1==0)
			{
				pass[2]='1';
				lcd_string("**1        ");
				delay();
				tmp++;
			}
			else if(sw2==0)
			{
				pass[2]='2';
				lcd_string("**2        ");
				delay();
				tmp++;
			}
			else if(sw3==0)
			{
				pass[2]='3';
				lcd_string("**3        ");
				delay();
				tmp++;
			}
			else if(sw4==0)
			{
				pass[2]='4';
				lcd_string("**4        ");
				delay();
				tmp++;
			}
			if (tmp)
			{
			cmd(0xc0);
			lcd_string("***        ");
				tmp=0;
				break;
			}
		}
		//-----------------------------------
		while(1)//p4
		{
			cmd(0xc0);
			if(sw1==0)
			{
				pass[3]='1';
				lcd_string("***1        ");
				delay();
				tmp++;
			}
			else if(sw2==0)
			{
				pass[3]='2';
				lcd_string("***2        ");
				delay();
				tmp++;
			}
			else if(sw3==0)
			{
				pass[3]='3';
				lcd_string("***3        ");
				delay();
				tmp++;
			}
			else if(sw4==0)
			{
				pass[3]='4';
				lcd_string("***4        ");
				delay();
				tmp++;
			}
			if (tmp)
			{
			cmd(0xc0);
			lcd_string("****        ");
				tmp=0;
				break;
			}
		}
		cmd(0xc0);
		if(pass[0]==passe[0] && pass[1]==passe[1] && pass[2]==passe[2] && pass[3]==passe[3] )
		{
			lcd_string("correct password");
			led4=1;
			led3=0;
			led2=0;
			led1=0;
			delay();
			delay();
			while(1);
			break;
			break;
		}
		else
		{
			lcd_string("wrong password");
			count++;
			if (count==3)
			{
				led3=1;
				cmd(0xc0);
				lcd_string("Max limit reached");
				break;
				break;
			}
			else
			{
				for(i=0;i<4;i++)
				pass[i]='0';
				if(count==1)
				{
					led1=1;
					cmd(0xc0);
				  lcd_string("2 attempts remaining");
				}
				else if(count==2)
				{
					led2=1;
					cmd(0xc0);
				  lcd_string("1 attempts remaining");
				}
			}
		}
	}
}

void check1(int a)
{
	while(pass[a]=='0')
	{
		if (sw1==0)
			pass[a]=pass[a]+1;
		else if (sw2==0)
			pass[a]=pass[a]+1;
		else if (sw3==0)
			pass[a]=pass[a]+3;
		else if (sw2==0)
			pass[a]=pass[a]+4;
		}
}
void lcd_init()
{
    cmd(0x38);
    cmd(0x0e);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}
void cmd(unsigned char a)
{
    lcd=a;
    rs=0;
    rw=0;
    en=1;
    delay();
    en=0;
}
void dat(unsigned char b)
{
    lcd=b;
    rs=1;
    rw=0;
    en=1;
    delay();
    en=0;
}
void lcd_string(char *s)
{
    while(*s) {
       dat(*s++);
     }
}
void delay()
{
    unsigned int i;
    for(i=0;i<10000;i++);
}