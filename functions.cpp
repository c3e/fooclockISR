#include <Arduino.h>

#include "functions.h"
#include "global_def.h"


int				spinner_pos			= 0;
int				dot_pos				= 0;
int				update_counter		= 0;
int				time_passed			= 0;
bool			animation_active	= false;
unsigned long	animation_end		= 0;
int				animation_length	= 0;

int				intervalpos			= 0;
time_t			timestamp			= now();


// --------------------------------------- Date Functions ----------------------------------------- //
void updateDate(time_t t)
{
	buffer[0] = digits[(day(t)         /10)];
	buffer[1] = digits[(day(t)         %10)]+1;

	buffer[2] = digits[(month(t)       /10)];
	buffer[3] = digits[(month(t)       %10)]+1;

	buffer[4] = digits[((year(t)-2000) /10)];
	buffer[5] = digits[((year(t)-2000) %10)];
}

// --------------------------------------- Time Functions ----------------------------------------- //
void updateTime(time_t t)
{
	buffer[0] = digits[(hour(t)         /10)];
	buffer[1] = digits[(hour(t)         %10)];

	buffer[2] = digits[(minute(t)       /10)];
	buffer[3] = digits[(minute(t)       %10)];

	buffer[4] = digits[(second(t)		/10)];
	buffer[5] = digits[(second(t)		%10)];
}
void updateBinaryTime(time_t t)
{
	int digit;

	for(int digitCount = 0; digitCount < 6; digitCount++)
	{
		//digit zusammenbauen
		digit = 0;

		digit |= ((hour(t)   & (1 << digitCount))>>digitCount)<<2;
		digit |= ((minute(t) & (1 << digitCount))>>digitCount)<<4;
		digit |= ((second(t) & (1 << digitCount))>>digitCount)<<6;

		buffer[5-digitCount]= digit;
	}
}

// --------------------------------------- System Functions --------------------------------------- //
void spin(int digit, int speed)
{
	if(update_counter % speed == 0){
	if(spinner_pos >= 6)spinner_pos = 0;
	switch (spinner_pos){
		case  0: buffer[digit] =   4+1; break;
		case  1: buffer[digit] =   2; break;
		case  2: buffer[digit] =  32+1; break;
		case  3: buffer[digit] =  64; break;
		case  4: buffer[digit] = 128+1; break;
		case  5: buffer[digit] =   8; break;
		default: buffer[digit] =   0; break;
	}
	spinner_pos ++;
	}
};

void dots(int speed)
{
	if(update_counter % speed == 0){
		if(dot_pos >= 6){
			dot_pos = 0;
			buffer[5] = 0;
		}
		buffer[dot_pos] = 1;
		if(dot_pos > 0) buffer[dot_pos -1] = 0;
		dot_pos++;
	}
}

void updateRegisters()
{
	// take the latchPin low so
	// the LEDs don't flicker while you're sending in bits:
	digitalWrite(latchPin, LOW);

	for(int digitCount=5; digitCount>=0; digitCount--)
	{
		shiftOut(dataPin, clockPin, MSBFIRST, frame[digitCount]);
	}
	//take the latch pin high so the LEDs will light up again:
	digitalWrite(latchPin, HIGH);
}

void flush()
{
	for (int i = 0; i < 6; i++){
		frame[5-i] = buffer[i];
	}
}

// --------------------------------------- Animations --------------------------------------- //

void shift_right (int new_digit){
	for (int i= 5; i >= 1; i--){
		frame[i] = frame [i-1];
	}
	frame[0] = new_digit;
}

void combine(int* new_data){
	
	/*

	time = 0 ... 99

	combine(int* new_data, int* old_data, int time){
		int segments_to_animate = time*6/100;

		for(int i = 0; i != segments_to_animate; i++){
			frame[i] = fooo(new_data, old_data)
		}
	
	}

	*/


	static int i = 0;
	static int j = 0;

	if(time_passed == 0){
			j = 0;
			animation_active = true;
			animation_length = (int)(animation_end - millis());		
	}

	int animation_update = update_counter % (int)(floor((0.1*(float)(animation_length)) / 18));
	
	if(millis() >= animation_end-1){
		time_passed			= 0;
		animation_active	= false;
		return;
	} 
	else if(animation_update == 0){
		if( j < 18){
			/*
			Serial.print("i : ");
			Serial.print(i);
			Serial.print("  j :  ");
			Serial.println(j);
			*/

			if(j % 3 == 0){
				frame [5-i] |= new_data[i];
			}
			else if(j % 3 == 1){
				frame [5-i] &= ~buffer[i];
			}
			else{
				frame [5-i] = new_data[i];
				i++;
			}

			if(i == 6){	i = 0;}

			j++;	
		}
	}

	time_passed ++;

	//Serial.print("Animation_update: ");
	//Serial.println(animation_update);
	//Serial.print("Animation_End - Millis() = ");
	//Serial.println(animation_end - millis());
	//Serial.println(animation_active?("----->Animation_active:"):(""));
	
	
}

void tune_brightness(time_t timestamp)
{
	int light_lvl = predefined_light_lvls[(hour(timestamp))];
	
	analogWrite(OutputEnable, 255 - light_lvl);

}