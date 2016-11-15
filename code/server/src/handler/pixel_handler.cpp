#include "pixel_handler.h"
#include "../flippie.h"
#include "../flippie.h"
#include <ESP8266WebServer.h>

PixelHandler::PixelHandler(Flippie* f) {
   flippie = f;
}

bool PixelHandler::handle(ESP8266WebServer& server, HTTPMethod method, String uri) {
   if(!canHandle(method, uri)) {
      return false;
   }

   if(method == HTTP_POST) {
      if(flippie->config->verbose)
         Serial.printf("set pixel => row=%u, module=%u, column=%u, state=%u\n", server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt());
      flippie->set_dot(server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt());
      server.send(200, "application/json", "true");
   } else if(method == HTTP_GET) {
      server.send(200, "application/json", flippie->get_dot(server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt()) == 1 ? "1" : "0");
   } else {
      return false;
   }
   return true;
}

bool PixelHandler::canHandle(HTTPMethod method, String uri) {
   if(uri == "/pixel" && server.hasArg("r") && server.hasArg("m") && server.hasArg("c") && (method == HTTP_GET || (method == HTTP_POST && server.hasArg("state")))) {
      return true;
   }
   return false;
}
