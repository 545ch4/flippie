#include "flippie.h"
#include "flippie_device.h"
#include <ESP8266WebServer.h>
#include "flippie_server.h"

FlippieServer::FlippieServer(ESP8266WebServer s) {
   server = s;
   FlippieDevice f;

   server.addHandler(new RootPage("/"));
   server.addHandler(new DotsPage("/dots", f));
   server.addHandler(new FlipDotPage("/flipdot", f));
   server.addHandler(new PixelPage("/pixel", f));
   server.addHandler(new SrPage("/shiftregister", f));
}
