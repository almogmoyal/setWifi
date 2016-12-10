#ifndef SET_WiFi_h
#define SET_WiFi_h

#include <ESP8266WebServer.h>

class setWifiClass{
	
	private:
		const int MAX_SSID_LENGTH = 32;
		const int MAX_PASSWORD_LENGTH = 64;

	public:
		void setupWifi(char* default_ssid = "esp8266", char* default_password = "secret8266");
		void handleSetWifi(ESP8266WebServer* server);
		
};

extern setWifiClass setWifi;

#endif