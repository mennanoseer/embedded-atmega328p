/*1- Write a C program using Timer to generate a 1000 Hz
PWM signal (square wave) on PORTB.5 with 50% Duty
cycle, Using Polling (don’t Use Interrupt).
a. Then examine the frequency using the oscilloscope.
b. Make it 70% Duty cycle.
c. Make it 90% Duty cycle.
d. Make it 20% Duty cycle.*/

#include <avr/io.h>

void duty_delay(uint8_t delay) {
	TCNT0 = delay;
	
	TCCR0A = 0;
	TCCR0B = (1 << CS01) | (1 << CS00);
	
	while ((TIFR0 & (1 << TOV0)) == 0);
	
	TCCR0B = 0;
	TIFR0 = (1 << TOV0);
	PORTB ^= (1 << PORTB5);
}


int main(void) {
	DDRB |= (1<<PORTB5);
	PORTB |= (1<<PORTB5);
	uint8_t percent = 50;
	
	while (1) {
		uint8_t delay = 16000 / 64;
		uint8_t on_delay = ~(delay * percent / 100) + 1;
		uint8_t off_delay = ~(delay * (100-percent) / 100) + 1;

		duty_delay(on_delay);
		duty_delay(off_delay);
	}
}