/*
ledmatrix88 lib 0x01

copyright (c) Davide Gironi, 2013

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#ifndef LEDMATRIX88_H_
#define LEDMATRIX88_H_

//define led matrix columns and rows
#define LEDMATRIX88_COLS 8
#define LEDMATRIX88_ROWS 8

//setup led matrix columns port
//for port A for Niki
//A7 = column 0 from the left
//A6 = column 1 from the left
//A5 = column 2 from the left
//A4 = column 3 from the left
//A3 = column 4 from the left
//A2 = column 5 from the left
//A1 = column 6 from the left
//A0 = column 7 from the left

#if LEDMATRIX88_COLS >= 1
#define LEDMATRIX88_COL1_DDR DDRA // DDRC
#define LEDMATRIX88_COL1_PORT PORTA //PORTC
#define LEDMATRIX88_COL1_PINOUT PA7 //PC0
#endif
#if LEDMATRIX88_COLS >= 2
#define LEDMATRIX88_COL2_DDR DDRA //DDRC
#define LEDMATRIX88_COL2_PORT PORTA //PORTC
#define LEDMATRIX88_COL2_PINOUT PA6 //PC1 
#endif
#if LEDMATRIX88_COLS >= 3
#define LEDMATRIX88_COL3_DDR DDRA //DDRC
#define LEDMATRIX88_COL3_PORT PORTA //PORTC
#define LEDMATRIX88_COL3_PINOUT PA5 //PC2 
#endif
#if LEDMATRIX88_COLS >= 4
#define LEDMATRIX88_COL4_DDR DDRA //DDRC
#define LEDMATRIX88_COL4_PORT PORTA //PORTC
#define LEDMATRIX88_COL4_PINOUT PA4 //PC3 
#endif
#if LEDMATRIX88_COLS >= 5
#define LEDMATRIX88_COL5_DDR DDRA //DDRC
#define LEDMATRIX88_COL5_PORT PORTA //PORTC
#define LEDMATRIX88_COL5_PINOUT PA3 //PC4 
#endif
#if LEDMATRIX88_COLS >= 6
#define LEDMATRIX88_COL6_DDR DDRA //DDRD
#define LEDMATRIX88_COL6_PORT PORTA //PORTD
#define LEDMATRIX88_COL6_PINOUT PA2 //PC5 
#endif
#if LEDMATRIX88_COLS >= 7
#define LEDMATRIX88_COL7_DDR DDRA //DDRB
#define LEDMATRIX88_COL7_PORT PORTA //PORTB
#define LEDMATRIX88_COL7_PINOUT PA1 //PB1
#endif
#if LEDMATRIX88_COLS >= 8
#define LEDMATRIX88_COL8_DDR DDRA //DDRB
#define LEDMATRIX88_COL8_PORT PORTA //PORTB
#define LEDMATRIX88_COL8_PINOUT PA1 //PB2
#endif

//setup led matrix rows port

//for port C for Niki
//C7 = row 0 from the bottom
//C6 = row 1 from the bottom
//C5 = row 2 from the bottom
//C4 = row 3 from the bottom
//C3 = row 4 from the bottom
//C2 = row 5 from the bottom
//C1 = row 6 from the bottom
//C0 = row 7 from the bottom

#if LEDMATRIX88_ROWS >= 1
#define LEDMATRIX88_ROW1_DDR DDRC //DDRD
#define LEDMATRIX88_ROW1_PORT PORTC //PORTD
#define LEDMATRIX88_ROW1_PINOUT PC7 //PD0
#endif
#if LEDMATRIX88_ROWS >= 2
#define LEDMATRIX88_ROW2_DDR DDRC //DDRD
#define LEDMATRIX88_ROW2_PORT PORTC //PORTD
#define LEDMATRIX88_ROW2_PINOUT PC6 //PD2
#endif
#if LEDMATRIX88_ROWS >= 3
#define LEDMATRIX88_ROW3_DDR DDRC //DDRD
#define LEDMATRIX88_ROW3_PORT PORTC //PORTD
#define LEDMATRIX88_ROW3_PINOUT PC5 //PD3
#endif
#if LEDMATRIX88_ROWS >= 4
#define LEDMATRIX88_ROW4_DDR DDRC //DDRD
#define LEDMATRIX88_ROW4_PORT PORTC //PORTD
#define LEDMATRIX88_ROW4_PINOUT PC4 //PD4
#endif
#if LEDMATRIX88_ROWS >= 5
#define LEDMATRIX88_ROW5_DDR DDRC //DDRD
#define LEDMATRIX88_ROW5_PORT PORTC //PORTD
#define LEDMATRIX88_ROW5_PINOUT PC3 //PD5
#endif
#if LEDMATRIX88_ROWS >= 6
#define LEDMATRIX88_ROW6_DDR DDRC //DDRD
#define LEDMATRIX88_ROW6_PORT PORTC //PORTD
#define LEDMATRIX88_ROW6_PINOUT PC2 //PD6
#endif
#if LEDMATRIX88_ROWS >= 7
#define LEDMATRIX88_ROW7_DDR DDRC //DDRD
#define LEDMATRIX88_ROW7_PORT PORTC //PORTD
#define LEDMATRIX88_ROW7_PINOUT PC1 //PD7
#endif
#if LEDMATRIX88_ROWS >= 8
#define LEDMATRIX88_ROW8_DDR DDRC //DDRB
#define LEDMATRIX88_ROW8_PORT PORTC //PORTB
#define LEDMATRIX88_ROW8_PINOUT PC0 //PB0
#endif

//functions
extern void ledmatrix88_init();
extern uint8_t ledmatrix88_getcol();
extern uint8_t ledmatrix88_getrow();
extern void ledmatrix88_setcol(uint8_t col);
extern void ledmatrix88_setrow(uint8_t row);
extern void ledmatrix88_zero();
extern void ledmatrix88_print();

#endif

//fix point arithmetic
//input output issues
//concurrent/synchronous state machine design 





