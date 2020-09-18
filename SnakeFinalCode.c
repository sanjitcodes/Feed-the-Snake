/*
 * atmega_snake_2darray.c
 *
 * Created: 14-09-2020 22:45:53
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>

static unsigned char x;
static int flag=0;
static int lt=0; static int rt=0; static int up=0; static int dn=0;
static int j,j1,j2,j3;
static int ex=0;
static int v1,r1;
static int s,q;
static int fl=0;
static int length=2;
static int stop=0;

int led[8][8] =
{
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
};

void USART_INIT(unsigned char ubrr)
{
	UBRRH=(unsigned char)(ubrr>>8);
	UBRRL=(unsigned char)(ubrr);
	
	UCSRB|=(1<<TXEN)|(1<<RXEN);
	UCSRC|=(3<<UCSZ0);
}

unsigned char USART_RECIEVE()
{
	if(!(UCSRA&(1<<RXC)))
	{
		return x;
	}
	else
	{
		return UDR;
	}
}

void out(int snake[8][8])
{
	for(int j=0;j<8;j++)
	{
		PORTB = 1<<j;
		PORTA = 0xFF;
		for(int i=0;i<8;i++)
		{
			if (snake[j][i]==1)
			{
				PORTA &= ~(1<<i);
			}
			else
			{
				PORTA |= 1<<i;
			}
		}
		_delay_ms(5);
	}
}




void food()
{
	s=rand()%6+1;
	q=rand()%6+1;
	if(led[s][q]==0)
	{
		led[s][q]=1;
		return 0;
	}
	else
	{
		food();
	}
	
}

void dirr(int l,int r1,int r2)
{
	int f=l;
	j=r2;
	int d;
	for( d=0;d<f;d++)
	{
		if(led[r1][j]==1&& d==f-1 && (r1!=s || j!=q))
		{
			stop=1;
			break;
		}
		else
		{
			led[r1][j]=1;
			j++;
			if(j>=7)
			{
			flag=1;
			}
		}
	}
	if(r1==s && j==q)
	{
		fl=1;
	}
}

void dird(int l,int c1,int c2)
{
	j2=c2;
	for(int d1=0;d1<l;d1++)
	{
		if(led[j2][c1]==1 && d1==l-1&& (j2!=s || c1!=q))
		{
			stop=1;
			break;
		}
		else
		{
			led[j2][c1]=1;
			j2++;
			if(j2>=7)
			{
			flag=1;
			}
		}
	}
	if(j2==s && c1==q)
	{
		fl=1;
	}
}


void diru(int l,int c1,int c2)
{
	j3=c2;
	for(int d1=0;d1<l;d1++)
	{
		if(led[j3][c1]==1 &&d1==l-1 && (j3!=s || c1!=q))
		{
			stop=1;
			break;
		}
		else
		{
			led[j3][c1]=1;
			j3--;
			if(j3<=0)
			{
			flag=1;
			}
		}
	}
	if(j3==s && c1==q)
	{
	     fl=1;
	}
}

void dirl (int l,int r1,int r2 )
{
	int f=l;
	j1=r2;
	int d;
	for( d=0;d<f;d++)
	{
		if(led[r1][j1]==1 &&d==f-1&& (r1!=s || j1!=q))
		{
			stop=1;
			break;
		}
		led[r1][j1]=1;
		j1--;
		if(j1<=0)
		{
			flag=1;
		}
	}
	if(r1==s && j1==q)
	{
		fl=1;
	}
}

void cond()
{
	x =  USART_RECIEVE();
	if(x=='4')
	{		
		ex=lt=1;
		rt=up=dn=0;
	}
	
	if(x=='3')
	{		
		ex=rt=1;
		lt=up=dn=0;
	}
	
	if(x=='1')
	{		
		ex=up=1;
		rt=lt=dn=0;
	}
	
	if(x=='2')
	{		
		ex=dn=1;
		rt=up=lt=0;
	}
}

int main(void)
{
	
	USART_INIT(6);
	
    DDRB = 0xff;
    DDRA = 0xff;
    DDRD = 0x00;
	
	int col=1;
	int row=1;
	int col1=1;
	int row1=1;
	int speed =0;
	int y;
	int l,r,u,d;
	l=r=u=d=0;
	int z=0;
	int t1=0;
	int k1,k2,k3,k4,k5,k6,k7,k8;	  
    int z9,z8,z7,z6;
	int l1,l2,l3,l4;
	l3=l4=l1=l2=0;
	int fs=0;
    while (1) 
    {
		count=0;
		
		if(flag==1)
		{
			break;
		}
		cond();
		if(bit_is_set(PIND,7))
		{
			speed++;
			if(speed==8)
			{
				if(ex==0)
				{
					l1=length;
					if(ex==0)
					{
						dirr (l1,row,col );
						col++;
						if(col>7)
						{
							col=0;
						}
					 if(fl==1)
					 {
						 fl=0;
						 food();
						 length++;
						 l1++;	
					 }  
				 }
			 }
			 
			 if(dn==1)
			 { 
				 if(l3>0)
				 {
					 l3=0;
					 l2=0;
					 l1=0;
					 l4=0;
					 k2=k6;
					 k1=j1;
				 }
				 
				 if(l1>0)
				 {
					  l3=0;
					  l2=0;
					  l1=0;
					  l4=0;
					  k1=j;
					  k2=row; 
				 }
				 if(l2!=length)
				 {
					 l2++;
				 }
				 dird(l2,k1,k2);
				 
				 if(l2==length)
				 {
					 k2++;
				 }
				 
				 if(k2>7)
				 {
					 k2=0;
				 }
				 if(fl==1)
				 {
					 food();
					 fl=0;
					 length++;
					 l2++;   
				 } 
			 }
			 
			 if(up==1)
			 {
				 if(l3>0)
				 {
					 l3=0;
					 l2=0;
					 l1=0;
					 l4=0;
					 k3=j1;
					 k4=k6;
				 }
				 
				 if(l1>0)
				 {
					 l3=0;
					 l2=0;
					 l1=0;
					 l4=0;
					 k3=j;
					 k4=row;
				 }
				 if(l4!=length)
				 {
					 l4++;
				 }
				 diru(l4,k3,k4);
				 if(l4==length)
				 {
					 k4--;
				 }
				 if(k4<0)
				 {
					 k4=7;
				 }
				 if(fl==1)
				 {
					   food();
					   fl=0;
					   length++;
					   l4++;
				} 
			 }
			 
			 if(lt==1)
			 {                           
				 if(l2>0)
				 {
					 l3=0;
					 l2=0;
					 l1=0;
					 l4=0;
					 k5=k1;
					 k6=j2;
				 }
				 
				 if(l4>0)
				 {
					  l3=0;
					  l2=0;
					  l1=0;
					  l4=0;
					 k5=k3;
					 k6=j3;
				 }
				 if(l3!=length)
				 {
					 l3++;
				 }
				 
				 dirl (l3,k6,k5);
				 if(l3==length)
				 {
					 k5--;
				 }
				 if(k5<0)
				 {
					 k5=7;
				 }
				 if(fl==1)
				 {
					   food();
					   fl=0;
					   length++;
					   l3++;
				}
			 }
			 
			 if(rt==1 && ex!=0  )
			 {	 
				 if(l2>0)
				 {
					  l3=0;
					  l2=0;
					  l1=0;
					  l4=0;	 
					  k7=k1;
					  k8=j2;
				 }
				 if(l4>0)
				 {
					  l3=0;
					  l2=0;
					  l1=0;
					  l4=0;	 
					  k7=k3;
					  k8=j3;
				 }
				 
				 if(l1!=length)
				 {
					 l1++;
				 }
			 dirr (l1,k8,k7 );
			
			 if(l1==length)
			 {
				 k7++;
			 }
			 if(k7>7)
			 {
				 k7=0;
			 }
			 if(fl==1)
			 {
				   food();
				   fl=0;
				   length++;
				   l1++;	 
			 }
	}
			 
}
	
	if(fs==0)
	{
		food();
		fs=1;
	}
	
	if(stop==1)
	{
		break;
	}	
		
		
		out(led);		//printing
		
		if(speed==15)
		{
			z9=z8=z7=z6=0;
			 
			speed=0;
			int fin;
			
			led[row1][col1]=0;
			
			if(row1>7)
			row1=0;
			if(row1<0)
			row1=7;
			if(col1>7)
			col1=0;
			if(col1<0)
			col1=7;
	
	
			if(col1<=6  && led[row1][col1+1]==1 &&((row1)!=s || (col1+1)!=q ))
			{
		
				z9=1;
				z8=z7=z6=0;
				
			}
			else if( col1>=1 && led[row1][col1-1]==1 &&( (row1) !=s || (col1-1)!=q))
			{
			
				z6=1;
				z8=z7=z9=0;
			}
		   	if(row1<=6  &&  led[row1+1][col1]==1 &&(  (row1+1) !=s || (col1)!=q)  )
			{
				z8=1;
				z9=z7=z6=0;
			}
			else if(row1>=1 &&  led[row1-1][col1]==1  &&  ((row1-1) !=s || (col1) !=q))
			{
				z7=1;
				z6=z8=z9=0;
			}
			
			if(col1==7 &&  z9+z8+z7+z6==0)
			{            
				col1++;
			}
			if(row1==7 && z9+z8+z7+z6==0)
			{
				row1++;
			}
			if(col1==0 && z9+z8+z7+z6==0)
			{
				col1--;
			}
			if(row1==0 && z9+z8+z7+z6==0)
			{
				row1--;
			}
			
			if(z9==1){
				col1++;
			}
			if(z8==1){
				row1++;
			}
			if(z7==1){
				row1--;
			}
			if(z6==1){
				col1--;
			}	
		}
	}		
  }
}