#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
    DDRB |= (1 << 5); // DDRB5 output
    DDRC = 0x00;      // PORTC input
    DDRD = 0xFF;      // PORTD output

    // 1000 Hz -> delay = 0.5 ms -> clocks = 8000 -> prescaled by 1/64 -> 125
    TCNT0 = 131;
    // normal mode, prescaler 64
    TCCR0A = 0x00;
    TCCR0B = 0x03;

    TIMSK0 = (1 << TOIE0);
    sei();

    while (1)
    {
        PORTD = PINC;
    }
}
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 131;
    PORTB ^= (1 << 5); // toggle PB5
}
