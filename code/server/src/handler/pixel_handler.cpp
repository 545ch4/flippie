#include "pixel_handler.h"

PixelHandler::PixelHandler(Flippie* f) {
   flippie = f;
}

bool PixelHandler::handle(ESP8266WebServer& server, HTTPMethod method, String uri) {
   Serial.printf("PIXEL!\n");
   if(!canHandle(method, uri) || !server.hasArg("r") || !server.hasArg("m") || !server.hasArg("c")) {
      return false;
   }

   if(method == HTTP_POST && server.hasArg("state")) {
      if(flippie->config->verbose)
         Serial.printf("set pixel => row=%u, module=%u, column=%u, state=%l\n", server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt());
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
   if(uri == "/pixel" && (method == HTTP_GET || method == HTTP_POST)) {
      return true;
   }
   return false;
}
