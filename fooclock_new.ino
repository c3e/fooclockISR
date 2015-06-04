#include <Time.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <TimerOne.h>

#include "functions.h"
#include "global_def.h"
#include "ntp.h"


void setup(){
	pinMode (OutputEnable, OUTPUT);
	pinMode (latchPin,     OUTPUT);
	pinMode (clockPin,     OUTPUT);
	pinMode (dataPin,      OUTPUT);

	analogWrite(OutputEnable,light_lvl_standard);

	Timer1.initialize(TIMERINTERVAL);		// initialize timer1, and set a 10 milli second period
	Timer1.attachInterrupt(updateDisplay);  // attaches callback() as a timer overflow interrupt

	Serial.begin(9600);

	while (Ethernet.begin(mac) == 0) {
		delay(5000);						// Wait for a valid IP-Address				
	}
	
	setupNTP();
	update_counter	= 0;						// Sync updates with NTP
	timestamp		= now();
	intervalpos		= timestamp % 70;
	phase_end		= millis();
	setup_done		= true;

};

void loop(){
	messageBuffer = init_udp_socket();
	animation_active = true;
	frame[0] = letters[messageBuffer[0]];
	delay(5000);
	animation_active = false;
}

void updateDisplay(){
	// ----- Manage Counter ----------
	// update_counter_max is defined as (1s/TIMERINTERVAL), therefor the update_counter is always reset after one second
	if(update_counter < update_counter_max){
		update_counter++;
	}
	else{
		update_counter	= 0;
		timestamp		= now();
		intervalpos		= timestamp % 70;
	}
	// ----- Check if device is "booting" ----
	if (!setup_done){
		//dots(5);
		spin(5,10);
	}
	// ----- All done, display time, date, binary time and so on ----
	else{

		if(intervalpos < 10){
			if( millis() > phase_end && intervalpos < 5){
				Serial.println("Interval 1, Animation start.");
				phase_end		= millis() + 10000;
				animation_end	= millis() + 1000;
			}
			updateDate(timestamp);

			if(millis() <= animation_end){
			//	combine(buffer);
			}
		}
		else if ( intervalpos > 10 && intervalpos < 20){
			
			if(millis() > phase_end && intervalpos < 15){
				Serial.println("Interval 2, Animation start.");
				phase_end		= millis() + 10000;
				animation_end	= millis() + 1000;
			}
			
			updateTime(timestamp);
			if(millis() <= animation_end){
			//	combine(buffer);
			}
		}
		else if ( intervalpos > 20 && intervalpos < 30){
			
			if(millis() > phase_end && intervalpos < 25){
				Serial.println("Interval 3, Animation start.");
				phase_end		= millis() + 10000;
				animation_end	= millis() + 1000;
			}
			updateBinaryTime(timestamp);
			if(millis() <= animation_end){
			//	combine(buffer);
			}
		}
		else if ( intervalpos > 40 && intervalpos < 50){

		}
		else{
			updateTime(timestamp);
		}
	}
	
	// ---- Copy Frame Buffer into Display Buffer unless an animation is active ---
	if(!animation_active){
		flush();
	}

	// ---- Shiftout the contents of the Display Buffer -- Don't forget this or you won't see anything!
	updateRegisters();
};
