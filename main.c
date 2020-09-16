#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>



void USART_INIT(unsigned char ubrr)
{
	UBRRH=(unsigned char)(ubrr>>8);
	UBRRL=(unsigned char)(ubrr);
	
	UCSRB|=(1<<TXEN)|(1<<RXEN);
	UCSRC|=(3<<UCSZ0);
}
unsigned char USART_RECIEVE()
{
	while(!(UCSRA&(1<<RXC)));
	return UDR;
}

int main(void)
{
	USART_INIT(25);
	DDRB = 0xff;
	DDRD = 0x00;
	DDRA = 0x00;
	PORTA = 0b11111111;
	
	PORTB =0b00000000;
	unsigned char x;
	while(1)
	{
		x = USART_RECIEVE();
		switch(x)
		{
			case '1': {PORTB=0b00000001;
				_delay_ms(250);}
			break;
			case '2': {PORTB=0b00000010;
				_delay_ms(250);}
			break;
			case '3': {PORTB=0b00000100;
				_delay_ms(250);}
			break;
			case '4': {PORTB=0b00001000;
				_delay_ms(250);}
			break;
			default : {PORTB=0b00010000;
				_delay_ms(250);}
		}
	}
	
}
