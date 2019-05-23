#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define SET_BIT(PORT, PIN) PORT |= (1<<PIN)
#define CLR_BIT(PORT, PIN) PORT &= ~(1<<PIN)

//Function prototype
void initADC();
uint16_t readADC(uint8_t ch);

int main(void)
{
    CLR_BIT(DDRC, PC0);
    CLR_BIT(DDRC, PC1);
    CLR_BIT(DDRC, PC2);
    CLR_BIT(DDRC, PC3);
    SET_BIT(DDRB, 5);
    initADC();
   
    while(1)
    {
         uint16_t a, b, c, d;
        a = readADC(0);
        _delay_ms(200);
        b = readADC(1);
        _delay_ms(200);
        c = readADC(2);
        _delay_ms(200);
        d = readADC(3);
        _delay_ms(200);
        if ((a < 30) || (b < 30) || (c < 30) || (d < 30))
        {
            SET_BIT(PORTB, 5);
            _delay_ms(200);
        }
        else
        {
            CLR_BIT(PORTB, 5);
            _delay_ms(200);
        }

    }
    return 0;
}

void initADC()
{
    ADMUX=(1<<REFS0);
    ADCSRA=(1<<ADEN)|(7<<ADPS0);
}

//ADC conversions
uint16_t readADC(uint8_t ch)
{
    ADMUX&=0xf8;
    ch=ch&0b00000111;
    ADMUX|=ch;

    ADCSRA|=(1<<ADSC);
    while(!(ADCSRA&(1<<ADIF)));
    ADCSRA|=(1<<ADIF);
    uint16_t TEMP=0;
    TEMP|=(ADCH<<8);
    TEMP|=(ADCL);
    return(TEMP);
}

