#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// left
#define IN1 PD1
#define IN2 PD2
#define ENA PB3

//right
#define IN3 PD3
#define IN4 PD4
#define ENB PD6

#define TRIG PD7
#define ECHO PB0 // ICP -> pin 8 on Arduino

volatile int overflow_count = 0;

void forward() {
	PORTD &= ~(1 << IN1);
	PORTD |= (1 << IN2);
	PORTD &= ~(1 << IN3);
	PORTD |= (1 << IN4);
}
void backward() {
	PORTD |= (1 << IN1);
	PORTD &= ~(1 << IN2);
	PORTD |= (1 << IN3);
	PORTD &= ~(1 << IN4);
}
void left() {
	PORTD |= (1 << IN1);
	PORTD &= ~(1 << IN2);
	PORTD &= ~(1 << IN3);
	PORTD |= (1 << IN4);
}
void right() {
	PORTD &= ~(1 << IN1);
	PORTD |= (1 << IN2);
	PORTD |= (1 << IN3);
	PORTD &= ~(1 << IN4);
}
void stop() {
	PORTD &= ~((1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4));
}

double falling_edge_routine() {
	TCNT1 = 0;
	TCCR1B = (1 << CS10); // no prescaling
	
	while ((TIFR1 & (1 << ICF1)) == 0); // Waits falling edge on ICF1

	long count = ICR1 + (65536 * overflow_count); // 2^16
	double distance = ((double) count / (16 * 1000000)) * 34300 / 2;

	overflow_count = 0;
	TIFR1 = (1 << ICF1);

	return distance;
}

int main(void) {
	DDRD |= (1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4);
	
	// right
	DDRD |= (1 << ENB);
	// clear OC0A on compare match when counting up, fast PWM
	TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	// prescaler 64
	TCCR0B = (1 << CS00)| (1 << CS01);
	OCR0A = 112;
	
	// left
	DDRB |= (1 << ENA);
	TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B = (1 << CS22); // prescaler 64
	OCR2A = 90;

	DDRD |= (1 << TRIG);
	DDRB &= ~(1 << ECHO);
	
	TCCR1A = 0; // normal mode
	TIMSK1 = (1 << TOIE1);
	
	sei();
	
	while (1) {
		// give 10us trigger pulse on trig. pin to HC-SR04
		PORTD |= (1 << TRIG);
		_delay_us(10);
		PORTD &= ~(1 << TRIG);
		
		double distance = falling_edge_routine();

		if (distance < 7) {
			stop();
			_delay_ms(250);
			backward();
			_delay_ms(250);
			right();
			_delay_ms(500);
		}
		
		else {
			forward();
		}
	}
}

ISR(TIMER1_OVF_vect) {
	overflow_count++;
}