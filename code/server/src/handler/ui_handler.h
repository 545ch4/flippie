#ifndef UI_HANDLER_H
#define UI_HANDLER_H
#include "flippie.h"
#include "flippie_device.h"
#include <ESP8266WebServer.h>

class UIHandler : public RequestHandler {
  public:
    UIHandler(const char* uri, FlippieDevice flippie);
    bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
  protected:
    String _uri, root_page, config_page;
};

#endif
