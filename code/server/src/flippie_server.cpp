#include "flippie_server.h"

FlippieServer::FlippieServer(ESP8266WebServer s) {
   server = s;
   FlippieDevice f;

   server.addHandler(new UIPage("/", f));
   server.addHandler(new DotsPage("/dots", f));
   server.addHandler(new FlipDotPage("/flipdot", f));
   server.addHandler(new PixelPage("/pixel", f));
   server.addHandler(new SrPage("/shiftregister", f));
}
