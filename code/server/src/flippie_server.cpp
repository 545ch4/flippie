#include "flippie_server.h"

FlippieServer::FlippieServer(ESP8266WebServer* s) {
   server = s;
   flippie = new Flippie();
   if(flippie->config->verbose)
      Serial.println("Finished initilizing flippie.");

   server->addHandler(new UIHandler(flippie));
   if(flippie->config->verbose)
      Serial.println("Added UIHandler");
//   server.addHandler(new DotsHandler("/dots", f));
   if(flippie->config->verbose)
      Serial.println("Added DotsHandler");
//   server.addHandler(new PixelHandler("/pixel", f));
   if(flippie->config->verbose)
      Serial.println("Added PixelHandler");
//   server.addHandler(new FlippieHandler("/flippie", f));
   if(flippie->config->verbose)
      Serial.println("Added FlippieHandler");
}
