#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "flippie.h"
#include "flippie_device.h"
#include "flippie_server.h"
#include "functions.h"

const char* host = "flippie";
const char* ssid = "WIFI";
const char* password = "***********";

ESP8266WebServer server(80);
MDNSResponder mdns;
FlippieServer flippie_server;

void setup(void){
  ESP.wdtEnable(WDTO_8S);
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


  if (mdns.begin("flippie", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  flippie_server.init(server);
  server.begin();
  mdns.addService("http", "tcp", 80);

  Serial.printf("Ready! Open http://%s in your browser\n", WiFi.localIP().toString().c_str());
  Serial.print("\n");
}

void loop(void){
  ESP.wdtEnable(WDTO_8S);
  server.handleClient();
}
