#ifndef HANDLER_UI_H
#define HANDLER_UI_H
#include "flippie.h"
#include "flippie_device.h"
#include <ESP8266WebServer.h>

class UIPage : public RequestHandler {
  public:
    UIPage(const char* uri, FlippieDevice flippie);
    bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
  protected:
    String _uri, root_page, config_page;
};

#endif
