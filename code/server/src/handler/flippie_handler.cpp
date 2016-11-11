#include "flippie_handler.h"
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

FlippieHandler::FlippieHandler(const char* uri, FlippieDevice f) : _uri(uri) {
   flippie = f;
}

bool FlippieHandler::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }
   bool sent = false;
   if(server.hasArg("led")) {
      flippie.paint_leds(
         server.hasArg("led_a") && server.arg("led_a").toInt() == 1 ? 1 : 0,
         server.hasArg("led_b") && server.arg("led_b").toInt() == 1 ? 1 : 0,
         server.hasArg("led_c") && server.arg("led_c").toInt() == 1 ? 1 : 0
      );
   } else if(server.hasArg("addr")) {
      unsigned int addr = server.arg("addr").toInt();
      flippie.set_address(255 & addr);
   } else if(server.hasArg("column")) {
      flippie.set_column(server.arg("column").toInt());
   } else if(server.hasArg("enable")) {
      flippie.set_enable(server.arg("enable").toInt());
   } else if(server.hasArg("d")) {
      flippie.set_data(server.arg("d").toInt());
   } else if(server.hasArg("row_set")) {
      flippie.set_row(server.arg("row_set").toInt());
   } else if(server.hasArg("row_rst")) {
      flippie.rst_row(server.arg("row_rst").toInt());
   } else if(server.hasArg("clear")) {
      flippie.clear_shift_register(false);
   } else if(server.hasArg("get")) {
      server.send(200, "application/json", flippie.shift_register_as_string());
      sent = true;
   } else if(server.hasArg("task")) {
      if(server.arg("task").equals("clear")) {
         flippie.clear();
      } else if(server.arg("task").equals("fill")) {
         flippie.fill();
      } else if(server.arg("task").equals("inverse")) {
         flippie.inverse();
      } else if(server.arg("task").equals("magnetize")) {
         flippie.magnetize(server.arg("duration").toInt());
      } else {
         Serial.printf("SR Unknown task '%s'\n", server.arg("task").c_str());
         server.send(405, "text/html", "Unknown command");
      }
   } else {
      Serial.printf("SR Unknown command '%s'\n", server.argName(0).c_str());
      server.send(405, "text/html", "Unknown command");
   }
   if(!sent) {
      Serial.printf("SR %s\n", server.argName(0).c_str());
      server.send(200, "text/html", "OK");
   }
   return true;
}
