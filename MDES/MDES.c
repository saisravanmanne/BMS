/********************************************************************************
Includes
********************************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/********************************************************************************
Macros and Defines
********************************************************************************/
#define F_CPU 8000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/********************************************************************************
Function Prototypes
********************************************************************************/
void usart_init(uint16_t ubrr);
char usart_getchar( void );
void usart_putchar( char data );
void usart_pstr(char *s);
unsigned char usart_kbhit(void);
int usart_putchar_printf(char var, FILE *stream);
uint16_t readADC(uint8_t ch);
int v4,v5;
int i4,i5;
/********************************************************************************
Global Variables
********************************************************************************/
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);
int d1=4,d2=0,d3=1,d4=8;
int c,c1,cur2,cur;


/********************************************************************************
Main
********************************************************************************/
int main( void ) {
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
	DDRD=0b11010000;
	PORTD=0b00001101;
	DDRB=0b00000000;
	PORTB=0b00000111;
	MCUCR&=((~(1<<ISC11))&(~(1<<ISC10))); //interrupt
	GICR|=1<<INT0;     //setting interrupt 1 and 0
	GICR|=1<<INT1;
	GICR|=1<<INT2;
	MCUCR&=((~(1<<ISC01))&(~(1<<ISC00)));  // lowlevel activates them
	MCUCSR&=((~(1<<ISC2)));
	sei();
	// define some local variables
	int myvalue;
   
	// setup our stdio stream
	stdout = &mystdout;

	// fire up the usart
	usart_init ( MYUBRR );
	printf("           WELCOME\n");
	printf("SMART BATTERY MANAGEMENT SYSTEM\n");
	printf("set the voltage and current limt\n");

	// dump some strings to the screen at power on
	myvalue = 64.45;
	//printf("Here is myvalue as an unsigned integer: %d\n", myvalue);
	//printf("Here is myvalue as a char: %c\n", myvalue);
	//printf("Here is myvalue in hex: 0x%X\n", myvalue);
	//printf("Here is myvalue in octal: %o\n", myvalue);
int c=5;
uint16_t cat,rat,mat;

	c1=0;
	// main loop
while(1)
{
	int v=(10*d1)+d2;
	int v2=v*(1024/42.9);
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
cat=readADC(0b00000010);
_delay_ms(262);
cur=readADC(0b00000011);
rat=readADC(0b00000111);

cur2=rat-cur;
mat=rat-cat;
//printf("setvoltage %d.%d  v2= %d  battery voltage %d\n",d1,d2,v2,mat);
uint16_t v3=(mat*4.29/1024)*100;
 v4=mat*4.29/1024;
v5=v3-v4*100;
cur2=cur2*10/2;
uint16_t i3=(cur2*4.29/1024)*10;
cur2=cur2/10;
i4=cur2*4.29/1024;
i5=i3-i4*100;
//printf("battery voltage %d.%d\n",v4,v5);	
	//mat=rat-cat;
	//printf(" adc readings %d\n",cat);

_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);

//while(mat>=v2)
//{
	//int v=(10*d1)+d2;
	//int v2=v*(1024/42.9);
	//printf(" adc readings %d %d %d\n",cat,rat,mat);

	//printf("inside %d\n",v2);
	//printf("***battery charged****\n");
	//PORTD^=1<<7;
	//_delay_ms(262);
	//delay_ms(262);
	//_delay_ms(262);
//}	
}
}
ISR(INT0_vect)
{
	
	
if(bit_is_set(PIND,7))
{
	printf("voltage limit=%d.%d\n",d1,d2);

d2=d2+1;
if(d2==9)
{
	d2=0;
	d1=d1+1;
}
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
}
if(bit_is_clear(PIND,7))
{
	printf("current limit %d.%d\n",d3,d4);
	d4=d4+1;
	if(d4==9)
	{
		d4=0;
		d3=d3+1;
	}
	_delay_ms(262);
	_delay_ms(262);
	_delay_ms(262);
	_delay_ms(262);
	_delay_ms(262);
	
}


}
ISR(INT1_vect)
{
	if(bit_is_set(PIND,7))
	{
		
	if(d2==0)
	{
		d2=9;
		d1=d1-1;
	}
if(c==0)
{
	printf("voltage limit=%d.%d\n",d1,d2);
}
d2=d2-1;

_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
_delay_ms(262);
	}
	if(bit_is_clear(PIND,7))
	{
		
		if(d4==0)
		{
			d4=9;
			d3=d3-1;
		}
		if(c==0)
		{
			printf("current limit=%d.%d\n",d3,d4);
		}
		d4=d4-1;

		_delay_ms(262);
		_delay_ms(262);
		_delay_ms(262);
		_delay_ms(262);
		_delay_ms(262);
	}
	
}
ISR(INT2_vect)
{
	printf("set voltage %d.%d\n",d1,d2);
	printf("battery voltage %d.%d\n",v4,v5);
	printf("battery current %d.%d\n",i4,i5);
	//printf("cur2 %d  %d\n",cur2,cur);
	_delay_ms(262);
	_delay_ms(262);
	_delay_ms(262);
	_delay_ms(262);
	_delay_ms(262);
	
}
/********************************************************************************
usart Related
********************************************************************************/
void usart_init( uint16_t ubrr) {
	// Set baud rate
	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL = (uint8_t)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set frame format: 8data, 1stop bit
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void usart_putchar(char data) 
{
	// Wait for empty transmit buffer
	while ( !(UCSRA & (_BV(UDRE))) );
	// Start transmission
	UDR = data;
}

char usart_getchar(void) {
	// Wait for incoming data
	while ( !(UCSRA & (_BV(RXC))) );
	// Return the data
	return UDR;
}

unsigned char usart_kbhit(void) {
	//return nonzero if char waiting polled version
	unsigned char b;
	b=0;
	if(UCSRA & (1<<RXC)) b=1;
	return b;
}

void usart_pstr(char *s) {
	// loop through entire string
	while (*s) {
		usart_putchar(*s);
		s++;
	}
}

// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream)
 {
	// translate \n to \r for br@y++ terminal
	if (var == '\n') usart_putchar('\r');
	usart_putchar(var);
	return 0;
}
uint16_t readADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);
	
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	return(ADC);
}