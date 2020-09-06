/*
 * led-matrix-4.c
 *
 * Created: 05-09-2020 18:35:07
 * Author : user
 */ 









#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>



static int lt=0; static int rt=0; static int up=0; static int dn=0;
static int j,j1,j2;
static int ex=0;


void dirr (int l,int r1,int r2 )	{
	PORTD = 0b11111111;
	PORTB =(int)(pow(2,(r1-1))+0.5);
	int f=l;
	
	int m=0;
	j=r2;
	int d;
	for( d=0;d<f;d++){
		m=m+(int)(pow(2,j)+0.5);
		j--;
		if(j<0){
			j=7;
		}
	}
	PORTD  &= ~(m);

	_delay_ms(90);
	
}



void dirl (int l,int r1,int r2 )	{
	PORTD = 0b11111111;
	PORTB =(int)(pow(2,(r1-1))+0.5);
	int f=l;
	
	int m=0;
	j1=r2;
	int d;
	for( d=0;d<f;d++){
		m=m+(int)(pow(2,j1)+0.5);
		j1++;
		if(j1>7){
			j1=0;
		}
	}
	PORTD  &= ~(m);

	_delay_ms(10);
	
}






void dird(int l,int c1,int c2){
	
	PORTB =0b00000000;
	
	PORTD = ~((int)(pow(2,(7-c1))+0.5));
	int m1=0;
	 j2=c2;
	for(int d1=0;d1<l;d1++){
		m1=m1+(int)(pow(2,j2)+0.5);
		j2++;
		if(j2>7){
			j2=0;
		}
	}
	PORTB |= m1;
	_delay_ms(90);
	
}




void diru(int l,int c1,int c2){
	PORTD = 0b11111111;
	PORTB =0b00000000;
	PORTD = ~((int)(pow(2,(7-c1))+0.5));
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
	_delay_ms(10);
}

void cond(){
	if(bit_is_clear(PINA,5)){
		ex=lt=1;
		rt=up=dn=0;
	}
	_delay_ms(50);
	if(bit_is_clear(PINA,3)){
		ex=rt=1;
		lt=up=dn=0;
	}
	_delay_ms(50);
	if(bit_is_clear(PINA,0)){
		ex=up=1;
		rt=lt=dn=0;
	}
	_delay_ms(50);
	if(bit_is_clear(PINA,7)){
		ex=dn=1;
		rt=up=lt=0;
	}
	_delay_ms(50);
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
	int length_snake=4;
	int l1,l2,l3,l4;
	l3=l4=l1=l2=1;
	 int column;
	int row;
	while (1)
	{
		cond();
		if(bit_is_clear(PINA,1)){
			
			if(ex==0){
			
				 row =3;
			
			l1=length_snake;
			if(ex==0){
				dirr (length_snake,row,h );
		
				h--;
				
				if(h<0){
					h=7;
				}
			}
			}
			
		
		
		if(rt==1 && ex!=0 ){
		
			if(l2>1){
				l2--;
				dird(l2,column,v);
				v++;
				if(v>7){
					v=0;
				}
				
			}
			if(l1==1 && l2>1){
				row=j2;
				if(row<=0){
					row=8;
				}
				h=7-column;
			}
	
			if(l1!=length_snake){
				l1++;
			}
						dirr (l1,row,h );
						if(l1==length_snake){
							h--;
						}
						if(h<0){
							h=7;
						}
		
		/*	PORTD = 0b11111111;
			dirr (l1,row,h );
			if(l1==length_snake){
				h--;
			}
			if(h<0){
				h=7;
			}*/
			
		}
		
		
		cond();
		
		if(dn==1){
			if(l1>1){
				l1--;
				// row=3;
				
				
				dirr (l1,row,h );
				h--;
				if(h<0){
					h=7;
				}
				
			}
			
			
			//
			
			if(l3>1){
				l3--;
		// row =3;
				dirl (l3,row,h2 );
				h2++;
				if(h2>7){
					h2=0;
				}
				
			}
			
			
			
			if(l2==1 && l1>1){
           
		       v=row-1;
				column=7-j-1;
				if(column < 0){
					column=7;
				}
			
				}
		   
		  
			if(l2==1 && l3>1){
				v=row;
				column=7-j1+1;
				if(column >7){
					column = 0;
				}
	
				}
			if(l2!=length_snake){
				l2++;
			}
			
			

			
			dird(l2,column,v);
			//	_delay_ms(250);
			if(l2==length_snake){
				v++;
			}
			
			if(v>7){
				v=0;
			}
			
			
			
			
			
		}
		
		

		
		cond();
		
		if(lt==1){
			int row =1;
			if(l3!=length_snake){
				l3++;
			}
			
			dirl (l3,row,h2 );
			if(l3==length_snake){
				h2++;
			}
			if(h2>7){
				h2=0;
			}
		}
		
		
		
		cond();
		
		
		
		
		
		



		




		if(up==1){
			
		/*	int column=1;
			if(l4!=length_snake){
				l4++;
			}
			diru(l4,column,v1);
			if(l4==length_snake){
				v1--;
			}
			if(v1<0){
				v1=7;
			}*/
		if(l1!=0){
			l1--;
			row=3;
			
			
			dirr (l1,row,h );
			h--;
			if(h<0){
				h=7;
			}
			
		}
		if(l4==1 && l1>1){
			
			v1=row-1;
			column=7-j-1;
			if(column < 0){
				column=7;
			}
			
		}
		
		if(l4!=length_snake){
			l4++;
		}
		diru(l4,column,v1);
		if(l4==length_snake){
			v1--;
		}
		if(v1<0){
			v1=7;
			}
		
		
		
			
			
		}
		
		



		}
		
		
	}

}




























