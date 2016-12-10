#include <Arduino.h>
#include <setWifi.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

void setWifiClass::setupWifi(char* default_ssid, char* default_password){
	char ssid[MAX_SSID_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
	bool wifi_connected = false;
  
	File ssid_file = SPIFFS.open("/ssid_file", "r");
	File password_file = SPIFFS.open("/wifi_password", "r");
		
	if (ssid_file && password_file){
		if (ssid_file.size() <= MAX_SSID_LENGTH && password_file.size() <= MAX_PASSWORD_LENGTH ) {
			// Read ssid and password from the files
			ssid_file.readBytes(ssid, ssid_file.size());
			password_file.readBytes(password, password_file.size());
  
			WiFi.begin(ssid, password);
  
			// Wait for connection
			while (WiFi.status() == WL_IDLE_STATUS) {
				delay(500);
			}
  
			if (WiFi.status() == WL_CONNECTED){
				wifi_connected = true;
			}
		}  
	}
	
	 if (!wifi_connected){
		WiFi.mode(WIFI_AP);
		WiFi.softAP(default_ssid, default_password);
	}
}

void setWifiClass::handleSetWifi(ESP8266WebServer* server){
	File wifi_page = SPIFFS.open("/wifi.html", "r");
	
	if (!wifi_page){
		server->send(404, "text/plain", "Missing wifi.html file.");
		return;
	}
		
	if (server->args() == 2 &&  server->hasArg("wifi") && server->hasArg("password")){
		server->send(200, "text/plain", "Got Arguments.");
		return;
	} 
	
	server->streamFile(wifi_page, "text/html");
	wifi_page.close();
}

setWifiClass setWifi;