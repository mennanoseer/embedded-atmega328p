/*1. Write a C program using a Timer (Normal mode) to generate a 500 Hz square wave frequency on pin PORTC.2.
a. Then examine the frequency using the oscilloscope.
b. Modify the count value to make sure that the frequency is exactly 500 Hz.*/

/*
 * Square wave with frequency = 500 Hz, period = 2 ms, delay = 1 ms.
 * With avr frequency of 16 MHz
 * Number of ticks = 16 * 10^6 * 1 * 10^-3 = 16000
 * Prescaling by 1/64, number of ticks (prescaled) = 16000/64 = 250
 * Remaining to overflow = 0x100 - 250 = 0x100 - 0xFA = 0x6 <- TCNT0
 */

#include <avr/io.h>

int main(void)
{
    // set PC2 as output
    DDRC |= (1 << 2);
    PORTC &= ~(1 << 2);

    while (1)
    {
        // set the start value to count till overflow
        TCNT0 = 0x6;

        // normal mode
        TCCR0A = 0;

        // prescaling of 1/64
        TCCR0B = (1 << CS01) | (1 << CS00);

        // count till overflow
        while (!(TIFR0 & (1 << TOV0)))
        { }

        // stop counting
        TCCR0B = 0;

        // clear the overflow flag bit
        TIFR0 = 1 << TOV0;

        // toggle PC2
        PORTC ^= (1 << 2);
    }
}

/*2. Rewrite task 1, using the CTC mode with 1000Hz.*/

/*
 * Square wave with frequency = 1000 Hz, period = 1 ms, delay = 0.5 ms.
 * With avr frequency of 16 MHz
 * Number of ticks = 16 * 10^6 * 0.5 * 10^-3 = 8000
 * Prescaling by 1/64, number of ticks (prescaled) = 8000/64 = 125, OCR0A = 125 - 1 = 124
 * Formula: OCR0A = (F_CPU / (2 * N * DesiredFrequency)) - 1
 * For DesiredFrequency = 1000Hz and Prescaler N = 64 -> OCR0A = 124; // (16000000 / (2 * 64 * 1000)) - 1 = 124
 */

int main(void)
{
    // set PC2 as output
    DDRC |= (1 << 2);
    PORTC &= ~(1 << 2);

    while (1)
    {
        // set the start value to count till overflow
        TCNT0 = 0x00;
        OCR0A = 124;

        // CTC mode
        TCCR0A = (1 << WGM01);

        // prescaling of 1/64
        TCCR0B = (1 << CS01) | (1 << CS00);

        // wait for the compare match
        while ((TIFR0 & (1 << OCF0A)) == 0)
        {}

        // clear the compare match flag
        TIFR0 = 1 << OCF0A;

        // toggle PC2
        PORTC ^= (1 << 2);
    }
}

/*3. Connect a key to PORTD.4. Using Timer/Counter0, write a C program to output high PORTB.5, when the key is
pressed, 5 times then low when the key is pressed 3 times.*/

volatile uint8_t count = 0;

int main(void)
{
    DDRD &= ~(1 << PD4); 
    DDRB |= (1 << PB5);  

    PORTB &= ~(1 << PB5); 
    PORTD |= (1 << PD4);  

    TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);

    while (1)
    {
        // Check for rising edge on key press (assuming active low)
        if (!(PIND & (1 << PD4)))
        {
            while (!(PIND & (1 << PD4)))
            {
            } // Debounce 
            count++;
        }

        if (count >= 5)
        {
            PORTB |= (1 << PB5); 
            count = 0;   // reset counter for next cycle
        }
        else if (count >= 3)
        {
            PORTB &= ~(1 << PB5); 
        }
    }
    return 0;
}