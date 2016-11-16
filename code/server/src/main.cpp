#include "debug.h"
#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include "flippie_server.h"
#include "../lib/functions.h"

//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

ESP8266WebServer* server;

void setup(void){
   Serial.begin(74880);
   Serial.println();
   Serial.println("Booting...");

   // TODO: What's the SSID of your WiFi?
   const char* ssid = "network";
   // TODO: What's the PASSWORD of your WiFi?
   const char* password = "forensicgenetics";
   // TODO: If you don't want to use DHCP, provide a static IP (and uncomment). Othewise leave this commented.

   //IPAddress ip(192, 168, 1, 250);
   //IPAddress gateway(192, 168, 1, 1);
   //IPAddress subnet(255, 255, 255, 0);
   //WiFi.config(ip, gateway, subnet);

   WiFi.mode(WIFI_AP_STA);
   WiFi.begin(ssid, password);
   //WiFi.mode(WIFI_AP);
   //WiFi.softAP(ssid, password);

   // Wait for connection
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
   Serial.printf("\nConnected to '%s'\n", ssid);
   Serial.printf("IP address: '%s'\n", WiFi.localIP().toString().c_str());
//   timeClient.begin();
//   timeClient.update();
//   Serial.printf("Got new time '%s'\n", timeClient.getFormattedTime().c_str());

//   MDNSResponder mdns;
//   if (mdns.begin("flippie", WiFi.localIP())) {
//      Serial.println("MDNS responder started");
//   }

   server = new ESP8266WebServer(80);
   FlippieServer* flippie_server = new FlippieServer(server);
   server->begin();
//   mdns.addService("http", "tcp", 80);

   Serial.printf("Ready! Open http://%s in your browser\n\n", WiFi.localIP().toString().c_str());
}

void loop(void){
   server->handleClient();
//   Serial.printf(".");
}
