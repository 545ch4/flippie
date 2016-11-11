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
   Serial.begin(115200);
   Serial.println();
   Serial.println("Booting...");

   // TODO: What's the SSID of your WiFi?
   const char* ssid = "WIFI";
   // TODO: What's the PASSWORD of your WiFi?
   const char* password = "***********";
   // TODO: If you don't want to use DHCP, provide a static IP (and uncomment). Othewise leave this commented.
   // IPAddress ip(192, 168, 1, 23);
   // IPAddress gateway(192, 168, 1, 1);
   // IPAddress subnet(255, 255, 255, 0);
   // WiFi.config(ip, gateway, subnet);

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
