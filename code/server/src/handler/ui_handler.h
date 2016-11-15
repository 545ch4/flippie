#ifndef UI_HANDLER_H
#define UI_HANDLER_H
#include "../flippie.h"
#include <ESP8266WebServer.h>

class UIHandler : public RequestHandler {
  public:
    UIHandler(Flippie* f);
    bool canHandle(HTTPMethod method, String uri) override;
    bool handle(ESP8266WebServer& server, HTTPMethod method, String uri) override;
  protected:
    String index_page, low_level_page, paint_page, tasks_page, config_page;
    Flippie* flippie;
};

#endif
