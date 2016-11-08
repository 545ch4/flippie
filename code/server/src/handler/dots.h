#ifndef HANDLER_DOTS_H
#define HANDLER_DOTS_H
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

class DotsPage : public RequestHandler {
public:
  DotsPage(const char* uri, FlippieDevice flippie);
  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
protected:
  String _uri;
  Flippie flippie;
};

#endif
