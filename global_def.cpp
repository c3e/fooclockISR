#include "global_def.h"

// ---------------------------------- Definition of Global Variables -------------------------- //

bool setup_done = false;

int update_counter_max = 1000000 / TIMERINTERVAL;

extern unsigned long phase_end = 0;

bool messageReceived = false;

byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


// Pin connected to OE	  of 74HC595
int OutputEnable    = 3;

// Pin connected to ST_CP of 74HC595
int latchPin        = 4;

// Pin connected to SH_CP of 74HC595
int clockPin        = 2;

// Pin connected to DS    of 74HC595
int dataPin         = 5;


int predefined_light_lvls [24] = {
//    0,   1,   2,   3,   4,   5
	 40,  50,  60,  70,  80,  90,
//    6,   7,   8,   9,  10,  11,
	100, 110, 130, 150, 190, 250,
//   12,  13,  14,  15,  16,  17
	250, 190, 150, 130, 110, 100,
//	 18,  19,  20,  21,  22,  23
	 90,  80,  70,  60,  50,  40
};

//          4
//      /======\
//     ||      ||
//   8 ||      ||  2
//     ||  16  ||
//      >======<
//     ||      ||
// 128 ||      || 32
//     ||  64  ||
//      \======/ O  1

int digits[10] = {
	238, //0 0xEE
	34,  //1 0x22
	214, //2 0xD6
	118, //3 0x76
	58,  //4 0x3A
	124, //5 0x7C
	252, //6 0xFC
	38,  //7 0x26
	254, //8 0xFE
	126  //9 0x7E
};


const int letter [26] = {

	0xbe,	// 190, // A  
	0xf8,	// 248, // b
	0xcc,	// 204, // C
	0xf2,	// 242, // d 
	0xdc,	// 220, // E  
	0x9c,	// 156, // F  
	0x7e,	// 126, // g 
	0xb8,	// 184, // h 
	0x20,	// 32,  // i  
	0xe6,	// 230, // J  
	0xbe,	// 190, // k 
	0xc8,	// 200, // L 
	0xb0,	// 176, // m  
	0xb0,	// 176, // n  
	0xf0,	// 240, // o  
	0x9e,	// 158, // P  
	0xee,	// 238, // Q  
	0x90,	// 144, // r  
	0x7c,	// 124, // S  
	0xd8,	// 216, // t  
	0xe0,	// 224, // u  
	0xe0,	// 224, // v  
	0x1a,	// 26,  // w  
	0xba,	// 186, // X 
	0x3a,	// 58,  // y 
	0xd6	// 214, // Z
};

const int ascii_table [130] = {
	0x00,	// nul
	0x00,	// soh
	0x00,	// stx
	0x00,	// etx
	0x00,	// eot
	0x00,	// enq
	0x00,	// ack
	0x00,	// bel
	0x00,	// bs
	0x00,	// tab
	0x00,	// lf
	0x00,	// vt
	0x00,	// np
	0x00,	// cr
	0x00,	// so
	0x00,	// si
	0x00,	// dle
	0x00,	// dc1
	0x00,	// dc2
	0x00,	// dc3
	0x00,	// dc4
	0x00,	// nak
	0x00,	// syn
	0x00,	// etb
	0x00,	// can
	0x00,	// em
	0x00,	// eof
	0x00,	// esc
	0x00,	// fs
	0x00,	// gs
	0x00,	// rs
	0x00,	// us
	0x00,	// space
	0x23,	// !
	0x0A,	// "
	0xF0,	// #
	0x7C,	// $
	0x92,	// %
	0x00,	// &
	0x02,	// '
	0xcc,	// (
	0x66,	// )
	0x01,	// *
	0x01,	// +
	0x01,	// ,
	0x10,	// -
	0x01,	// .
	0x92,	// /
	0xee,	// 0
	0x22,	// 1
	0xd6,	// 2
	0x76,	// 3
	0x3a,	// 4
	0x7c,	// 5
	0xfc,	// 6
	0x26,	// 7
	0xfe,	// 8
	0x7e,	// 9
	0x50,	// :
	0x01,	// ;
	0x01,	// <
	0x01,	// =
	0x01,	// >
	0x97,	// ?
	0x01,	// @
	0xbe,	// A  
	0xf8,	// b
	0xcc,	// C
	0xf2,	// d 
	0xdc,	// E  
	0x9c,	// F  
	0x7e,	// g 
	0xb8,	// h 
	0x20,	// i  
	0xe6,	// J  
	0xbe,	// k 
	0xc8,	// L 
	0xb0,	// m  
	0xb0,	// n  
	0xf0,	// o  
	0x9e,	// P  
	0xee,	// Q  
	0x90,	// r  
	0x7c,	// S  
	0xd8,	// t  
	0xe0,	// u  
	0xe0,	// v  
	0x1a,	// w  
	0xba,	// X 
	0x7a,	// y 
	0xd6,	// Z
	0xcc,	// [
	0x38,	// backslash
	0x66,	// ]
	0x01,	// ^
	0x40,	// _
	0x08,	// `
	0xbe,	// A  
	0xf8,	// b
	0xcc,	// C
	0xf2,	// d 
	0xdc,	// E  
	0x9c,	// F  
	0x7e,	// g 
	0xb8,	// h 
	0x20,	// i  
	0xe6,	// J  
	0xbe,	// k 
	0xc8,	// L 
	0xb0,	// m  
	0xb0,	// n  
	0xf0,	// o  
	0x9e,	// P  
	0xee,	// Q  
	0x90,	// r  
	0x7c,	// S  
	0xd8,	// t  
	0xe0,	// u  
	0xe0,	// v  
	0x1a,	// w  
	0xba,	// X 
	0x7a,	// y 
	0xd6,	// Z
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

int buffer [6] = {
	letter[S],letter[T],letter[A],letter[R],letter[T],0 
};

int frame [6] = {
	0, 0, 0, 0, 0, 0
};
