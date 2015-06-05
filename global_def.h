#ifndef global_def_h
#define global_def_h

#include <Arduino.h>

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

#define UP		1
#define DOWN	2

#define light_lvl_standard	60
#define light_lvl_risen		255

// Timerinterval in microseconds (1 000 000 us = 1s)
#define TIMERINTERVAL 10000

// ---------------------------------- Definition of Global Variables -------------------------- //

extern int predefined_light_lvls [24];

extern bool setup_done;

extern int update_counter_max;

extern unsigned long phase_end;

extern byte mac[];

extern int OutputEnable;
extern int latchPin;
extern int clockPin;
extern int dataPin;

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

extern int digits[10];

extern const int letter [26]; 
extern const int ascii_table [130];

extern int frame [6];

extern int buffer [6];

#endif