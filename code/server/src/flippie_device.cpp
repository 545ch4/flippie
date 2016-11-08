#include "flippie.h"
#include "flippie_device.h"

FlippieDevice::FlippieDevice() : Flippie() {
   config.num_modules = 4;
   config.addresses = new unsigned int[4]{1, 2, 4, 8};
   config.num_rows = 18;
   config.num_columns = new unsigned int[4]{28, 28, 28, 21};

   // shift-register config
   // SR1 - SR20 SET
   config.sr_set_row_pins = new unsigned int[20]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
   // SR21 - SR40 RST
   config.sr_rst_row_pins = new unsigned int[20]{20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
   // SR41 D
   config.sr_data_pin = 40;
   // SR42 - SR46 A0-B1
   config.sr_column_code_pins = new unsigned int[5]{45, 44, 43, 42, 41};
   // SR47 - SR53 ADDR1-ADDR7
   config.sr_address_pins = new unsigned int[7]{52, 51, 50, 49, 48, 47, 46};
   // SR54 LED A
   config.sr_led_a_pin = 53;
   // SR55 LED B
   config.sr_led_b_pin = 54;
   // SR56 LED C
   config.sr_led_c_pin = 55;

   // shift-register input
   // 74*595 shift-register clear pin [normal:high, clear:low] (MR, SRCLR, SCLR, SCL)
   config.clear_pin = 16; // wemos D1 mini D0 => GPIO16
   // 74*595 shift-register clock pin (SH_CP, SRCLK, SCK)
   config.clock_pin = 14; // wemos D1 mini D5 => GPIO14
   // 74*595 shift-register storage register clock pin (latch) (ST_CP, RCLK, RCK)
   config.latch_pin = 12; // wemos D1 mini D6 => GPIO12
   // 74*595 shift-register output enable pin [normal:low, tristate output:high] (G, OE)
   config.output_enable_pin = 13; // wemos D1 mini D7 => GPIO13
   // 74*595 shift-register serial data input pin (DS, SER, A, SI)
   config.serial_data_pin = 4; // wemos D1 mini D2 => GPIO4
   // +VS enable (ON pin at current limiter FPF2702MX circuit) pin
   config.vs_enable_pin = 2; // wemos D1 mini D4 => GPIO2
   // NOT_EN and ADDR8@FP2800A
   config.enable_pin = 5; // wemos D1 mini D1 => GPIO5
}
