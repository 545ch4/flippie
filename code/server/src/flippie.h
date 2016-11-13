#include <Arduino.h>
#include "fp2800a.h"
#include "brose.h"
#include <limits.h>

#ifndef FLIPPIE_H
#define FLIPPIE_H


#define NUMBER_OF_SHIFT_REGISTERS 7
#define SHIFT_REGISTER_WIDTH 8
#define SHIFT_REGISTER_CLEAR_TIME_IN_USEC 2
#define SHIFT_REGISTER_LATCH_TIME_IN_USEC 2

#define LED_MODE_NONE 0
#define LED_MODE_FLASHING 1


typedef struct {
   // number of modules connected (127 modules BROSE connector limit)
   unsigned int num_modules;

   // 7-bit addresses of all modules
   unsigned int *addresses;

   // number of rows (equal on each module, 20 max => BROSE connector limit)
   unsigned int num_rows;

   // number of colums (max 28, due to FP2800A limit) of each module (right-padded in the FP2800A truth table)
   unsigned int *num_columns;

   // shift-register pins of the +VS-switching lanes (20 max => BROSE connector limit)
   unsigned int *sr_row_set_pins;

   // shift-register pins of the GND-switching lanes (20 max => BROSE connector limit)
   unsigned int *sr_row_rst_pins;

   // shift-register pins of the 5 columns-coding FP2800A pins (B1, B0, A2, A1, A0)
   unsigned int *sr_column_code_pins;

   // shift-register "direction" pin of the FP2800A (DATA: HIGH => switches +VS, LOW switches GND)
   unsigned int sr_d_pin;

   // shift-register pins of the 7 BROSE module comparator adress pins (ADDR0..ADDR6)
   unsigned int *sr_address_pins;

   // shift-register pin of LED A
   unsigned int sr_led_a_pin;

   // shift-register pin of LED B
   unsigned int sr_led_b_pin;

   // shift-register pin of LED C
   unsigned int sr_led_c_pin;

   // 74*595 shift-register clock pin (SH_CP, SRCLK, SCK)
   unsigned int clock_pin;

   // 74*595 shift-register storage register clock pin (latch) (ST_CP, RCLK, RCK)
   unsigned int latch_pin;

   // 74*595 shift-register serial data input pin (DS, SER, A, SI)
   unsigned int serial_data_pin;

   // 74*595 shift-register clear pin [normal:high, clear:low] (MR, SRCLR, SCLR, SCL)
   unsigned int clear_pin;

   // 74*595 shift-register output enable pin [normal:low, tristate output:high] (G, OE)
   unsigned int output_enable_pin;

   // +VS enable (ON pin at current limiter circuit) pin
   unsigned int vs_enable_pin;

   // pin of the last (8th) BROSE module comparator adress pin and FP2800A enable (E)
   // set it on the DIP switches to "ON" to archive a enable-like functionality
   unsigned int enable_pin;

   // set the led mode
   unsigned int led_mode;

   // enable/disable verbose messages on serial console
   bool verbose;
} flippie_t;

class Flippie {

private:
   unsigned int ** _dots;
   unsigned int ** _next_dots;
   byte * _shift_register;
   unsigned int * _int_bit_array;
   byte * _byte_bit_array;
   void cycle_dots();

public:
   Flippie();
   Flippie(flippie_t* f);

   // flippie configuation
   flippie_t* config;

   // LEDs status
   bool led_A_on;
   bool led_B_on;
   bool led_C_on;

   // flippie tasks
   void clear();
   void fill();
   void inverse();
   void magnetize(unsigned int repeats);

   // paint _dots in different flavours
   void paint();
   void paint(bool override_former_dot_state);
   void paint(unsigned int ** dots);

   // setter and getter of shift-register parts
   void clear_shift_register(bool fire_after_clear);
   void set_row_set(unsigned int row);
   void set_row_rst(unsigned int row);
   void set_column(unsigned int column);
   void set_address(byte address);
   void set_d(unsigned int state);
   int get_row_set();
   int get_row_rst();
   int get_column();
   byte get_address();
   unsigned int get_d();

   // low-level fire shift-register (optional set FP2800A enable)
   void fire_shift_register();
   void fire_shift_register(bool enable);
   void set_shift_register_and_fire(unsigned int row, unsigned int module, unsigned int column, unsigned int state);
   String shift_register_as_string();
   String shift_register_as_json_short_string();

   //   void test(unsigned int test_bit, unsigned int state);
};

#endif
