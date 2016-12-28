#include "flippie.h"

Flippie::Flippie() {
  config = (flippie_t *)malloc(sizeof(flippie_t));
  unsigned char i;

  // TODO: How many modules does your display consists of?
  const unsigned char num_modules = 1;
  config->num_modules = num_modules;
  // TODO: What are the addresses (as byte) of the modules? (see DIP-switches at
  // each module)
  config->addresses = new unsigned char[num_modules]{1};
  // TODO: How many rows does your display have? (equal over all modules)
  config->num_rows = 16;
  // TODO: How many columns does each module of your display have? (same order
  // as the addresses)
  config->num_columns = new unsigned char[num_modules]{21};
  // TODO: Should LED C toggle on each shift-register firing?
  config->led_mode = LED_MODE_FLASHING;
  // TODO: Verbose outputs on serial line?
  config->verbose = true;

  // values below are specific to the flippie board - do not modify
  // shift-register config
  // SR1 - SR20 SET
  config->sr_row_set_pins = new unsigned char[BROSE_MAX_ROWS]{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  // SR21 - SR40 RST
  config->sr_row_rst_pins =
      new unsigned char[BROSE_MAX_ROWS]{20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                        30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
  // SR41 D
  config->sr_d_pin = 40;
  // SR42 - SR46 A0-B1
  config->sr_column_code_pins =
      new unsigned char[FP2800A_COLUMN_CODE_LINES]{45, 44, 43, 42, 41};
  // SR47 - SR53 ADDR1-ADDR7
  config->sr_address_pins =
      new unsigned char[BROSE_ADDR_LINES]{46, 47, 48, 49, 50, 51, 52};
  // SR54 LED A
  config->sr_led_a_pin = 53;
  // SR55 LED B
  config->sr_led_b_pin = 54;
  // SR56 LED C
  config->sr_led_c_pin = 55;

  // shift-register input
  // 74*595 shift-register clear pin [normal:high, clear:low] (~MR, ~SRCLR,
  // ~SCLR, ~SCL)
  config->not_clear_pin = D8;
  // 74*595 shift-register clock pin (SH_CP, SRCLK, SCK)
  config->clock_pin = D5;
  // 74*595 shift-register storage register clock pin (latch) (ST_CP, RCLK, RCK)
  config->latch_pin = D6;
  // 74*595 shift-register output enable pin [normal:low, tristate output:high]
  // (~G, ~OE)
  config->not_output_enable_pin = D7;
  // 74*595 shift-register serial data input pin (DS, SER, A, SI)
  config->serial_data_pin = D2;

  // ~EN_POWER_RAILS pin (eg. ON pin at current limiter FPF2702MX circuit)
  config->not_enable_power_rails_pin = D1;

  // ~EN and ADDR8@FP2800A
  config->not_enable_pin = D3;

  if (config->verbose)
    Serial.println("Finished configure flippie.");

  // init fast bit-wise comparator array (int-sized)
  _int_bit_array = (unsigned int *)malloc(32 * sizeof(unsigned int));
  for (i = 0; i < 32; ++i) {
    _int_bit_array[i] = 1 << i;
  }
  // init fast bit-wise comparator array (byte-sized)
  _byte_bit_array =
      (unsigned char *)malloc(SHIFT_REGISTER_WIDTH * sizeof(unsigned char));
  for (i = 0; i < SHIFT_REGISTER_WIDTH; ++i) {
    _byte_bit_array[i] = 1 << i;
  }

  // initialze shift-register as NUMBER_OF_SHIFT_REGISTERS *
  // SHIFT_REGISTER_WIDTH
  _shift_register =
      (unsigned char *)calloc(NUMBER_OF_SHIFT_REGISTERS, SHIFT_REGISTER_WIDTH);

  // shift-register LED_A, LED_B and LED_C
  led_A_on = false;
  led_B_on = false;
  led_C_on = false;

  // define pins (not srPins) as outputs

  pinMode(config->not_output_enable_pin, OUTPUT);
  // tri-state all outputs of the shift-register
  digitalWrite(config->not_output_enable_pin, HIGH);

  pinMode(config->clock_pin, OUTPUT);
  digitalWrite(config->clock_pin, LOW);

  pinMode(config->serial_data_pin, OUTPUT);
  digitalWrite(config->serial_data_pin, LOW);

  pinMode(config->latch_pin, OUTPUT);
  digitalWrite(config->latch_pin, LOW);

  pinMode(config->not_clear_pin, OUTPUT);
  digitalWrite(config->not_clear_pin, HIGH);

  // don't enable FP2800A
  pinMode(config->not_enable_pin, OUTPUT);
  digitalWrite(config->not_enable_pin, HIGH);

  // reset shift-register
  digitalWrite(config->not_clear_pin, LOW);
  digitalWrite(config->not_clear_pin, HIGH);

  // enable all power rails
  pinMode(config->not_enable_power_rails_pin, OUTPUT);
  digitalWrite(config->not_enable_power_rails_pin, LOW);

  // enable all outputs of the shift-register
  digitalWrite(config->not_output_enable_pin, LOW);

  // disable internal LED
  digitalWrite(D4, HIGH);

  if (config->verbose)
    Serial.println("Finished defining and setting all output pins.");

  // init shift-register to LOW except flash LED_A, LED_B and LED_C three times
  for (i = 0; i < 3; ++i) {
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
  if (config->led_mode == LED_MODE_FLASHING) {
    flashing_led_C_on = false;
  }

  if (config->verbose)
    Serial.println("\nFinished first test of shift-register.");

  // initialze _dots and _next_dots
  // array of rows => array of modules => columns are encoded bit-wise in an
  // integer (32-bit wide => 32 column max)
  _dots = (unsigned int **)malloc(config->num_rows * sizeof(unsigned int *));
  _next_dots =
      (unsigned int **)malloc(config->num_rows * sizeof(unsigned int *));
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    _dots[i] =
        (unsigned int *)calloc(config->num_modules, sizeof(unsigned int));
    _next_dots[i] =
        (unsigned int *)calloc(config->num_modules, sizeof(unsigned int));
  }
}

// copy current state _next_dots to _dots
void Flippie::cycle_dots() {
  memcpy(_dots, _next_dots, config->num_rows * sizeof(unsigned int *));
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    memcpy(_dots[i], _next_dots[i], config->num_modules * sizeof(unsigned int));
  }
}

// paint content of _next_dots
// only paint differnces to _dots unless override is true (default = false)
void Flippie::paint(bool override_former_dot_state) {
  debug_printf("Start painting with override=%s ... ",
               override_former_dot_state ? "true" : "false");
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    for (unsigned char j = 0; j < config->num_modules; ++j) {
      for (unsigned char k = 0; k < config->num_columns[j]; ++k) {
        if (override_former_dot_state ||
            (_dots[i][j] & _int_bit_array[k]) !=
                (_next_dots[i][j] & _int_bit_array[k])) {
          _set_dot(i, j, k,
                   (_next_dots[i][j] & _int_bit_array[k]) == _int_bit_array[k]
                       ? 1
                       : 0,
                   false);
          fire_shift_register(true);
        }
      }
    }
  }
  // _next_dots are the new _dots
  cycle_dots();
  if (DEBUG)
    debug_printf(" DONE.\n");
  else if (config->verbose)
    Serial.printf("Done painting _next_dots.\n");
}
// set content of _next_dots and paint (cleverly only setting changed dots)
void Flippie::set_next_and_paint(unsigned int **dots,
                                 bool override_former_dot_state) {
  // memcpy(_next_dots, dots, config->num_rows * sizeof(unsigned int*));
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    memcpy(_next_dots[i], dots[i], config->num_modules * sizeof(unsigned int));
  }
  paint(override_former_dot_state);
}

// repaint (magnetize) the whole display
void Flippie::magnetize(unsigned char repeats) {
  debug_printf("Start magnetizing %d times ", repeats);
  for (unsigned char r = 0; r < repeats; ++r) {
    for (unsigned char i = 0; i < config->num_rows; ++i) {
      for (unsigned char j = 0; j < config->num_modules; ++j) {
        for (unsigned char k = 0; k < config->num_columns[j]; ++k) {
          _set_dot(i, j, k,
                   ((_dots[i][j] & _int_bit_array[j]) == _int_bit_array[j]) ? 1
                                                                            : 0,
                   false);
          fire_shift_register(true);
          debug_printf(".");
        }
      }
    }
  }
  if (DEBUG)
    debug_printf(" DONE.\n");
  else if (config->verbose)
    Serial.printf("Done magnetizing display %d times.\n", repeats);
}

// clear all dots and paint
void Flippie::clear() {
  debug_printf("Start clearing the display ");
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    for (unsigned char j = 0; j < config->num_modules; ++j) {
      _next_dots[i][j] = 0;
      _dots[i][j] = 0;
      for (unsigned char k = 0; k < config->num_columns[j]; ++k) {
        _set_dot(i, j, k, 0, false);
        fire_shift_register(true);
        debug_printf(".");
      }
    }
  }
  if (DEBUG)
    debug_printf(" DONE.\n");
  else if (config->verbose)
    Serial.printf("Done clearing display.\n");
}

// calc inverse of _dots, save to _next_dots and paint
void Flippie::inverse() {
  debug_printf("Start inversing the display ");
  unsigned char x = 0;
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    for (unsigned char j = 0; j < config->num_modules; ++j) {
      _dots[i][j] = UINT_MAX - _dots[i][j];
      for (unsigned char k = 0; k < config->num_columns[j]; ++k) {
        _set_dot(i, j, k,
                 ((_dots[i][j] & _int_bit_array[j]) == _int_bit_array[j]) ? 1
                                                                          : 0,
                 false);
        fire_shift_register(true);
        debug_printf(".");
      }
    }
  }
  if (DEBUG)
    debug_printf(" DONE.\n");
  else if (config->verbose)
    Serial.printf("Done inversing display.\n");
}

// fill all dots, save to _next_dots and paint
void Flippie::fill() {
  debug_printf("Start filling the display ");
  unsigned char x = 0;
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    for (unsigned char j = 0; j < config->num_modules; ++j) {
      _dots[i][j] = UINT_MAX;
      for (unsigned char k = 0; k < config->num_columns[j]; ++k) {
        _set_dot(i, j, k, 1, false);
        fire_shift_register(true);
        debug_printf(".");
      }
    }
  }
  if (DEBUG)
    debug_printf("DONE.\n");
  else if (config->verbose)
    Serial.printf("Done filling display.\n");
}

// set/get row_set
void Flippie::set_row_set(unsigned char row) {
  debug_printf("Setting ROW_SET %u ... ", row);
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  // reset all RST rows
  if (row < BROSE_MAX_ROWS) {
    set_row_rst(BROSE_MAX_ROWS);
  }
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    if (i == row) {
      _shift_register[config->sr_row_set_pins[i] / SHIFT_REGISTER_WIDTH] |=
          _byte_bit_array[config->sr_row_set_pins[i] % SHIFT_REGISTER_WIDTH];
    } else {
      _shift_register[config->sr_row_set_pins[i] / SHIFT_REGISTER_WIDTH] &=
          (SHIFT_REGISTER_MAXVAL -
           _byte_bit_array[config->sr_row_set_pins[i] % SHIFT_REGISTER_WIDTH]);
    }
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("DONE.\n");
}
unsigned char Flippie::get_row_set() {
  for (unsigned char row = 0; row < BROSE_MAX_ROWS; ++row) {
    if ((_shift_register[config->sr_row_set_pins[row] / SHIFT_REGISTER_WIDTH] &
         _byte_bit_array[config->sr_row_set_pins[row] % SHIFT_REGISTER_WIDTH]) >
        FP2800A_LOW)
      return row;
  }
  return BROSE_MAX_ROWS;
}

// set/get row_rst
void Flippie::set_row_rst(unsigned char row) {
  debug_printf("Setting ROW_RST %u ... ", row);
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  // reset all SET rows
  if (row < BROSE_MAX_ROWS) {
    set_row_set(BROSE_MAX_ROWS);
  }
  for (unsigned char i = 0; i < config->num_rows; ++i) {
    if (i == row) {
      _shift_register[config->sr_row_rst_pins[i] / SHIFT_REGISTER_WIDTH] |=
          _byte_bit_array[config->sr_row_rst_pins[i] % SHIFT_REGISTER_WIDTH];
    } else {
      _shift_register[config->sr_row_rst_pins[i] / SHIFT_REGISTER_WIDTH] &=
          (SHIFT_REGISTER_MAXVAL -
           _byte_bit_array[config->sr_row_rst_pins[i] % SHIFT_REGISTER_WIDTH]);
    }
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("DONE.\n");
}
unsigned char Flippie::get_row_rst() {
  for (unsigned char row = 0; row < BROSE_MAX_ROWS; ++row) {
    if ((_shift_register[config->sr_row_rst_pins[row] / SHIFT_REGISTER_WIDTH] &
         _byte_bit_array[config->sr_row_rst_pins[row] %
                         SHIFT_REGISTER_WIDTH]) ==
        _byte_bit_array[config->sr_row_rst_pins[row] % SHIFT_REGISTER_WIDTH])
      return row;
  }
  return BROSE_MAX_ROWS;
}

// set/get coolumn
void Flippie::set_column(unsigned char column) {
  debug_printf("Setting COLUMN %u ... ", column);
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  for (unsigned char i = 0; i < FP2800A_COLUMN_CODE_LINES; ++i) {
    if (column < FP2800A_MAX_COLUMNS &&
        FP2800A_COLUMN_CODES[column][i] == FP2800A_HGH) {
      _shift_register[config->sr_column_code_pins[i] / SHIFT_REGISTER_WIDTH] =
          _shift_register[config->sr_column_code_pins[i] /
                          SHIFT_REGISTER_WIDTH] |
          _byte_bit_array[config->sr_column_code_pins[i] %
                          SHIFT_REGISTER_WIDTH];
    } else {
      _shift_register[config->sr_column_code_pins[i] / SHIFT_REGISTER_WIDTH] =
          _shift_register[config->sr_column_code_pins[i] /
                          SHIFT_REGISTER_WIDTH] &
          (SHIFT_REGISTER_MAXVAL -
           _byte_bit_array[config->sr_column_code_pins[i] %
                           SHIFT_REGISTER_WIDTH]);
    }
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("... DONE.\n");
}
unsigned char Flippie::get_column() {
  bool found = true;
  for (unsigned char column = 0; column < FP2800A_MAX_COLUMNS; ++column) {
    found = true;
    for (unsigned char i = 0; i < FP2800A_COLUMN_CODE_LINES; ++i) {
      found &= ((FP2800A_COLUMN_CODES[column][i] == FP2800A_HGH &
                 ((_shift_register[config->sr_column_code_pins[i] /
                                   SHIFT_REGISTER_WIDTH] &
                   _byte_bit_array[config->sr_column_code_pins[i] %
                                   SHIFT_REGISTER_WIDTH]) ==
                  _byte_bit_array[config->sr_column_code_pins[i] %
                                  SHIFT_REGISTER_WIDTH])) ||
                (FP2800A_COLUMN_CODES[column][i] == FP2800A_LOW &
                 ((_shift_register[config->sr_column_code_pins[i] /
                                   SHIFT_REGISTER_WIDTH] &
                   _byte_bit_array[config->sr_column_code_pins[i] %
                                   SHIFT_REGISTER_WIDTH]) == FP2800A_LOW)));
    }
    if (found)
      return column;
  }
  return FP2800A_MAX_COLUMNS;
}

// set/get address (ADDR1-ADDR7)
void Flippie::set_address(unsigned char address) {
  debug_printf("Setting ADDRESS %u ... ", address);
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  for (unsigned char i = 0; i < BROSE_ADDR_LINES; ++i) {
    if ((address & _byte_bit_array[i]) == _byte_bit_array[i]) {
      _shift_register[config->sr_address_pins[i] / SHIFT_REGISTER_WIDTH] |=
          _byte_bit_array[config->sr_address_pins[i] % SHIFT_REGISTER_WIDTH];
    }
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("DONE.\n");
}
unsigned char Flippie::get_address() {
  unsigned char address = 0;
  for (unsigned char i = 0; i < BROSE_ADDR_LINES; ++i) {
    if ((_shift_register[config->sr_address_pins[i] / SHIFT_REGISTER_WIDTH] &
         _byte_bit_array[config->sr_address_pins[i] % SHIFT_REGISTER_WIDTH]) ==
        _byte_bit_array[config->sr_address_pins[i] % SHIFT_REGISTER_WIDTH]) {
      address |= _byte_bit_array[i];
    }
  }
  return address;
}

// set FP2800A direction FP2800A_HGH(1) => switches +VS, FP2800A_LOW(0) switches
// GND
void Flippie::set_d(unsigned char d) {
  debug_printf("Setting D %u ... ", d);
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  if (d == FP2800A_HGH) {
    _shift_register[config->sr_d_pin / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_d_pin % SHIFT_REGISTER_WIDTH];
  } else {
    _shift_register[config->sr_d_pin / SHIFT_REGISTER_WIDTH] &=
        (SHIFT_REGISTER_MAXVAL -
         _byte_bit_array[config->sr_d_pin % SHIFT_REGISTER_WIDTH]);
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("DONE.\n");
}
unsigned char Flippie::get_d() {
  return ((_shift_register[config->sr_d_pin / SHIFT_REGISTER_WIDTH] &
           _byte_bit_array[config->sr_d_pin % SHIFT_REGISTER_WIDTH]) ==
          _byte_bit_array[config->sr_d_pin % SHIFT_REGISTER_WIDTH])
             ? 1
             : 0;
}

// clear shift-registers
void Flippie::clear_shift_register(bool fire_after_clear) {
  debug_printf("Clearing shift-register %s... ",
               fire_after_clear ? "and fire afeterwards " : " ");
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  for (unsigned char i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = 0;
  }
  // fireing shift-register if requested
  if (fire_after_clear) {
    fire_shift_register(false);
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("DONE.\n");
}

// fill shift-registers
void Flippie::fill_shift_register(bool fire_after_fill) {
  debug_printf("Filling shift-register %s... ",
               fire_after_fill ? "and fire afeterwards " : " ");
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  for (unsigned char i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = UCHAR_MAX;
  }
  // fireing shift-register if requested
  if (fire_after_fill) {
    fire_shift_register(false);
  }
  debug_printf("\n%s\n", shift_register_as_json_short_string().c_str());
  debug_printf("DONE.\n");
}

// assemble the shift-register for a specific dots
void Flippie::_set_dot(unsigned char row, unsigned char module,
                       unsigned char column, unsigned char state, bool save) {
  unsigned char i;

  // clear shift-register
  for (i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = 0;
  }

  // set state of the selected row
  if (state == 1) {
    _shift_register[config->sr_row_set_pins[row] / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_row_set_pins[row] % SHIFT_REGISTER_WIDTH];
  } else {
    _shift_register[config->sr_row_rst_pins[row] / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_row_rst_pins[row] % SHIFT_REGISTER_WIDTH];
  }

  // set column code (B1-A0)
  for (i = 0; i < FP2800A_COLUMN_CODE_LINES; ++i) {
    if (FP2800A_COLUMN_CODES[(FP2800A_MAX_COLUMNS -
                              config->num_columns[module]) +
                             column][i] == FP2800A_HGH) {
      _shift_register[config->sr_column_code_pins[i] / SHIFT_REGISTER_WIDTH] |=
          _byte_bit_array[config->sr_column_code_pins[i] %
                          SHIFT_REGISTER_WIDTH];
    }
  }

  // set address (ADDR1-ADDR7)
  for (i = 0; i < BROSE_ADDR_LINES; ++i) {
    if ((config->addresses[module] & _byte_bit_array[i]) ==
        _byte_bit_array[i]) {
      _shift_register[config->sr_address_pins[i] / SHIFT_REGISTER_WIDTH] |=
          _byte_bit_array[config->sr_address_pins[i] % SHIFT_REGISTER_WIDTH];
    }
  }

  // set D
  if (state == 1) {
    _shift_register[config->sr_d_pin / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_d_pin % SHIFT_REGISTER_WIDTH];
  }

  if (save) {
    if (state == 1) {
      _dots[row][module] |= _int_bit_array[column];
    } else {
      _dots[row][module] &= (UINT32_MAX - (_int_bit_array[column]));
    }
  }
}
void Flippie::set_dot(unsigned char row, unsigned char module,
                      unsigned char column, unsigned char state) {
  _set_dot(row, module, column, state, true);
  fire_shift_register(true);
}
unsigned char Flippie::get_dot(unsigned char row, unsigned char module,
                               unsigned char column) {
  return (((unsigned char)(_dots[row][module] << column)) & _byte_bit_array[0]);
}

// fire a given shift-register according to pins given
void Flippie::fire_shift_register(bool enable, bool persistant) {
  debug_printf("Fireing shift-register (enable=%s, persistant=%s)... ",
               enable ? "true" : "false", persistant ? "true" : "false");
  // set LEDs
  if (led_A_on) {
    _shift_register[config->sr_led_a_pin / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_led_a_pin % SHIFT_REGISTER_WIDTH];
  } else {
    _shift_register[config->sr_led_a_pin / SHIFT_REGISTER_WIDTH] &=
        255 - _byte_bit_array[config->sr_led_a_pin % SHIFT_REGISTER_WIDTH];
  }
  if (led_B_on) {
    _shift_register[config->sr_led_b_pin / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_led_b_pin % SHIFT_REGISTER_WIDTH];
  } else {
    _shift_register[config->sr_led_b_pin / SHIFT_REGISTER_WIDTH] &=
        255 - _byte_bit_array[config->sr_led_b_pin % SHIFT_REGISTER_WIDTH];
  }
  if (config->led_mode == LED_MODE_FLASHING) {
    led_C_on = flashing_led_C_on;
    flashing_led_C_on = !flashing_led_C_on;
  }
  if (led_C_on) {
    _shift_register[config->sr_led_c_pin / SHIFT_REGISTER_WIDTH] |=
        _byte_bit_array[config->sr_led_c_pin % SHIFT_REGISTER_WIDTH];
  } else {
    _shift_register[config->sr_led_c_pin / SHIFT_REGISTER_WIDTH] &=
        255 - _byte_bit_array[config->sr_led_c_pin % SHIFT_REGISTER_WIDTH];
  }

  // just in case => defined start point
  digitalWrite(config->clock_pin, LOW);
  digitalWrite(config->latch_pin, LOW);

  // shift out (reverse order) shift-register unsigned char array
  for (int i = (NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH) - 1; i >= 0;
       --i) {
    digitalWrite(config->serial_data_pin,
                 (_shift_register[i / SHIFT_REGISTER_WIDTH] &
                  _byte_bit_array[i % SHIFT_REGISTER_WIDTH]) ==
                         _byte_bit_array[i % SHIFT_REGISTER_WIDTH]
                     ? HIGH
                     : LOW);
    digitalWrite(config->clock_pin, HIGH);
    digitalWrite(config->clock_pin, LOW);
  }
  // storage register
  digitalWrite(config->latch_pin, HIGH);
  digitalWrite(config->latch_pin, LOW);

  if (enable) {
    // fire using ADDRSHIFT_REGISTER_WIDTH aka NOT_EN => FP2800A enable (E)
    digitalWrite(config->not_enable_pin, LOW);
    if (!persistant) {
      delay(FP2800A_ACTIVE_TIME_IN_MSEC);
      digitalWrite(config->not_enable_pin, HIGH);
    }
  } else {
    digitalWrite(config->not_enable_pin, HIGH);
  }

  if (config->verbose)
    Serial.print(enable ? "X" : "x");

  debug_printf("DONE.\n");
  yield();
}
void Flippie::fire_shift_register(bool enable) {
  fire_shift_register(enable, false);
}

// fire a given shift-register according to pins given
// print shift-register
String Flippie::shift_register_as_string() {
  char *tmp =
      new char[(3 * ((NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH) + 1)) +
               1];
  unsigned char tmp_pos = 0;

  tmp_pos += sprintf(tmp + tmp_pos, "SRA: ");
  for (unsigned char i = NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH;
       0 < i--;) {
    tmp_pos += sprintf(tmp + tmp_pos, "%u", i / SHIFT_REGISTER_WIDTH);
  }

  tmp_pos += sprintf(tmp + tmp_pos, "\nSRA: ");
  for (unsigned char i = NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH;
       0 < i--;) {
    tmp_pos += sprintf(tmp + tmp_pos, "%u", i % SHIFT_REGISTER_WIDTH);
  }

  tmp_pos += sprintf(tmp + tmp_pos, "\nSRD: ");
  for (unsigned char i = NUMBER_OF_SHIFT_REGISTERS * SHIFT_REGISTER_WIDTH;
       0 < i--;) {
    tmp[tmp_pos] = (_shift_register[i / SHIFT_REGISTER_WIDTH] &
                    _byte_bit_array[i % SHIFT_REGISTER_WIDTH]) ==
                           _byte_bit_array[i % SHIFT_REGISTER_WIDTH]
                       ? 'H'
                       : 'L';
    tmp_pos++;
  }
  sprintf(tmp + tmp_pos, "\n\0");
  String s(tmp);
  free(tmp);
  return s;
}

// return shift-register in shortend form as json string
String Flippie::shift_register_as_json_short_string() {
  return binary_array_as_bit_string(_shift_register, NUMBER_OF_SHIFT_REGISTERS,
                                    true);
}
String Flippie::binary_array_as_bit_string(unsigned char *arr, unsigned int len,
                                           bool quotes) {
  char *bit_string =
      (char *)malloc(len * (8 * sizeof(unsigned char)) + (quotes ? 3 : 1));
  unsigned int bit_string_pos = 0;

  if (quotes)
    bit_string[bit_string_pos++] = '"';

  for (unsigned int i = 0; i < len; ++i)
    for (unsigned int j = 0; j < (8 * sizeof(unsigned char)); ++j)
      bit_string[bit_string_pos++] =
          (((arr[i] & _byte_bit_array[j]) == _byte_bit_array[j]) ? '1' : '0');

  if (quotes)
    bit_string[bit_string_pos++] = '"';

  bit_string[bit_string_pos] = 0;
  String s(bit_string);
  free(bit_string);
  return s;
}

String Flippie::dots_as_string(unsigned int **dots) {
  unsigned int c_len = 0;
  unsigned char i, j, k;
  for (j = 0; j < config->num_modules; ++j) {
    c_len += config->num_columns[j];
  }
  c_len = ((c_len + 10) * (config->num_rows + 3)) + 1;

  char *c = (char *)malloc(c_len);
  c_len = 0;

  c_len += sprintf(c + c_len, "\nMM ");
  for (j = 0; j < config->num_modules; ++j) {
    for (k = 0; k < config->num_columns[j]; ++k) {
      c_len += sprintf(c + c_len, "%1u", j);
    }
  }

  c_len += sprintf(c + c_len, "\nCC ");
  for (j = 0; j < config->num_modules; ++j) {
    for (k = 0; k < config->num_columns[j]; ++k) {
      c_len += sprintf(c + c_len, "%1u", k / 10);
    }
  }
  c_len += sprintf(c + c_len, "\nCC ");
  for (j = 0; j < config->num_modules; ++j) {
    for (k = 0; k < config->num_columns[j]; ++k) {
      c_len += sprintf(c + c_len, "%1u", k % 10);
    }
  }

  for (i = 0; i < config->num_rows; ++i) {
    c_len += sprintf(c + c_len, "\n%2u ", i);
    for (j = 0; j < config->num_modules; ++j) {
      for (k = 0; k < config->num_columns[j]; ++k) {
        c[c_len++] = ((dots[i][j] & 1 << k) == 1 << k) ? '@' : '.';
      }
    }
  }
  c[c_len++] = '\n';
  c[c_len] = 0;
  String s(c);
  free(c);
  return s;
}

// return shift-register in shortend form as json string
String Flippie::shift_register_as_json() {
  char *r = (char *)malloc(1024);
  unsigned char r_len =
      sprintf(r, "{\n\t\"address\": %i,\n\t\"column\": %i,\n\t\"row_set\": "
                 "%i,\n\t\"row_rst\": %i,\n\t\"led_A\": %u,\n\t\"led_B\": "
                 "%u,\n\t\"led_C\": %u,\n\t\"d\": %u\n}\n\0",
              get_address(), get_column(), get_row_set(), get_row_rst(),
              led_A_on ? 1 : 0, led_B_on ? 1 : 0, led_C_on ? 1 : 0, get_d());
  String s(r);
  free(r);
  return s;
}

// set all possible shift-register outputs (filling the shift-register and
// fire it)
void Flippie::test(unsigned char test_bit, unsigned char state) {
  if (DEBUG) {
    if (state == 0) {
      _shift_register[test_bit / SHIFT_REGISTER_WIDTH] &=
          (SHIFT_REGISTER_MAXVAL -
           _byte_bit_array[test_bit % SHIFT_REGISTER_WIDTH]);
    } else {
      _shift_register[test_bit / SHIFT_REGISTER_WIDTH] |=
          _byte_bit_array[test_bit % SHIFT_REGISTER_WIDTH];
    }
    Serial.printf("set bit-position %u(%u,%u) to %u => [ %u", test_bit,
                  test_bit / SHIFT_REGISTER_WIDTH,
                  test_bit % SHIFT_REGISTER_WIDTH, state, _shift_register[0]);
    for (unsigned char i = 1; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
      Serial.printf(", %u", _shift_register[i]);
    }
    Serial.println("]");
    fire_shift_register(false);
  }
}
