/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 5/7/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 11.059200 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16a.h>
#include <stdio.h>
#include <delay.h>
#include <eeprom.h>

// Declare your global variables here

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);	
		j++;
	}
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
   unsigned int codeLength = 0;
   unsigned char flag = 0; 
   char charCodeLength = 0;
   char d; 
   int digit = 0;
   int a = 0; 
   int b = 0;  
   int temp;
   char charDigit;
   TCNT1 = 0x01;
   while((PIND&(1<<PIND2)) == 0) {
         if(TCNT1 == 0) {
            flag = 1;
            break;
         }
   }            
   PORTA = (0<<PORTA0);
   if(flag)
        UART_SendString("Entered Programming Mode \r\r");
   while((PIND&(1<<PIND2)) == 0) {
        if ((PINC&(1<<PINC0)) == 0) {  
            UART_SendString("Recieved Digit "); 
            codeLength++; 
            temp = codeLength;
            eeprom_write_byte(100, codeLength);
            if(codeLength > 9) {  
                a = temp%10;
                temp = temp/10;
                b = temp;
                charCodeLength = b+'0';
                UART_TxChar(charCodeLength);
                charCodeLength = a+'0'; 
                UART_TxChar(charCodeLength);
            }  
            else {
                charCodeLength = codeLength+'0';
                UART_TxChar(charCodeLength);  
            }
            d = !(PINB&(1<<PINB0))+'0'; 
            if(d == '1')
                digit += 1;  
            d = !(PINB&(1<<PINB1))+'0'; 
            if(d == '1')
                digit += 2;   
            d = !(PINB&(1<<PINB2))+'0'; 
            if(d == '1')
                digit += 4; 
            d = !(PINB&(1<<PINB3))+'0'; 
            if(d == '1')
                digit += 8; 
            if(digit == 10) {  
                digit = 0;
            }
            UART_SendString("\r");
            charDigit = digit+'0';
            UART_SendString("Code digit = ");
            UART_TxChar(charDigit);
            UART_SendString("\r\r"); 
            eeprom_write_byte(100+codeLength, digit);
            digit = 0; 
            delay_ms(1000);
        }   
   }
   PORTA = !(0<<PORTA0);
}

void main(void)
{
unsigned int codeLength;
unsigned int i = 1;
char d; 
int digit = 0; 
char charDigit;

// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=Out 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=1 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (1<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (1<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (1<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=P Bit1=T Bit0=P 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (1<<PORTD2) | (0<<PORTD1) | (1<<PORTD0);

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 10.800 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 2 s
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x54;
OCR1AL=0x5F;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x47;

// Global enable interrupts
#asm("sei")
UART_SendString("Door Lock\r\r");    

    while(1)
    {       
        codeLength = eeprom_read_byte(100);
       if ((PINC&(1<<PINC0)) == 0) {  
            UART_SendString("Recieved Digit "); 
            d = !(PINB&(1<<PINB0))+'0'; 
            if(d == '1')
                digit += 1;  
            d = !(PINB&(1<<PINB1))+'0'; 
            if(d == '1')
                digit += 2;   
            d = !(PINB&(1<<PINB2))+'0'; 
            if(d == '1')
                digit += 4; 
            d = !(PINB&(1<<PINB3))+'0'; 
            if(d == '1')
                digit += 8;
            if(digit == 10) {  
                digit = 0;
            }       
            UART_SendString("\r");
            charDigit = digit+'0';
            UART_SendString("Code digit = ");
            UART_TxChar(charDigit);
            UART_SendString("\r\r"); 
            if(digit == eeprom_read_byte(100+i)){ 
                i++;
            }
            else {  
                i = 1;
                PORTC = (0<<PORTC1);
                delay_ms(1000);
                PORTC |= (1<<PORTC1);
                UART_SendString("Error\r\r");
                delay_ms(1000);
            }
            if(i == codeLength+1) { 
                PORTB = (0<<PORTB4);
                delay_ms(1000);
                PORTB |= (1<<PORTB4);
                UART_SendString("Success\r\r");
                delay_ms(1000); 
                i = 1;   
                PORTD = (1<<PORTD2);
            }
            digit = 0; 
            delay_ms(1000);
        } 
    }
}
