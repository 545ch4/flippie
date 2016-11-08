#ifndef HANDLER_FLIP_DOT_H
#define HANDLER_FLIP_DOT_H
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

class FlipDotPage : public RequestHandler {
public:
  FlipDotPage(const char* uri, FlippieDevice flippie);
  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
protected:
  String _uri;
  Flippie flippie;
};

#endif
