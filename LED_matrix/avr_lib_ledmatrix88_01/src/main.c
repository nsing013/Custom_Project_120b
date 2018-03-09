#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

#include "ledmatrix88/ledmatrix88.h"

#define UART_BAUD_RATE 2400
#include "uart/uart.h"

void ledmatrix88_setvalue(uint16_t value) {
	//select column and row based on the passed value
	uint8_t colon = (uint8_t)((value-1)%LEDMATRIX88_COLS);
	uint8_t rowon = (uint8_t)((value-1)/LEDMATRIX88_ROWS);
	uint8_t colsel = (uint16_t)(pow(2,LEDMATRIX88_COLS)-1) & (uint16_t)(1<<colon);
	uint8_t rowsel = (uint16_t)(pow(2,LEDMATRIX88_ROWS)-1) & (uint16_t)(1<<rowon);

	char out[100];
	itoa(value, out, 10); uart_puts(out); uart_puts("-");
	itoa(colsel, out, 10); uart_puts(out); uart_puts("-");
	itoa(rowsel, out, 10); uart_puts(out); uart_puts("\r\n");

	ledmatrix88_setcol(colsel);
	ledmatrix88_setrow(rowsel);
}

int main(void) {
	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init ledmatrix
	ledmatrix88_init();

	//init interrupt
	sei();

	uint8_t i = 0;
	for(;;) {

		for(i=0; i<LEDMATRIX88_COLS*LEDMATRIX88_ROWS; i++) {
			ledmatrix88_setvalue(i+1);
			ledmatrix88_print();
			_delay_ms(500);
		}
	}
}
