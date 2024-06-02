/*Connect a Voltage Generator to one of the Analog Pins,
then read the input voltage, if Voltage greater than 2.5V
then Turn on Built in LED else turn it off.*/

#include <avr/io.h>

int main(void)

{

    DDRB |= (1 << PB5); // Set PB5 (built-in LED) as output

    ADCSRA |= (1 << ADEN); // ADC enable = 1 0 0 0 = 0x8 
    
    // prescaler with division factor 128 -> Freq = 16MHz / 128 = 125KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    ADMUX |= (1 << REFS0); // Vref from Vcc // 01, right-justified =0xC0

    while (1)

    {
        ADCSRA |= (1 << ADSC); // start conversion

        while (!(ADCSRA & (1 << ADIF))); // wait for conversion to finish

        // read ADC value (10-bit left-adjusted)
        uint16_t adc_value = ADCL;
        adc_value |= (ADCH << 8);

        //ADCSRA |= (1 << ADIF);

        float voltage = (adc_value * 5.0) / 1023.0;

        if (voltage > 2.5)
        {
            PORTB |= (1 << PB5); 
        else
        {
            PORTB &= ~(1 << PB5);
        }
    }
    }
}
