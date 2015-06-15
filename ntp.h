#ifndef ntp_h
#define ntp_h

#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <Time.h>

extern IPAddress	timeServer;
extern const int	timeZone;
extern byte			messageBuffer[206];
extern boolean		ntp_update_active;

void	setupNTP			();
time_t	getNtpTime			();
void	sendNTPpacket		(IPAddress &address);


int		listenForMessages	();

#endif
