#include "ui_handler.h"

const char UIHandler::index_page[] PROGMEM =
#include "data/index.html"
    ;
const char UIHandler::low_level_page[] PROGMEM =
#include "data/low_level.html"
    ;
const char UIHandler::paint_page[] PROGMEM =
#include "data/paint.html"
    ;
const char UIHandler::tasks_page[] PROGMEM =
#include "data/tasks.html"
    ;

UIHandler::UIHandler(Flippie *f) {
  flippie = f;
  char *config_page_temp;
  config_page_temp = (char *)malloc(1024 * sizeof(char));
  unsigned int i = 0;
  i = sprintf(config_page_temp + i, "{\n\t\"rows\": %u,\n",
              flippie->config->num_rows);
  i += sprintf(config_page_temp + i, "\t\"max_columns\": %i,\n",
               FP2800A_MAX_COLUMNS);
  i += sprintf(config_page_temp + i, "\t\"max_rows\": %i,\n", BROSE_MAX_ROWS);
  i += sprintf(config_page_temp + i, "\t\"columns\": [\n");
  for (int j = 0; j < flippie->config->num_modules - 1; j++) {
    i += sprintf(config_page_temp + i, "\t\t%u,\n",
                 flippie->config->num_columns[j]);
  }
  i += sprintf(config_page_temp + i, "\t\t%u\n\t]\n}\n\0",
               flippie->config->num_columns[flippie->config->num_modules - 1]);
  config_page = (char *)malloc(i * sizeof(char));
  memcpy(config_page, config_page_temp, i);
  free(config_page_temp);
}

bool UIHandler::handle(ESP8266WebServer &server, HTTPMethod method,
                       String uri) {
  if (!canHandle(method, uri)) {
    return false;
  }

  if (flippie->config->verbose)
    Serial.printf("Handle '%s' in UIHandler.\n", uri.c_str());

  if (uri == "/" || strncmp("/ui", uri.c_str(), 3) == 0) {
    if (uri == "/" || uri == "/index.html") {
      server.sendHeader("Location", "/ui/", true);
      server.send(302, "text/html", "");
    } else if (uri == "/ui" || uri == "/ui/" || uri == "/ui/index.html") {
      server.send(200, "text/html", index_page);
    } else if (uri == "/ui/low_level.html") {
      server.send(200, "text/html", low_level_page);
    } else if (uri == "/ui/paint.html") {
      server.send(200, "text/html", paint_page);
    } else if (uri == "/ui/tasks.html") {
      server.send(200, "text/html", tasks_page);
    } else if (uri == "/ui/config.json") {
      server.send(200, "application/json", config_page);
    } else {
      return false;
    }
    return true;
  }
  return false;
}
bool UIHandler::canHandle(HTTPMethod method, String uri) {
  if (method == HTTP_GET &&
      (uri == "/" || strncmp("/ui", uri.c_str(), 3) == 0)) {
    return true;
  }
  return false;
}
