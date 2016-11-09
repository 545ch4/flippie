#include "root.h"
#include "flippie.h"
#include "flippie_device.h"
#include <ESP8266WebServer.h>

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

RootPage::RootPage(const char* uri) {
   root_page = 
#include "data/index.html"
;
   replace(root_page, "@@@rows@@@", 
}

bool RootPage::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }

   server.send(200, "text/html",
);
return true;
}
