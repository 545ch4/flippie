#include "sr.h"
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

SrPage::SrPage(const char* uri, FlippieDevice f) : _uri(uri) {
   flippie = f;
}

bool SrPage::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }
   bool sent = false;
   if(server.hasArg("led")) {
     flippie.paint_leds(
       server.arg("led").toInt() == 1 && server.arg("state").toInt() == 1 ? 1 : 0,
       server.arg("led").toInt() == 2 && server.arg("state").toInt() == 1 ? 1 : 0,
       server.arg("led").toInt() == 3 && server.arg("state").toInt() == 1 ? 1 : 0
     );
   } else if(server.hasArg("fp2800a_addr")) {
     unsigned int addr = server.arg("fp2800a_addr").toInt();
     flippie.set_address(255 & addr);
   } else if(server.hasArg("fp2800a_column")) {
     flippie.set_column(server.arg("fp2800a_column").toInt());
   } else if(server.hasArg("fp2800a_column_code")) {
     flippie.set_column_code(server.arg("fp2800a_column_code").toInt(), server.arg("state").toInt());
   } else if(server.hasArg("fp2800a_enable")) {
     flippie.set_enable(server.arg("state").toInt());
   } else if(server.hasArg("fp2800a_data")) {
     flippie.set_data(server.arg("state").toInt());
   } else if(server.hasArg("fp2800a_row_set_plusvs")) {
     flippie.set_row(server.arg("fp2800a_row_set_plusvs").toInt());
   } else if(server.hasArg("fp2800a_row_set_gnd")) {
     flippie.rst_row(server.arg("fp2800a_row_set_gnd").toInt());
   } else if(server.hasArg("clear")) {
     flippie.clear_shift_register(false);
   } else {
     if(!sent) {
       Serial.printf("SR Unknown commane '%s'\n", server.argName(0).c_str());
       server.send(405, "text/html", "Unknown command");
     }
   }
   if(!sent) {
     Serial.printf("SR %s\n", server.argName(0).c_str());
     server.send(200, "text/html", "OK");
   }
   return true;
}
