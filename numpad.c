#include <msp430g2553.h>
#include <legacymsp430.h>
#include <stdint.h>

char keymap_char[16] = {'1', '2', '3', 'A',
						'4', '5', '6', 'B',
						'7', '8', '9', 'C',
						'*', '0', '#', 'D'};

uint32_t keymap_hex[16] = {0x0, 0x1, 0x2, 0x3,
						   0x4, 0x5, 0x6, 0x7,
						   0x8, 0x9, 0xA, 0xB,
						   0xC, 0xD, 0xE, 0xF};

void led_output(uint8_t bits);

int main(void)
{
	// Disable watch dog timer
	WDTCTL = WDTPW+WDTHOLD;

	// Set all pins as inputs
	// pins 0, 1, 2, 3 of port 1 read values from the rows of the numpads
	P1DIR = 0;
	P2DIR = 0;

	// Pins 0, 1, 2, 3 of port 2 feed into the columns of the numpad
	// pins 7, 6 of port 1 and pins 5 and 4 of port 2 feed the 4 LEDs
	P1DIR |= (BIT0 | BIT1 | BIT2 | BIT3 | BIT7 | BIT6);
	P2DIR |= (BIT4 | BIT5);

	// Set initial outputs values to 0
	P1OUT = 0;
	P2OUT = 0;

	uint32_t io_pins[4] = {BIT0, BIT1, BIT2, BIT3};

	while(1) {
		for(uint8_t row = 0; row < 4; row++)
		{
			P1OUT |= io_pins[row];
			for(uint8_t col = 0; col < 4; col++)
			{
				if(P2IN & io_pins[col])
				{
					led_output(keymap_hex[row*4+col]);
				}
			}
			P1OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);
		}
	}
}

void led_output(uint8_t bits)
{
	(bits & BIT0) ? (P1OUT |= BIT7) : (P1OUT &= ~BIT7);
	(bits & BIT1) ? (P1OUT |= BIT6) : (P1OUT &= ~BIT6);
	(bits & BIT2) ? (P2OUT |= BIT5) : (P2OUT &= ~BIT5);
	(bits & BIT3) ? (P2OUT |= BIT4) : (P2OUT &= ~BIT4);
}
