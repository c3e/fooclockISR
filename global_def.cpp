#include "global_def.h"

// ---------------------------------- Definition of Global Variables -------------------------- //

bool setup_done = false;

int update_counter_max = 1000000 / TIMERINTERVAL;

extern unsigned long phase_end = 0;

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

int buffer [6] = {
	letter[S],letter[T],letter[A],letter[R],letter[T],0 
};

int frame [6] = {
	0, 0, 0, 0, 0, 0
};
