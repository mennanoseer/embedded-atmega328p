/*1. 1- An External square wave (From the Function Generator)
with an 100KHz Frequency used as an external Clock
source to the microcontroller, write a C program to
generate a 1000 Hz square wave on PORTB.5 with 50%
Duty cycle using Counter 0. Then make it 70% Duty cycle.*/


/* exteral sqwave = 100kHz, generate 1000 Hz
 * 50% duty cycle - delay = 0.5 ms
 * clocks = 100 * 10^3 * 0.5 * 10^-3 = 50 -> 256 - 50 = 206
 * 70% duty cycle -> delay = 0.3 ms
 * clocks = 100 * 10^3 * 0.3 * 10^-3 = 30 -> 256 - 30 = 226
 */

#include <avr/io.h>

void duty_delay(uint8_t delay)
{
    TCNT0 = delay;

    // Normal mode, external clock source on T0 pin, no prescaling
    TCCR0A = 0x00;
    TCCR0B = (1 << CS01) | (1 << CS00);

    while (!(TIFR0 & (1 << TOV0)));

    TIFR0 = (1 << TOV0);

    PORTB ^= (1 << 5);
}

int main()
{
    DDRB |= (1 << 5);
    PORTB &= ~(1 << 5); 

    while (1)
    {
        // 50% Duty cycle: high for 0.5 ms, low for 0.5 ms
        duty_delay(206); // High delay
        duty_delay(206); // Low delay

        // 70% duty cycle 
        /*
        duty_delay(186); // High delay for 70% duty cycle (0.7 ms)
        duty_delay(226); // Low delay for 30% duty cycle (0.3 ms)
        */
    }
}

/* 2. A square wave (from the Function generator) is connected
to an external interrupt and any time a L-to-H pulse comes
in, a single PORTB.5 is turned on, and any time a H-to-L
pulse comes in, the PORTB.5 is turn off. The rate of "On"
and "Off" is the same as the square wave frequency. Show
the input square wave and the output square wave on the
Oscilloscope.*/

#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
    DDRB |= (1 << 5);
    PORTB &= ~(1 << 5);

    EICRA = (1 << ISC00); // any logical change
    EIMSK = (1 << INT0);
    sei();

    while (1);
}

ISR(INT0_vect)
{
    PORTB ^= (1 << 5); 
    //EICRA ^= (1 << 0); // change from falling to rising and vice versa
}