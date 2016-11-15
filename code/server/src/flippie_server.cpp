#include "flippie_server.h"

FlippieServer::FlippieServer(ESP8266WebServer* s) {
   server = s;
   flippie = new Flippie();
   if(flippie->config->verbose)
      Serial.println("Finished initilizing flippie.");

   server->addHandler(new UIHandler(flippie));
   if(flippie->config->verbose)
      Serial.println("Added UIHandler");

   server->addHandler(new DotsHandler(flippie));
   if(flippie->config->verbose)
      Serial.println("Added DotsHandler");

   server->addHandler(new PixelHandler(flippie));
   if(flippie->config->verbose)
      Serial.println("Added PixelHandler");

   server->addHandler(new FlippieHandler(flippie));
   if(flippie->config->verbose)
      Serial.println("Added FlippieHandler");
}
