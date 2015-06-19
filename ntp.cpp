#include "ntp.h"

// NTP Servers:
IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov


//const int timeZone = 1;     // Central European Time
const int timeZone = 2;     // Central European Time (summertime)

//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)


EthernetUDP Udp;

unsigned int localPort		= 8888;  // local port to listen for UDP packets



const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
boolean ntp_packet_received = false;
boolean ntp_update_active	= false;


EthernetUDP message_socket;
byte messageBuffer[206];

EthernetServer server(2342);


void setupNTP()
{
	Udp.begin(localPort);
	setSyncInterval(3600);
	setSyncProvider(getNtpTime);
}

int listenForMessages()
{
	if(ntp_packet_received){
		server.begin();
		ntp_packet_received = false;
	}

	int messageCharCounter = 0;

	EthernetClient client = server.available();
	if (client){
#ifdef DEBUG
		Serial.println("New client.");
#endif
		while (client.connected())
		{
			if(client.available()){
				char c = client.read();
#ifdef DEBUG
				Serial.write(c);
#endif
				messageBuffer[messageCharCounter] = c;
				messageCharCounter ++;
				if (c == '\n')
				{
					break;
				}
				if(messageCharCounter >= 201){
					messageCharCounter = 200;
					client.println("\n Message too long! Will only print the first 200 characters.");
					break;
				}
				
			}
		}

		messageBuffer[messageCharCounter] = 0;
#ifdef DEBUG
		Serial.print("Message length: ");
		Serial.println(messageCharCounter-1);
#endif
		client.println("\n Writing your message to the Board. \n Please be patient ...");
		delay(10);
		client.stop();
	}
	
	return messageCharCounter;
}

time_t getNtpTime()
{
	ntp_update_active = true;
	while (Udp.parsePacket() > 0) ; // discard any previously received packets
	//Serial.println("Transmit NTP Request");
	sendNTPpacket(timeServer);
	uint32_t beginWait = millis();
	while (millis() - beginWait < 1500) {
		int size = Udp.parsePacket();
		if (size >= NTP_PACKET_SIZE) {
#ifdef DEBUG
			Serial.println("Receive NTP Response");
#endif
			Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
			unsigned long secsSince1900;
			// convert four bytes starting at location 40 to a long integer
			secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
			secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
			secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
			secsSince1900 |= (unsigned long)packetBuffer[43];

			ntp_update_active = false;
			ntp_packet_received = true;

			return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
			
		}
	}
	//Serial.println("No NTP Response :-(");
	ntp_packet_received = true;
	return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0]   = 0xE3;   // LI, Version, Mode
	packetBuffer[1]   = 0;     // Stratum, or type of clock
	packetBuffer[2]   = 6;     // Polling Interval
	packetBuffer[3]   = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12]  = 49;
	packetBuffer[13]  = 0x4E;
	packetBuffer[14]  = 49;
	packetBuffer[15]  = 52;
	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	Udp.beginPacket(address, 123); //NTP requests are to port 123
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	Udp.endPacket();
}