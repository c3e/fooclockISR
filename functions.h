#ifndef functions_h
#define functions_h

#include <Time.h>

extern int				spinner_pos;
extern int				update_counter;
extern int				intervalpos;
extern time_t			timestamp;
extern unsigned	long	animation_end;
extern bool				animation_active;

void updateDate			(time_t t);
void updateTime			(time_t t);
void updateBinaryTime	(time_t t);


void flush();

void clear_frame();

void combine			(int* new_data); 
void shift_right		(int new_digit);
void writeChaospott		();

void spin(int digit, int speed);
void dots(int speed);
void updateRegisters();

void tune_brightness(time_t timestamp);

#endif
