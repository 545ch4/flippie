#include "flippie.h"

Flippie::Flippie() {
   config = (flippie_t *)malloc(sizeof(flippie_t));
   unsigned int i;

   // TODO: How many modules does your display consists of?
   const unsigned int num_modules = 4;
   config->num_modules = num_modules;
   // TODO: What are the addresses (as byte) of the modules? (see DIP-switches at each module)
   config->addresses = new unsigned int[num_modules]{1, 2, 4, 8};
   // TODO: How many rows does your display have? (equal over all modules)
   config->num_rows = 18;
   // TODO: How many columns does each module of your display have? (same order as the addresses)
   config->num_columns = new unsigned int[num_modules]{28, 28, 28, 21};
   // TODO: Should LED C toggle on each shift-register firing?
   config->led_mode = LED_MODE_FLASHING;
   // TODO: Verbose outputs on serial line?
   config->verbose = true;

   // values below are specific to the flippie board - do not modify
   // shift-register config
   // SR1 - SR20 SET
   config->sr_row_set_pins = new unsigned int[BROSE_MAX_ROWS]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
   // SR21 - SR40 RST
   config->sr_row_rst_pins = new unsigned int[BROSE_MAX_ROWS]{20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
   // SR41 D
   config->sr_d_pin = 40;
   // SR42 - SR46 A0-B1
   config->sr_column_code_pins = new unsigned int[FP2800A_COLUMN_CODE_LINES]{45, 44, 43, 42, 41};
   // SR47 - SR53 ADDR1-ADDR7
   config->sr_address_pins = new unsigned int[BROSE_ADDR_LINES - 1]{52, 51, 50, 49, 48, 47, 46};
   // SR54 LED A
   config->sr_led_a_pin = 53;
   // SR55 LED B
   config->sr_led_b_pin = 54;
   // SR56 LED C
   config->sr_led_c_pin = 55;

   // shift-register input
   // 74*595 shift-register clear pin [normal:high, clear:low] (MR, SRCLR, SCLR, SCL)
   config->clear_pin = 16; // wemos D1 mini D0 => GPIO16
   // 74*595 shift-register clock pin (SH_CP, SRCLK, SCK)
   config->clock_pin = 14; // wemos D1 mini D5 => GPIO14
   // 74*595 shift-register storage register clock pin (latch) (ST_CP, RCLK, RCK)
   config->latch_pin = 12; // wemos D1 mini D6 => GPIO12
   // 74*595 shift-register output enable pin [normal:low, tristate output:high] (G, OE)
   config->output_enable_pin = 13; // wemos D1 mini D7 => GPIO13
   // 74*595 shift-register serial data input pin (DS, SER, A, SI)
   config->serial_data_pin = 4; // wemos D1 mini D2 => GPIO4
   // +VS enable (ON pin at current limiter FPF2702MX circuit) pin
   config->vs_enable_pin = 2; // wemos D1 mini D4 => GPIO2
   // NOT_EN and ADDR8@FP2800A
   config->enable_pin = 5; // wemos D1 mini D1 => GPIO5
   if(config->verbose)
      Serial.println("Finished configure flippie.");


   // init fast bit-wise comparator array (int-sized)
   _int_bit_array = (unsigned int *)malloc(32 * sizeof(unsigned int));
   for(i = 0; i < 32; ++i) {
      _int_bit_array[i] = 1<<i;
   }
   // init fast bit-wise comparator array (byte-sized)
   _byte_bit_array = (unsigned char *)malloc(8 * sizeof(unsigned char));
   for(i = 0; i < 8; ++i) {
      _byte_bit_array[i] = 1<<i;
   }

   // initialze shift-register as NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH
   _shift_register = (unsigned char *)calloc(NUMBER_OF_SHIFT_REGISTERS, SHIFT_REGISTER_WIDTH);


   // shift-register LED_A, LED_B and LED_C
   led_A_on = false;
   led_B_on = false;
   led_C_on = false;

   // define pins (not srPins) as outputs
   pinMode(config->output_enable_pin, OUTPUT);
   pinMode(config->clock_pin, OUTPUT);
   pinMode(config->serial_data_pin, OUTPUT);
   pinMode(config->latch_pin, OUTPUT);
   pinMode(config->clear_pin, OUTPUT);
   pinMode(config->enable_pin, OUTPUT);
   // don't enable
   digitalWrite(config->enable_pin, HIGH);
   // enable +VS
   digitalWrite(config->vs_enable_pin, LOW);

   if(config->verbose)
      Serial.println("Finished defining all output pins.");

   // reset shift-register
   digitalWrite(config->clear_pin, LOW);
   delayMicroseconds(SHIFT_REGISTER_CLEAR_TIME_IN_USEC);
   digitalWrite(config->clear_pin, HIGH);

   // init shift-register to tristate all outputs
   digitalWrite(config->output_enable_pin, HIGH);
   digitalWrite(config->clock_pin, LOW);
   digitalWrite(config->serial_data_pin, LOW);
   digitalWrite(config->latch_pin, LOW);
   digitalWrite(config->clear_pin, LOW);

   // init shift-register to ALL-LOW and just flash LED_A, LED_B and LED_C three times
   for(i = 0; i < 3; i++) {
      led_A_on = true;
      led_B_on = true;
      led_C_on = true;
      fire_shift_register(false);
      delay(100);
      led_A_on = false;
      led_B_on = false;
      led_C_on = false;
      fire_shift_register(false);
      delay(700);
   }
   if(config->verbose)
      Serial.println("\nFinished initilizing shift-register.");

   // initialze _dots and _next_dots
   // array of rows => array of modules => columns are encoded bit-wise in an integer (32-bit wide => 32 column max)
   _dots = (unsigned int **)malloc(config->num_rows * sizeof(unsigned int *));
   _next_dots = (unsigned int **)malloc(config->num_rows * sizeof(unsigned int *));
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      _dots[i] = (unsigned int *)calloc(config->num_modules, sizeof(unsigned int));
      _next_dots[i] = (unsigned int *)calloc(config->num_modules, sizeof(unsigned int));
   }
}


// copy current state _next_dots to _dots
void Flippie::cycle_dots() {
   memcpy(_dots, _next_dots, config->num_rows * sizeof(unsigned int *));
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      memcpy(_dots[i], _next_dots[i], config->num_modules * sizeof(unsigned int));
   }
}

// paint content of _next_dots
// only paint differnces to _dots unless override is true (default = false)
void Flippie::paint(bool override_former_dot_state) {
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      for(unsigned int j = 0; j < config->num_modules; ++j) {
         for(unsigned int k = 0; k < config->num_columns[j]; ++k) {
            if(override_former_dot_state || (_dots[i][j] & _int_bit_array[k]) != (_next_dots[i][j] & _int_bit_array[k])) {
               _set_dot(i, j, k, (_next_dots[i][j] & _int_bit_array[k]) == _int_bit_array[k] ? 1 : 0, false);
               fire_shift_register(true);
            }
         }
      }
   }
   // _next_dots are the new _dots
   cycle_dots();
   if(config->verbose)
      Serial.printf("Done painting _next_dots.\n");
}
void Flippie::paint() {
   paint(false);
}
// set content of _next_dots and paint (cleverly only setting changed dots)
void Flippie::paint(unsigned int** dots) {
   memcpy(_next_dots, dots, config->num_rows * sizeof(unsigned int *));
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      memcpy(_next_dots[i], dots[i], config->num_modules * sizeof(unsigned int));
   }
   paint();
}

// repaint (magnetize) the whole display
void Flippie::magnetize(unsigned int repeats) {
   for(unsigned int r = 0; r < repeats; r++) {
      for(unsigned int i = 0; i < config->num_rows; ++i) {
         for(unsigned int j = 0; j < config->num_modules; ++j) {
            for(unsigned int k = 0; k < config->num_columns[j]; ++k) {
               _set_dot(i, j, k, _dots[i][j], false);
               fire_shift_register(true);
            }
         }
      }
   }
   if(config->verbose)
      Serial.printf("Done magnetizing display %d times.\n", repeats);
}


// clear all dots and paint
void Flippie::clear() {
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      for(unsigned int j = 0; j < config->num_modules; ++j) {
         _next_dots[i][j] = 0;
         _dots[i][j] = 0;
         for(unsigned int k = 0; k < config->num_columns[j]; ++k) {
            _set_dot(i, j, k, 0, false);
            fire_shift_register(true);
         }
      }
   }
   if(config->verbose)
      Serial.printf("Done clearing display.\n");
}

// calc inverse of _dots, save to _next_dots and paint
void Flippie::inverse() {
   unsigned int x = 0;
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      for(unsigned int j = 0; j < config->num_modules; ++j) {
         _dots[i][j] = UINT_MAX - _dots[i][j];
         for(unsigned int k = 0; k < config->num_columns[j]; ++k) {
            _set_dot(i, j, k, _next_dots[i][j], false);
            fire_shift_register(true);
         }
      }
   }
   if(config->verbose)
      Serial.printf("Done inversing display.\n");
}

// fill all dots, save to _next_dots and paint
void Flippie::fill() {
   unsigned int x = 0;
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      for(unsigned int j = 0; j < config->num_modules; ++j) {
         _dots[i][j] = UINT_MAX;
         for(unsigned int k = 0; k < config->num_columns[j]; ++k) {
            _set_dot(i, j, k, _dots[i][j], false);
            fire_shift_register(true);
         }
      }
   }
   if(config->verbose)
      Serial.printf("Done filling display.\n");
}

// set/get row_set
void Flippie::set_row_set(unsigned int row) {
   // reset all RST rows
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      _shift_register[config->sr_row_rst_pins[i]/8] &= (255 - _byte_bit_array[config->sr_row_rst_pins[i]%8]);
   }
   _shift_register[config->sr_row_set_pins[row]/8] |= _byte_bit_array[config->sr_row_set_pins[row]%8];
}
int Flippie::get_row_set() {
   for(unsigned int row = 0; row < BROSE_MAX_ROWS; row++) {
      if((_shift_register[config->sr_row_set_pins[row]/8] & _byte_bit_array[config->sr_row_set_pins[row]%8]) == _byte_bit_array[config->sr_row_set_pins[row]%8])
         return row;
   }
   return -1;
}

// set/get row_rst
void Flippie::set_row_rst(unsigned int row) {
   // reset all SET rows
   for(unsigned int i = 0; i < config->num_rows; ++i) {
      _shift_register[config->sr_row_set_pins[i]/8] &= (255 - _byte_bit_array[config->sr_row_set_pins[i]%8]);
   }
   _shift_register[config->sr_row_rst_pins[row]/8] |= _byte_bit_array[config->sr_row_rst_pins[row]%8];
}
int Flippie::get_row_rst() {
   for(unsigned int row = 0; row < BROSE_MAX_ROWS; row++) {
      if((_shift_register[config->sr_row_rst_pins[row]/8] & _byte_bit_array[config->sr_row_rst_pins[row]%8]) == _byte_bit_array[config->sr_row_rst_pins[row]%8])
         return row;
   }
   return -1;
}

// set/get coolumn
void Flippie::set_column(unsigned int column) {
   for(unsigned int i = 0; i < FP2800A_COLUMN_CODE_LINES; i++) {
      if(FP2800A_COLUMN_CODES[column][i] == 1) {
         _shift_register[config->sr_column_code_pins[i]/8] |= _byte_bit_array[config->sr_column_code_pins[i]%8];
      } else {
         _shift_register[config->sr_column_code_pins[i]/8] &= (255 - _byte_bit_array[config->sr_column_code_pins[i]%8]);
      }
   }
}
int Flippie::get_column() {
   bool found = true;
   for(unsigned int column = 0; column < FP2800A_MAX_COLUMNS; column++) {
      found = true;
      for(unsigned int i = 0; i < FP2800A_COLUMN_CODE_LINES; i++) {
         found &= ((_shift_register[config->sr_column_code_pins[i]/8] & _byte_bit_array[config->sr_column_code_pins[i]%8]) == _byte_bit_array[config->sr_column_code_pins[i]%8]);
      }
      if(found)
         return column;
   }
   return -1;
}

// set/get address (ADDR1-ADDR7)
void Flippie::set_address(unsigned char address) {
   for(unsigned int i = 0; i < BROSE_ADDR_LINES - 1; ++i) {
      if((address>>i) & 1 == 1) {
         _shift_register[config->sr_address_pins[i]/8] |= _byte_bit_array[config->sr_address_pins[i]%8];
      }
   }
}
unsigned char Flippie::get_address() {
   unsigned char address = 0x00;
   for(int i = BROSE_ADDR_LINES - 2; i >= 0 ; i--) {
      if((_shift_register[config->sr_address_pins[i]/8] & _byte_bit_array[config->sr_address_pins[i]%8]) == _byte_bit_array[config->sr_address_pins[i]%8]) {
         address |= 1;
      }
      address<<1;
   }
   return address;
}

// set FP2800A direction 1 => switches +VS, 0 switches GND
void Flippie::set_d(unsigned int state) {
   if(state == 1) {
      _shift_register[config->sr_d_pin/8] |= _byte_bit_array[config->sr_d_pin%8];
   } else {
      _shift_register[config->sr_d_pin/8] &= (255 - _byte_bit_array[config->sr_d_pin%8]);
   }
}
unsigned int Flippie::get_d() {
   return ((_shift_register[config->sr_d_pin/8] & _byte_bit_array[config->sr_d_pin%8]) == _byte_bit_array[config->sr_d_pin%8]) ? 1 : 0;
}

// clear shift-registers
void Flippie::clear_shift_register(bool fire_after_clear) {
   for(unsigned int i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
      _shift_register[i] = 0;
   }
   // fireing shift-register if requested
   if(fire_after_clear) {
      fire_shift_register(false);
   }
}

// assemble the shift-register for a specific dotsand fire it
// resetting shift-register and set all output to low afterwards
void Flippie::_set_dot(unsigned int row, unsigned int module, unsigned int column, unsigned int state, bool save) {
   unsigned int i;

   // clear shift-register
   for(i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
      _shift_register[i] = 0;
   }

   // set state of the selected row
   if(state == 1) {
      _shift_register[config->sr_row_set_pins[row]/8] |= _byte_bit_array[config->sr_row_set_pins[row]%8];
   } else {
      _shift_register[config->sr_row_rst_pins[row]/8] |= _byte_bit_array[config->sr_row_rst_pins[row]%8];
   }

   // set column code (B1-A0)
   for(i = 0; i < FP2800A_COLUMN_CODE_LINES; ++i) {
      if(FP2800A_COLUMN_CODES[(FP2800A_MAX_COLUMNS - config->num_columns[module]) + column][i] == 1) {
         _shift_register[config->sr_column_code_pins[i]/8] |= _byte_bit_array[config->sr_column_code_pins[i]%8];
      }
   }

   // set address (ADDR1-ADDR7)
   for(i = 0; i < BROSE_ADDR_LINES - 1; ++i) {
      if(config->addresses[module]>>i & 1 == 1) {
         _shift_register[config->sr_address_pins[i]/8] |= _byte_bit_array[config->sr_address_pins[i]%8];
      }
   }

   // set D
   if(state == 0) {
      _shift_register[config->sr_d_pin/8] |= _byte_bit_array[config->sr_d_pin%8];
   }

   // set LEDs
   // if configured flash automatically
   if(config->led_mode == LED_MODE_FLASHING) {
      led_C_on = !led_C_on;
   }
   if(led_A_on) {
      _shift_register[config->sr_led_a_pin/8] |= _byte_bit_array[config->sr_led_a_pin%8];
   }
   if(led_B_on) {
      _shift_register[config->sr_led_b_pin/8] |= _byte_bit_array[config->sr_led_b_pin%8];
   }
   if(led_C_on) {
      _shift_register[config->sr_led_c_pin/8] |= _byte_bit_array[config->sr_led_c_pin%8];
   }

   if(save) {
      if(state & 1 == 1) {
         _dots[row][module] |= 1<<column;
      } else {
         _dots[row][module] -= 1<<column;
      }
   }
}
void Flippie::set_dot(unsigned int row, unsigned int module, unsigned int column, unsigned int state) {
   _set_dot(row, module, column, state, true);
}
unsigned int Flippie::get_dot(unsigned int row, unsigned int module, unsigned int column) {
   return _dots[row][module]<<column & 1;
}

// fire a given shift-register according to pins given
void Flippie::fire_shift_register(bool enable) {
   // just in case => defined start point
   digitalWrite(config->clock_pin, LOW);
   // just in case => clear shift-register
   digitalWrite(config->clear_pin, LOW);
   digitalWrite(config->clear_pin, HIGH);

   // shift out (reverse order) shift-register unsigned char array
   for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
      digitalWrite(config->serial_data_pin, (_shift_register[i/8] & _byte_bit_array[i%8]) == _byte_bit_array[i%8] ? HIGH : LOW);
      digitalWrite(config->clock_pin, HIGH);
      digitalWrite(config->clock_pin, LOW);
   }
   digitalWrite(config->latch_pin, HIGH);
   digitalWrite(config->latch_pin, LOW);

   if(enable) {
      // fire using ADDR8 aka NOT_EN => FP2800A enable (E)
      digitalWrite(config->enable_pin, HIGH);
      delayMicroseconds(FP2800A_ACTIVE_TIME_IN_USEC);
      digitalWrite(config->enable_pin, LOW);
   }

   if(config->verbose)
      Serial.print(enable ? "X" : "x");

   yield();
}

// fire a given shift-register according to pins given
// print shift-register
String Flippie::shift_register_as_string() {
   char *tmp = new char[(3 * ((NUMBER_OF_SHIFT_REGISTERS * 8) + 1)) + 1];
   unsigned int tmp_pos = 0;

   tmp_pos += sprintf(tmp + tmp_pos, "SRA: ");
   for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
      tmp_pos += sprintf(tmp + tmp_pos, "%u", i/8);
   }

   tmp_pos += sprintf(tmp + tmp_pos, "\nSRA: ");
   for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
      tmp_pos += sprintf(tmp + tmp_pos, "%u", i%8);
   }

   tmp_pos += sprintf(tmp + tmp_pos, "\nSRD: ");
   for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
      tmp[tmp_pos] = (_shift_register[i/8] & _byte_bit_array[i%8]) == _byte_bit_array[i%8] ? 'H' : 'L';
      tmp_pos++;
   }
   sprintf(tmp + tmp_pos, "\n\0");
   String s(tmp);
   free(tmp);
   return s;
}

// return shift-register in shortend form as json string
String Flippie::shift_register_as_json_short_string() {
   char *bit_string = (char *)malloc((NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH) + 3);
   bit_string[0] = '"';
   unsigned int l = 1;
   for(unsigned int i = 0; i < NUMBER_OF_SHIFT_REGISTERS; i++) {
      for(unsigned int j = 0; j < SHIFT_REGISTER_WIDTH; j++) {
         bit_string[l] = ((((_shift_register[i]<<j) & 1) == 1) ? '1' : '0');
         l++;
      }
   }
   bit_string[l] = '"';
   bit_string[l + 1] = '\0';
   String s(bit_string);
   free(bit_string);
   return s;
}

// return shift-register in shortend form as json string
String Flippie::shift_register_as_json() {
   char* r = (char *)malloc(1024);
   unsigned int r_len = sprintf(r, "{\n\t\"address\": %i,\n\t\"column\": %i,\n\t\"row_set\": %i,\n\t\"row_rst\": %i,\n\t\"led_A\": %u,\n\t\"led_B\": %u,\n\t\"led_C\": %u,\n\t\"d\": %u\n}\n\0", get_address(), get_column(), get_row_set(), get_row_rst(), led_A_on ? 1 : 0, led_B_on ? 1 : 0, led_C_on ? 1 : 0, get_d());
   String s(r);
   free(r);
   return s;
}





// // set all possible shift-register outputs (filling the shift-register and fire it)
// void Flippie::test(unsigned int test_bit, unsigned int state) {
//    if(state == 0) {
//       _shift_register[test_bit/8] &= (255 - _byte_bit_array[test_bit%8]);
//    } else {
//       _shift_register[test_bit/8] |= _byte_bit_array[test_bit%8];
//    }
//    Serial.printf("set bit-position %u(%u,%u) to %u => [ %u", test_bit, test_bit/8, test_bit%8, state, _shift_register[0]);
//    for(unsigned int i = 1; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
//       Serial.printf(", %u", _shift_register[i]);
//    }
//    Serial.println("]");
//    fire_shift_register_with_print(false);
// }
