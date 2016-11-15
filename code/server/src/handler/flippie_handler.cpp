#include "flippie_handler.h"

FlippieHandler::FlippieHandler(Flippie* f) {
   flippie = f;
}

bool FlippieHandler::handle(ESP8266WebServer& server, HTTPMethod method, String uri) {
   if(!canHandle(method, uri)) {
      return false;
   }
   if(method == HTTP_GET) {
      char *tmp = new char[16];
      if(server.hasArg("shiftregister")) {
         server.send(200, "application/json", flippie->shift_register_as_json_short_string());
      } else if(server.hasArg("led_A")) {
         server.send(200, "application/json", flippie->led_A_on ? "1" : "0");
      } else if(server.hasArg("led_B")) {
         server.send(200, "application/json", flippie->led_B_on ? "1" : "0");
      } else if(server.hasArg("led_C")) {
         server.send(200, "application/json", flippie->led_C_on ? "1" : "0");
      } else if(server.hasArg("address")) {
         sprintf(tmp, "%hhu\0", flippie->get_address() & 127);
         server.send(200, "application/json", String(tmp));
      } else if(server.hasArg("column")) {
         sprintf(tmp, "%hhu\0", flippie->get_column() & 32);
         server.send(200, "application/json", String(tmp));
      } else if(server.hasArg("d")) {
         server.send(200, "application/json", flippie->get_d() ? "true" : "false");
      } else if(server.hasArg("row_set")) {
         sprintf(tmp, "%hhu\0", flippie->get_row_set() & 32);
         server.send(200, "application/json", String(tmp));
      } else if(server.hasArg("row_rst")) {
         sprintf(tmp, "%hhu\0", flippie->get_row_rst() & 32);
         server.send(200, "application/json", String(tmp));
      } else {
         server.send(405, "application/json", "\"Unknown get command\"");
      }
      free(tmp);
   } else if(method == HTTP_POST) {
      bool json_verb = true;
      if(server.hasArg("task")) {
         if(server.arg("task").equals("clear")) {
            flippie->clear();
         } else if(server.arg("task").equals("fill")) {
            flippie->fill();
         } else if(server.arg("task").equals("inverse")) {
            flippie->inverse();
         } else if(server.arg("task").equals("magnetize")) {
            flippie->magnetize(server.hasArg("repeats") ? server.arg("repeats").toInt() : 1);
         } else {
            Serial.printf("Unknown task '%s'\n", server.arg("task").c_str());
            server.send(405, "application/json", "\"Unknown task\"");
         }
      } else {
         if(server.hasArg("led_mode")) {
            flippie->config->led_mode = server.arg("led_mode").toInt();
            goto send_message;
         }
         if(server.hasArg("verbose")) {
            flippie->config->verbose = (server.arg("verbose").toInt() & 1) == 1;
            goto send_message;
         }
         if(server.hasArg("clear") && server.arg("clear").toInt() == 1) {
            flippie->clear_shift_register(true);
            goto send_message;
         }
         if(server.hasArg("led_A")) {
            flippie->led_A_on = (server.arg("led_A").toInt() & 1) == 1 ? true : false;
         }
         if(server.hasArg("led_B")) {
            flippie->led_B_on = (server.arg("led_B").toInt() & 1) == 1 ? true : false;
         }
         if(server.hasArg("led_C")) {
            if(flippie->config->led_mode == LED_MODE_NONE) {
               flippie->led_C_on = (server.arg("led_C").toInt() & 1) == 1 ? true : false;
            } else {
               json_verb = false;
            }
         }
         if(server.hasArg("address")) {
            flippie->set_address(server.arg("address").toInt() & 127);
         }
         if(server.hasArg("column")) {
            flippie->set_column(server.arg("column").toInt() & 32);
         }
         if(server.hasArg("d")) {
            flippie->set_d(server.arg("d").toInt() & 1);
         }
         if(server.hasArg("row_set")) {
            flippie->set_row_set(server.arg("row_set").toInt() & 32);
         }
         if(server.hasArg("row_rst")) {
            flippie->set_row_rst(server.arg("row_rst").toInt() & 32);
         }
         flippie->fire_shift_register(server.hasArg("enable") && (server.arg("enable").toInt() & 1) == 1);
      }
send_message:
      server.send(200, "application/json", json_verb ? "true" : "false");
   }
   return true;
}


bool FlippieHandler::canHandle(HTTPMethod method, String uri) {
   if (uri == "/flippie" && (method == HTTP_GET || method == HTTP_POST)) {
      return true;
   }
   return false;
}
