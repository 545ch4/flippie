#ifndef DEBUG_H
#define DEBUG_H
#define DEBUG 1
#define debug_printf(fmt, ...)                                                 \
  do {                                                                         \
    if (DEBUG) {                                                               \
      Serial.printf(fmt, ##__VA_ARGS__);                                       \
    }                                                                          \
  } while (0)
#define debug_verbose_printf(fmt, ...)                                         \
  do {                                                                         \
    if (DEBUG) {                                                               \
      Serial.printf("%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__,          \
                    ##__VA_ARGS__);                                            \
    }                                                                          \
  } while (0)
#define debug_delay()                                                          \
  do {                                                                         \
    if (DEBUG) {                                                               \
      delayMicroseconds(10000);                                                \
    }                                                                          \
  } while (0)
#endif
