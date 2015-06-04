#ifndef ntp_h
#define ntp_h

#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <Time.h>

extern IPAddress timeServer;
extern const int timeZone;     

void	setupNTP();
time_t	getNtpTime();
void	sendNTPpacket(IPAddress &address);

#endif
