#include <Arduino.h>
#include "fp2800a.h"
#include <limits.h>

#ifndef FLIPPIE_H
#define FLIPPIE_H


#define NUMBER_OF_SHIFT_REGISTERS 7
#define SHIFT_REGISTER_CLEAR_TIME_IN_USEC 2
#define SHIFT_REGISTER_LATCH_TIME_IN_USEC 2

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
   unsigned int *sr_set_row_plusvs_pins;

   // shift-register pins of the GND-switching lanes (20 max => BROSE connector limit)
   unsigned int *sr_set_row_gnd_pins;

   // shift-register pins of the 5 columns-coding FP2800A pins (B1, B0, A2, A1, A0)
   unsigned int *sr_column_code_pins;

   // shift-register "direction" pin of the FP2800A (DATA: HIGH => switches +VS, LOW switches GND)
   unsigned int sr_data_pin;

   // shift-register pins of the 7 BROSE module comparator adress pins (ADDR0..ADDR6)
   unsigned int *sr_address_pins;

   // shift-register pin of LED1
   unsigned int sr_led1_pin;

   // shift-register pin of LED2
   unsigned int sr_led2_pin;

   // shift-register pin of LED3
   unsigned int sr_led3_pin;

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

   // pin of the last (8th) BROSE module comparator adress pin and FP2800A enable (E)
   // set it on the DIP switches to "ON" to archive a enable-like functionality
   unsigned int address_enable_pin;
} flippie_t;

class Flippie {

private:
    flippie_t _f;
    unsigned int ** _dots;
    unsigned int ** _next_dots;
    byte * _shift_register;
    byte * _shift_register_clear; // to keep LED status
    unsigned int _activity;
    unsigned int _status_led;
    unsigned int * _int_bit_array;
    byte * _byte_bit_array;
    void fire_shift_register(byte * shift_register);
    void fire_shift_register_with_print(byte * shift_register);

public:
    Flippie();
    void init(flippie_t _f);
    void clear();
    void fill();
    void inverse();
    void magnitize(unsigned int state, unsigned int duration);
    void paint(bool override);
    void paint(unsigned int ** dots);
    void paint(unsigned int ** dots, unsigned int led1_state, unsigned int led2_state, unsigned int led3_state);
    void paint_leds(unsigned int led1_state, unsigned int led2_state, unsigned int led3_state);
    void fill_shift_register_and_fire(unsigned int row, unsigned int module, unsigned int column, unsigned int state, unsigned int duration);
    unsigned int rows;
    unsigned int modules;
    unsigned int columns;

    void test(unsigned int test_bit, unsigned int state);
    void clear_shift_registers();
    void set_row_plusvs(unsigned int row);
    void set_row_gnd(unsigned int row);
    void set_column(unsigned int column);
    void set_column_code(unsigned int fp2800a_column_code, unsigned int state);
    void set_address(byte address);
    void set_data(unsigned int state);
    void set_enable(unsigned int state);
};

#endif
