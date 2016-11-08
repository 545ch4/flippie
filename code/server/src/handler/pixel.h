#ifndef HANDLER_PIXEL_H
#define HANDLER_PIXEL_H
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

class PixelPage : public RequestHandler {
public:
  PixelPage(const char* uri, FlippieDevice flippie);
  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
protected:
  String _uri;
  Flippie flippie;
};

#endif
