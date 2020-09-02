/*
 * ledmatrix2.c
 *
 * Created: 01-09-2020 23:17:10
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>







int dirr (int l,int r1,int r2 )	{
	PORTB=r1;
	int f=l;
	
	int m=0;
	int j=r2;
	int d;
	for( d=0;d<f;d++){
		m=m+(int)(pow(2,j)+0.5);
		j--;
		if(j<0){         
			j=7;
		}
	}
	PORTD  &= ~(m);

	_delay_ms(500);
	
}





int main(void)
{
    DDRB = 0xff;
	DDRD = 0xff;
	DDRA = 0x00;
//	PORTB =0b00000001;   code for lighting top left led
//	PORTD = 0b01111111;
	PORTA = 0b11111111;
	
PORTD = 0b11111111;
	PORTB =0b00000001;
	int h=7;
	int lm=224;
    while (1) 
    { 
		
		int length_snake=3;
		int row =1;
		PORTD = 0b11111111;
      dirr (length_snake,row,h );		
			h--;
			if(h<0){
				h=7;
			}		
		
	
		
}

}

