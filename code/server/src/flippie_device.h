#include "flippie.h"
#ifndef FLIPPIE_DEVICE_H
#define FLIPPIE_DEVICE_H

class FlippieDevice {
private:
   flippie_t ft;
public:
   FlippieDevice();
   void init();
   Flippie f;
};

#endif
