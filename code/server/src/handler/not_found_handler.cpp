#include "not_found_handler.h"

NotFoundHandler::NotFoundHandler(Flippie* f) {
   flippie = f;
}

bool NotFoundHandler::handle(ESP8266WebServer& server, HTTPMethod method, String uri) {
   if(flippie->config->verbose)
      Serial.printf("Handle '%s'(%s) in NotFoundHandler.\n", uri.c_str(), method == HTTP_GET ? "GET" : (method == HTTP_POST ? "POST" : "UNKOWN"));
   
   server.send(404, "text/html", String("Not found."));
   return true;
}

bool NotFoundHandler::canHandle(HTTPMethod method, String uri) {
   true;
}
