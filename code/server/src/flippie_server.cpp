#include "flippie_server.h"

FlippieServer::FlippieServer(ESP8266WebServer s) {
   server = s;
   FlippieDevice f;

   server.addHandler(new UIHandler("/", f));
   server.addHandler(new DotsHandler("/dots", f));
   server.addHandler(new PixelHandler("/pixel", f));
   server.addHandler(new FlippieHandler("/flippie", f));
}
