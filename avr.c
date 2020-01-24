/**
 * \file
 *
 * \brief Empty user application template
 *
 */
/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */
/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
//#include <asf.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 1000000UL //set the CPU frequency for delay function
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define BAUD 2400
#define MYUBRR F_CPU / 16 / BAUD - 1
#define BUFSIZE 10
uint8_t temp = 0;
volatile uint8_t portdhistory = 0xFF;
char receivedByte = 0;

void USART_Init(unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable receiver and transmitter */
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    /* Set frame format: 8data, 1stop bit (default) */
    UCSR0C |= (3 << UCSZ00); // data bits
}
void LED_Init()
{
    /* Set pins PC0..3 as outputs */
    DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3); //set DDRC PC0-3 to outputs
}
void PWM_Init()
{
    /* Set pins PD5..6 to outputs */
    DDRD |= (1 << DDD5) | (1 << DDD6);

    /* Enable Fast PWM (A1+B1) and inverting mode (A0+B0) */
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0);

    /* ? */
    TCCR0A |= (1 << WGM01) | (1 << WGM00);

    /* Set no prescaler */
    TCCR0B |= 0b00000001;

    /* Set start value of PWM, min */
    OCR0A = 0;
    OCR0B = 0;
}
int board_setup()
{
    LED_Init();
    PWM_Init();
    USART_Init(MYUBRR);

    // INTERRUPTS
    DDRD &= ~(1 << DDD2);
    DDRD &= ~(1 << DDD3);
    //SREG |= 0b10000000;
    PORTD |= ((1 << PD2) | (1 << PD3));
    PCICR |= (1 << PCIE2);                     // enable interrupt "group" 2 (pins 16-23)
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19); // enable pin change interrupts on PD2-3

    // GLOBAL INTERRUPTS
    sei();
    //cli();
    return 0; // enable global interrupts
}

ISR(PCINT2_vect)
{ //, ISR_BLOCK){

    uint8_t changedbits;
    changedbits = PIND ^ portdhistory;
    portdhistory = PIND;

    if (changedbits & (1 << PD2))
    { // PCINT18 changed
        temp = (PIND & (1 << PIND2)) == (PIND & (1 << PIND3));
        if (temp)
        { // PCINT18/A lagging behind -> CCW
            OCR0A -= 1;
            OCR0B -= 1;
        }
        else
        { // PCINT18/A leading -> CW
            OCR0A += 1;
            OCR0B += 1;
        }
    }
    if (changedbits & (1 << PD3))
    { // PCINT19 changed
        temp = (PIND & (1 << PIND2)) == (PIND & (1 << PIND3));
        if (temp)
        { // PCINT19/B lagging behind -> CW
            OCR0A += 1;
            OCR0B += 1;
        }
        else
        { // PCINT19/A leading -> CCW
            OCR0A -= 1;
            OCR0B -= 1;
        }
    }
}
unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return (UDR0);
}
char *USART_ReceiveString(void)
{
    static char input[BUFSIZE];
    uint8_t i;
    char c;

    for (i = 0; i < BUFSIZE - 1; i++)
    {
        c = USART_Receive();
        if (c == '\n')
            break;
        input[i] = c;
    }
    input[i + 1] = 0;
    return input;
}
void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}
void USART_TransmitString(const char *s)
{
    while (*s)
    {
        USART_Transmit(*s++);
    }
}
ISR(USART_RX_vect, ISR_BLOCK)
{

    char *s = USART_ReceiveString();
    USART_TransmitString(s);
}
int main(void)
{
    board_setup();

    while (1)
    {
    }
}