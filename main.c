/*
 * ledmatrix2.c
 *
 * Created: 01-09-2020 23:17:10
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>



static int lt=0; static int rt=0; static int up=0; static int dn=0;



void dirr (int l,int r1,int r2 ) {
	PORTB =r1;
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

	_delay_ms(250);
	
}



void dirl (int l,int r1,int r2 )	{
	PORTB =r1;
	int f=l;
	
	int m=0;
	int j=r2;
	int d;
	for( d=0;d<f;d++){
		m=m+(int)(pow(2,j)+0.5);
		j++;
		if(j>7){
			j=0;
		}
	}
	PORTD  &= ~(m);

	_delay_ms(250);
	
}






void dird(int l,int c1,int c2){
	PORTD = ~((int)(pow(2,(8-c1))+0.5));
	int m1=0;
	int j1=c2;
	for(int d1=0;d1<l;d1++){
		m1=m1+(int)(pow(2,j1)+0.5);
		j1++;
		if(j1>7){
			j1=0;
		}
	}
	PORTB |= m1;
	_delay_ms(250);
}




      void diru(int l,int c1,int c2){
	      PORTD = ~((int)(pow(2,(8-c1))+0.5));
	      int m1=0;
	      int j1=c2;
	      for(int d1=0;d1<l;d1++){
		      m1=m1+(int)(pow(2,j1)+0.5);
		      j1--;
		      if(j1<0){
			      j1=7;
		      }
	      }
	      PORTB |= m1;
	      _delay_ms(250);
      }

   void cond(){
	    if(bit_is_clear(PINA,5)){
		    lt=1;
		    rt=up=dn=0;
	    }
	    _delay_ms(35);
	    if(bit_is_clear(PINA,3)){
		    rt=1;
		    lt=up=dn=0;
	    }
	     _delay_ms(35);
	    if(bit_is_clear(PINA,0)){
		    up=1;
		    rt=lt=dn=0;
	    }
         _delay_ms(35);
	    if(bit_is_clear(PINA,7)){
		    dn=1;
		    rt=up=lt=0;
	    }
	   
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
	int v=0;
	int h2=0;
	int v1=7;
	
    while (1) 
    { 
		
		int length_snake=4;
		 cond();
	 
	
		
		if(rt==1){
			int row =1;
			PORTD = 0b11111111;
			dirr (length_snake,row,h );		
			h--;
			if(h<0){
			     h=7;
			}		
		}
			
		 cond();
			
			
			
		if(lt==1){
			int row =1;
			PORTD = 0b11111111;
			dirl (length_snake,row,h2 );		
				h2++;
				if(h2>7){
					h2=0;
				}		
		}
	
	
	 	cond();
	
	
	
		if(dn==1){
			int column=1;
			PORTD = 0b11111111;
			PORTB =0b00000000;
			dird(length_snake,column,v);
			v++;
			if(v>7){
				v=0;
			}
		}



 		cond();




		if(up==1){
			int column=1;
			PORTD = 0b11111111;
			PORTB =0b00000000;
			diru(length_snake,column,v1);
			v1--;
			if(v1<0){
				v1=7;
			}
		}

		
	}

}
