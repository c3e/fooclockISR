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

	analogWrite(OutputEnable,255-light_lvl_standard);

	Timer1.initialize(TIMERINTERVAL);		// initialize timer1, and set a 10 milli second period
	Timer1.attachInterrupt(updateDisplay);  // attaches callback() as a timer overflow interrupt

	memset(messageBuffer,0,206);

	Serial.begin(9600);

	while (Ethernet.begin(mac) == 0) {
		delay(5000);						// Wait for a valid IP-Address				
	}
	
	setupNTP();
	update_counter	= 0;						// Sync updates with NTP
	timestamp		= now();
	intervalpos		= timestamp % 70;
	phase_end		= millis();

	Serial.print("My IP-Adress is: ");
	Serial.println(Ethernet.localIP());
	setup_done		= true;

};

void loop(){
	int len = init_udp_socket();
	animation_active = true;
	Serial.print("Message Buffer: ");
	Serial.println(messageBuffer[0]);
	
	clear_frame();

	for(int i = 0; i < len + 5 ; i ++){
		shift_right(ascii_table[messageBuffer[i]]);
		delay(500);
	}
	
	animation_active = false;
	memset(messageBuffer,0,206);


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
		dots(5);
		//spin(5,10);
	}
	// ----- All done, display time, date, binary time and so on ----
	else{

		if(intervalpos < 10){
			
			updateDate(timestamp);

		}
		else if ( intervalpos > 10 && intervalpos < 20){
			
			updateTime(timestamp);
			
		}
		else if ( intervalpos > 20 && intervalpos < 30){
			
			updateBinaryTime(timestamp);
			
		}
		else if ( intervalpos > 40 && intervalpos < 50){
			updateDate(timestamp);
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

	tune_brightness(timestamp);

};
