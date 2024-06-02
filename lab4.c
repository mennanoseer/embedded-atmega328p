/* 1. Write a program that toggles PB5 every second (you can use the build in function _delay_ms(double)).*/

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL

int main(void)
{
    DDRB |= (1 << 5);
    while (1)
    {
        PORTB ^= (1 << 5);
        _delay_ms(1000);
    }
}

/*2. Connect a key to PC0. Check the key state. If the key is pressed,
toggle PB5 every second. Otherwise, turn it off.*/

int main(void)
{
    DDRB |= (1 << 5);
    DDRC &= ~0x1;
    while (1)
    {
        if (PINC & 0x1)
        {
            PORTB ^= (1 << 5);
        }
        else
        {
            PORTB &= ~(1 << 5);
        }
        _delay_ms(1000);
    }
}

/*3. Write a code to display numbers from 1 to 9 on seven segment
display with a delay of 1 sec between each number. Connect the
seven-segment display as shown in the figure:*/

const int digits[] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111};

int main(void)
{
    DDRD = 0xFF;
    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            PORTD = digits[i];
            _delay_ms(1000);
        }
    }
}