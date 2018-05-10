#ifndef global_def_h
#define global_def_h

#include <Arduino.h>

#define LETTER_A 0
#define LETTER_B 1
#define LETTER_C 2
#define LETTER_D 3
#define LETTER_E 4
#define LETTER_F 5
#define LETTER_G 6
#define LETTER_H 7
#define LETTER_I 8
#define LETTER_J 9
#define LETTER_K 10
#define LETTER_L 11
#define LETTER_M 12
#define LETTER_N 13
#define LETTER_O 14
#define LETTER_P 15
#define LETTER_Q 16
#define LETTER_R 17
#define LETTER_S 18
#define LETTER_T 19
#define LETTER_U 20
#define LETTER_V 21
#define LETTER_W 22
#define LETTER_X 23
#define LETTER_Y 24
#define LETTER_Z 25

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