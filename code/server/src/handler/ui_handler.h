#ifndef UI_HANDLER_H
#define UI_HANDLER_H
#include "flippie.h"
#include <ESP8266WebServer.h>

class UIHandler : public RequestHandler {
  public:
    UIHandler(Flippie* f);
    bool canHandle(HTTPMethod method, String uri) override;
    bool handle(ESP8266WebServer &server, HTTPMethod requestMethod, String requestUri) override;
  protected:
    String root_page, config_page;
    Flippie* flippie;
};

#endif
