#ifndef PIXEL_HANDLER_H
#define PIXEL_HANDLER_H
#include "abstract_handler.h"
#include "../flippie.h"
#include <ESP8266WebServer.h>

class PixelHandler : public AbstractHandler {
public:
  PixelHandler(Flippie* f);
  bool canHandle(HTTPMethod method, String uri) override;
  bool handle(ESP8266WebServer& server, HTTPMethod method, String uri) override;
protected:
  Flippie* flippie;
};

#endif
