#ifndef NOT_FOUND_HANDLER_H
#define NOT_FOUND_HANDLER_H
#include "../flippie.h"
#include <ESP8266WebServer.h>

class NotFoundHandler : public RequestHandler {
  public:
    NotFoundHandler(Flippie* f);
    bool canHandle(HTTPMethod method, String uri) override;
    bool handle(ESP8266WebServer& server, HTTPMethod method, String uri) override;
  protected:
    Flippie* flippie;
};

#endif
