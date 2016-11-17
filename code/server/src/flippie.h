#include "brose.h"
#include "debug.h"
#include "fp2800a.h"
#include <Arduino.h>
#include <limits.h>

#ifndef FLIPPIE_H
#define FLIPPIE_H

#define NUMBER_OF_SHIFT_REGISTERS 7
#define SHIFT_REGISTER_WIDTH 8
#define SHIFT_REGISTER_TYPE unsigned char
#define SHIFT_REGISTER_MAXVAL 255
#define SHIFT_REGISTER_CLEAR_TIME_IN_USEC 2
#define SHIFT_REGISTER_LATCH_TIME_IN_USEC 2

#define LED_MODE_NONE 0
#define LED_MODE_FLASHING 1

typedef struct {
  // number of modules connected (127 modules BROSE connector limit)
  unsigned char num_modules;

  // 7-bit addresses of all modules
  unsigned char *addresses;

  // number of rows (equal on each module, 20 max => BROSE connector limit)
  unsigned char num_rows;

  // number of colums (max 28, due to FP2800A limit) of each module
  // (right-padded in the FP2800A truth table)
  unsigned char *num_columns;

  // shift-register pins of the +VS-switching lanes (20 max => BROSE connector
  // limit)
  unsigned char *sr_row_set_pins;

  // shift-register pins of the GND-switching lanes (20 max => BROSE connector
  // limit)
  unsigned char *sr_row_rst_pins;

  // shift-register pins of the 5 columns-coding FP2800A pins (B1, B0, A2, A1,
  // A0)
  unsigned char *sr_column_code_pins;

  // shift-register "direction" pin of the FP2800A (DATA: HIGH => switches +VS,
  // LOW switches GND)
  unsigned char sr_d_pin;

  // shift-register pins of the 7 BROSE module comparator adress pins
  // (ADDR0..ADDR6)
  unsigned char *sr_address_pins;

  // shift-register pin of LED A
  unsigned char sr_led_a_pin;

  // shift-register pin of LED B
  unsigned char sr_led_b_pin;

  // shift-register pin of LED C
  unsigned char sr_led_c_pin;

  // 74*595 shift-register clock pin (SH_CP, SRCLK, SCK)
  unsigned char clock_pin;

  // 74*595 shift-register storage register clock pin (latch) (ST_CP, RCLK, RCK)
  unsigned char latch_pin;

  // 74*595 shift-register serial data input pin (DS, SER, A, SI)
  unsigned char serial_data_pin;

  // 74*595 shift-register clear pin [normal:high, clear:low] (MR, SRCLR, SCLR,
  // SCL)
  unsigned char clear_pin;

  // 74*595 shift-register output enable pin [normal:low, tristate output:high]
  // (G, OE)
  unsigned char output_enable_pin;

  // +VS enable (ON pin at current limiter circuit) pin
  unsigned char vs_enable_pin;

  // pin of the last (SHIFT_REGISTER_WIDTHth) BROSE module comparator adress pin
  // and FP2800A enable (E)
  // set it on the DIP switches to "ON" to archive a enable-like functionality
  unsigned char enable_pin;

  // set the led mode
  unsigned char led_mode;

  // enable/disable verbose messages on serial console
  bool verbose;
} flippie_t;

class Flippie {

private:
  unsigned int **_dots;
  unsigned int **_next_dots;
  unsigned char *_shift_register;
  unsigned int *_int_bit_array;
  unsigned char *_byte_bit_array;
  void cycle_dots();
  void _set_dot(unsigned char row, unsigned char module, unsigned char column,
                unsigned char state, bool save);
  String binary_array_as_bit_string(unsigned char *arr, unsigned int len,
                                    bool quotes);

public:
  Flippie();
  Flippie(flippie_t *f);

  // flippie configuation
  flippie_t *config;

  // LEDs status
  bool led_A_on;
  bool led_B_on;
  bool led_C_on;

  // flippie tasks
  void clear();
  void fill();
  void inverse();
  void magnetize(unsigned char repeats);

  // paint _dots in different flavours
  void paint(bool override_former_dot_state);
  void paint(unsigned int **dots, bool override_former_dot_state);

  // setter and getter of shift-register parts
  void clear_shift_register(bool fire_after_clear);
  void set_row_set(unsigned char row);
  void set_row_rst(unsigned char row);
  void set_column(unsigned char column);
  void set_address(unsigned char address);
  void set_d(unsigned char state);
  void set_dot(unsigned char row, unsigned char module, unsigned char column,
               unsigned char state);
  unsigned char get_row_set();
  unsigned char get_row_rst();
  unsigned char get_column();
  unsigned char get_address();
  unsigned char get_d();
  unsigned char get_dot(unsigned char row, unsigned char module,
                        unsigned char column);

  // low-level fire shift-register (optional set FP2800A enable)
  void fire_shift_register();
  void fire_shift_register(bool enable);
  String shift_register_as_string();
  String shift_register_as_json_short_string();
  String shift_register_as_json();

  // access to dots
  unsigned int **get_next_dots() { return _next_dots; };
  unsigned int **get_dots() { return _dots; };
  String dots_as_string(unsigned int **dots);

  //   void test(unsigned char test_bit, unsigned char state);
};

#endif
