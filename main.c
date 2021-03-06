
//*** Program Header ***
/************************************************************************************
	File Name: ELNC_6007_LAB1_GS		
	Author:	   ASHISH SHARMA	
	Date:	   March 11, 2022 
	Modified:  None	
	Description:    This program will:
			1) Convert the analog value obtained from the potentiometer connected at port A into digital through A/D conversion.
			2) Calculate the linear equation from the digital value generated by A/D converter and display it on LCD.

************************************************************************************/

// Preprocessor ===================================================================

#define F_CPU 8000000UL
#define lcd PORTC
#include <avr/io.h>
#include <util/delay.h>

int ADC_read(int x)
{
	ADMUX=x|0x40;
	ADCSRA=0xd7;
	while((ADCSRA & 0x10)==0x00);
	return ADC;
}

void lcdinit()
{
	lcd_cmd(0x02); //to set the home position
	lcd_cmd(0x28); // 4bit mode, 0x38 8 bit mode
	lcd_cmd(0x06); // increment 
	lcd_cmd(0x01); //clear lcd
	lcd_cmd(0x0C); // set cursor OFF
}

void lcd_cmd(char c)
{
	lcd=((c & 0xF0)+0x04);
	_delay_ms(1);
	lcd=lcd-0x04;
	lcd=((c<<4)& 0xF0) +0x04;
	_delay_ms(1);
	lcd=lcd-0x04;
}

void lcd_data(char d)
{	
	lcd=((d & 0xF0)+0x05);
	_delay_ms(1);
	lcd=lcd-0x04;
	lcd=((d<<4)& 0xF0) +0x05;
	_delay_ms(1);
	lcd=lcd-0x04; 
}

void lcd_str(char ch[])
{ int i=0;
	while (ch[i]!='\0')
	{
		lcd_data(ch[i]);
		i++;
	}
}

void lcd_num(int n)
{
	if (n<10)
	{
		lcd_data(n+48);
	}
	else
	{
		lcd_num(n/10);
		lcd_data((n%10)+48);
	}
}

void smiley()
{
	lcd_cmd(0x40);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00001010);
	lcd_data(0b00000000);
	lcd_data(0b00010001);
	lcd_data(0b00001110);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
}
void sad()
{
	lcd_cmd(0x48);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00001010);
	lcd_data(0b00000000);
	lcd_data(0b00001110);
	lcd_data(0b00010001);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
}
/*********************************************************************************
***** MAIN FUNCTION **************************************************************
**********************************************************************************/
int main(void)
{	
	DDRC =0xFF;
	DDRA=0x00; 
	lcdinit();
	lcd_str("Welcome");
	_delay_ms(100);
	lcd_cmd(0x01);
   
    while (1) 
    {	
		int val= ADC_read(0);
		float mv = (5/1024.0)*val*1000;
		float temp = mv/10;
		lcd_cmd(0x80);
		lcd_num(temp);
		_delay_ms(100);			
    }
}

