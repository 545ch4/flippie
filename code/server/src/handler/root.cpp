#include "root.h"
#include "flippie.h"
#include "flippie_device.h"
#include <ESP8266WebServer.h>

bool RootPage::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }

   server.send(200, "text/html",
   #include "data/index.html"
);
return true;
}
