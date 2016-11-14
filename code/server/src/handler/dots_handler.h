#ifndef DOTS_HANDLER_H
#define DOTS_HANDLER_H
#include "../flippie.h"
#include "../flippie.h"
#include <ESP8266WebServer.h>

class DotsHandler : public RequestHandler {
public:
  DotsHandler(Flippie* flippie);
  bool canHandle(HTTPMethod method, String uri) override;
  bool handle(ESP8266WebServer& server, HTTPMethod method, String uri) override;
protected:
  Flippie* flippie;
};

#endif
