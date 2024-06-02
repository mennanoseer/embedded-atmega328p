/*1.Write a C program for the AVR to transfer the char
‘00000010’ serially using UART at 9600 baud,
continuously. Use 8-bit data and 1 stop bit, and show
the output on the Oscilloscope using trigger mode.*/

#include <avr/io.h>
void usart_init (void){
	UCSR0B = (1<<TXEN0); // transmit enable
	UCSR0C = (1<<UCSZ01) | (1<< UCSZ00); // 8 bit char size
	UBRR0L = 103; //baud rate = 9600bps
}

void usart_send(unsigned char ch) {
	while (!(UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty // TXC0
	UDR0 = ch;
}

int main(void)
{
    usart_init();
    while (1) 
    {
		usart_send(0x2); //transmit 00000010
		
    }
	return 0;
}

/*2.Write a C program for the AVR to transfer the char
‘00000010’ serially using SPI, continuously, and
show the output on the Oscilloscope using trigger mode.*/

#define MOSI 3 //PB3
#define SCK 5  //PB5

int main (void){
	DDRB = (1<<MOSI) | (1<<SCK)|; // output
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0); //enable SPI
	while(1) {
		SPDR = 0x2;
		while(!(SPSR &(1<<SPIF)));
    _delay_ms(100);
	}
	return 0;
}

//3. PWM Peripheral to generate a 1000 Hz PWM signal with 70% Duty cycle.

int main (void){
	DDRD |= (1<<6); //OC0A
	TCCR0A = (1<<COM0A1) | (1<< WGM01) | (1<<WGM00);
	TCCR0B = (1<<CS00) | (1<<CS01); // prescaler = 64

  OCR0A = 179; // 70/100 * 256 - 1 = 178.2 = 179
  while(1){}
}
