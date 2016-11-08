#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "flippie_device.h"
#include "flippie_server.h"
#include "../lib/functions.h"

ESP8266WebServer server;

void setup(void){
   const char* host = "flippie";
   const char* ssid = "WIFI";
   const char* password = "***********";

   Serial.begin(115200);
   Serial.println();
   Serial.println("Booting...");

   WiFi.mode(WIFI_AP_STA);
   WiFi.begin(ssid, password);

   // Wait for connection
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
   Serial.println("");
   Serial.print("Connected to ");
   Serial.println(ssid);
   Serial.print("IP address: ");
   Serial.println(WiFi.localIP());


   MDNSResponder mdns;
   if (mdns.begin("flippie", WiFi.localIP())) {
      Serial.println("MDNS responder started");
   }

   ESP8266WebServer server(80);

   FlippieServer flippie_server(server);
   server.begin();
   mdns.addService("http", "tcp", 80);

   Serial.printf("Ready! Open http://%s in your browser\n", WiFi.localIP().toString().c_str());
   Serial.print("\n");
}

void loop(void){
   server.handleClient();
}
