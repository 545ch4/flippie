#include "flip_dot.h"
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

FlipDotPage::FlipDotPage(const char* uri, FlippieDevice f) : _uri(uri) {
   flippie = f;
}

bool FlipDotPage::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }
   bool sent = false;
   if(server.arg("task").equals("clear")) {
     flippie.clear();
   } else if(server.arg("task").equals("fill")) {
     flippie.fill();
   } else if(server.arg("task").equals("inverse")) {
     flippie.inverse();
   } else if(server.arg("task").equals("magnitize")) {
     flippie.magnetize(server.arg("duration").toInt());
   } else {
     if(!sent) {
       Serial.printf("FLIPDOT Unknown command '%s'\n", server.arg("task").c_str());
       server.send(500, "text/html", "Unknown command");
     }
   }
   if(!sent) {
     Serial.printf("FLIPDOT %s\n", server.arg("task").c_str());
     server.send(200, "text/html", "OK");
   }
   return true;
}
