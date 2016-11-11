#include "pixel_handler.h"
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

PixelHandler::PixelHandler(const char* uri, FlippieDevice f) : _uri(uri) {
   flippie = f;
}

bool PixelHandler::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }
   flippie.set_shift_register_and_fire(server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt());
   Serial.printf("set pixel => row=%u, module=%u, column=%u, state=%u\n", server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt());
   server.send(200, "text/html", "OK");
   return true;
}
