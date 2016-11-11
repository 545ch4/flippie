#include "flippie.h"

Flippie::Flippie() {}

Flippie::Flippie(flippie_t f) {
  unsigned int i;

  config = f;

  // initialze shift-register as NUMBER_OF_SHIFT_REGISTERS * 8 (unsigned char)
  _shift_register = (byte *)calloc(NUMBER_OF_SHIFT_REGISTERS, sizeof(byte));

  // shift-register LED_A, LED_B and LED_C
  _led_a_on = true;
  _led_b_on = true;
  _led_c_on = true;

  // define pins (not srPins) as outputs
  pinMode(config.output_enable_pin, OUTPUT);
  pinMode(config.clock_pin, OUTPUT);
  pinMode(config.serial_data_pin, OUTPUT);
  pinMode(config.latch_pin, OUTPUT);
  pinMode(config.clear_pin, OUTPUT);
  pinMode(config.enable_pin, OUTPUT);
  // don't enable
  digitalWrite(config.enable_pin, HIGH);
  // enable +VS
  digitalWrite(config.vs_enable_pin, LOW);

  // reset shift-register
  digitalWrite(config.clear_pin, LOW);
  delayMicroseconds(SHIFT_REGISTER_CLEAR_TIME_IN_USEC);
  digitalWrite(config.clear_pin, HIGH);

  // init shift-register to tristate all outputs
  digitalWrite(config.output_enable_pin, HIGH);
  digitalWrite(config.clock_pin, LOW);
  digitalWrite(config.serial_data_pin, LOW);
  digitalWrite(config.latch_pin, LOW);
  digitalWrite(config.clear_pin, LOW);

  // init shift-register to ALL-LOW and just flash LED_A and LED_B shortly
  fire_shift_register(false);
  _led_a_on = false;
  _led_b_on = false;
  delay(1000);
  fire_shift_register(false);

  // initialze _dots and _next_dots
  // array of rows => array of modules => columns are encoded bit-wise in an integer (32-bit wide => 32 column max)
  _dots = (unsigned int **)malloc(config.num_rows * sizeof(unsigned int *));
  _next_dots = (unsigned int **)malloc(config.num_rows * sizeof(unsigned int *));
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    _dots[i] = (unsigned int *)calloc(config.num_modules, sizeof(unsigned int));
    _next_dots[i] = (unsigned int *)calloc(config.num_modules, sizeof(unsigned int));
  }

  // init fast bit-wise comparator array (int-sized)
  _int_bit_array = (unsigned int *)malloc(32 * sizeof(unsigned int));
  for(i = 0; i < 32; ++i) {
    _int_bit_array[i] = 1<<i;
  }
  // init fast bit-wise comparator array (byte-sized)
  _byte_bit_array = (byte *)malloc(8 * sizeof(byte));
  for(i = 0; i < 8; ++i) {
    _byte_bit_array[i] = 1<<i;
  }
}


// copy current state _next_dots to _dots
void Flippie::cycle_dots() {
   memcpy(_dots, _next_dots, config.num_rows * sizeof(unsigned int *));
   for(unsigned int i = 0; i < config.num_rows; ++i) {
     memcpy(_dots[i], _next_dots[i], config.num_modules * sizeof(unsigned int));
   }
}

// paint content of _next_dots
// only paint differnces to _dots unless override is true (default = false)
void Flippie::paint() {
   paint(false);
}
void Flippie::paint(bool override_former_dot_state) {
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    for(unsigned int j = 0; j < config.num_modules; ++j) {
      for(unsigned int k = 0; k < config.num_columns[j]; ++k) {
        if(override_former_dot_state || (_dots[i][j] & _int_bit_array[k]) != (_next_dots[i][j] & _int_bit_array[k])) {
          fill_shift_register_and_fire(i, j, k, (_next_dots[i][j] & _int_bit_array[k]) == _int_bit_array[k] ? 1 : 0, FP2800A_ACTIVE_TIME_IN_USEC);
        }
      }
    }
  }
  // _next_dots are the new _dots
  cycle_dots();
}

// repaint (magnetize) the whole display
void Flippie::magnetize(unsigned int duration) {
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    for(unsigned int j = 0; j < config.num_modules; ++j) {
      for(unsigned int k = 0; k < config.num_columns[j]; ++k) {
          fill_shift_register_and_fire(i, j, k, _dots[i][j], duration);
      }
    }
  }
  // _next_dots are the new _dots
  cycle_dots();
}


// set content of _next_dots and paint
void Flippie::paint(unsigned int ** dots) {
  memcpy(_next_dots, dots, config.num_rows * sizeof(unsigned int *));
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    memcpy(_next_dots[i], dots[i], config.num_modules * sizeof(unsigned int));
  }
  paint();
}

// clear all dots and paint
void Flippie::clear() {
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    for(unsigned int j = 0; j < config.num_modules; ++j) {
      _next_dots[i][j] = 0;
      _dots[i][j] = 0;
    }
  }
  paint(true);
}

// calc inverse of _dots, save to _next_dots and paint
void Flippie::inverse() {
  unsigned int x = 0;
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    for(unsigned int j = 0; j < config.num_modules; ++j) {
      _next_dots[i][j] = UINT_MAX - _dots[i][j];
    }
  }
  paint(true);
}

// fill all dots, save to _next_dots and paint
void Flippie::fill() {
  unsigned int x = 0;
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    for(unsigned int j = 0; j < config.num_modules; ++j) {
      _next_dots[i][j] = UINT_MAX;
      _dots[i][j] = UINT_MAX;
    }
  }
  paint(true);
}

// clear shift-registers
void Flippie::clear_shift_register(bool fire_after_clear) {
  for(unsigned int i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = 0;
  }
  // fireing shift-register if requested
  if(fire_after_clear) {
    fire_shift_register_with_print(false);
  }
}

// return shift-register
String Flippie::shift_register_as_string() {
   char *bit_string = (char *)malloc(((NUMBER_OF_SHIFT_REGISTERS * sizeof(byte)) + 1) * sizeof(char));
   unsigned int l = 0;
   for(unsigned int i = 0; i < NUMBER_OF_SHIFT_REGISTERS; i++) {
      for(unsigned int j = 0; j < sizeof(byte); j++) {
         bit_string[l] = ((((_shift_register[i]<<j) & 1) == 1) ? '1' : '0');
         l++;
      }
   }
   bit_string[l] = '\0';
   return String(bit_string);
}

// set LEDs (filling the shift-register and fire it)
void Flippie::paint_leds(unsigned int led_a_state, unsigned int led_b_state, unsigned int led_c_state) {
  unsigned int i;

  // clear shift-register
  clear_shift_register(false);

  if(led_a_state == 1) {
     _led_a_on = true;
    _shift_register[config.sr_led_a_pin/8] |= _byte_bit_array[config.sr_led_a_pin%8];
  } else _led_a_on = false;


  if(led_b_state == 1) {
     _led_b_on = true;
     _shift_register[config.sr_led_b_pin/8] |= _byte_bit_array[config.sr_led_b_pin%8];
  } else _led_b_on = false;


  if(led_c_state == 1) {
     _led_c_on = true;
    _shift_register[config.sr_led_c_pin/8] |= _byte_bit_array[config.sr_led_c_pin%8];
  } else _led_c_on = false;

  // fireing
  fire_shift_register_with_print(false);
}

// set all possible shift-register outputs (filling the shift-register and fire it)
void Flippie::test(unsigned int test_bit, unsigned int state) {
  if(state == 0) {
    _shift_register[test_bit/8] &= (255 - _byte_bit_array[test_bit%8]);
  } else {
    _shift_register[test_bit/8] |= _byte_bit_array[test_bit%8];
  }
  Serial.printf("set bit-position %u(%u,%u) to %u => [ %u", test_bit, test_bit/8, test_bit%8, state, _shift_register[0]);
  for(unsigned int i = 1; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    Serial.printf(", %u", _shift_register[i]);
  }
  Serial.println("]");
  fire_shift_register_with_print(false);
}

void Flippie::set_row(unsigned int row) {
  // reset all GND rows
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    _shift_register[config.sr_set_row_pins[i]/8] &= (255 - _byte_bit_array[config.sr_set_row_pins[i]%8]);
  }
  _shift_register[config.sr_set_row_pins[row]/8] |= _byte_bit_array[config.sr_set_row_pins[row]%8];

  // fireing shift-register
  fire_shift_register_with_print(false);
}

void Flippie::rst_row(unsigned int row) {
  // reset all +VS rows
  for(unsigned int i = 0; i < config.num_rows; ++i) {
    _shift_register[config.sr_rst_row_pins[i]/8] &= (255 - _byte_bit_array[config.sr_rst_row_pins[i]%8]);
  }
  _shift_register[config.sr_rst_row_pins[row]/8] |= _byte_bit_array[config.sr_rst_row_pins[row]%8];

  // fireing shift-register
  fire_shift_register_with_print(false);
}

void Flippie::set_column(unsigned int column){
  for(unsigned int i = 0; i < 5; ++i) {
    if(fp2800a_column_codes[column][i] == 1) {
        _shift_register[config.sr_column_code_pins[i]/8] |= _byte_bit_array[config.sr_column_code_pins[i]%8];
    } else {
      _shift_register[config.sr_column_code_pins[i]/8] &= (255 - _byte_bit_array[config.sr_column_code_pins[i]%8]);
    }
  }

  // fireing shift-register
  fire_shift_register_with_print(false);
}

// set address (ADDR1-ADDR7)
void Flippie::set_address(byte address) {
  for(unsigned int i = 0; i < 7; ++i) {
    if((address>>i) & 1 == 1) {
      _shift_register[config.sr_address_pins[i]/8] |= _byte_bit_array[config.sr_address_pins[i]%8];
    }
  }
  // fireing shift-register
  fire_shift_register_with_print(false);
}

// set FP2800A direction HIGH => switches +VS, LOW switches GND
void Flippie::set_data(unsigned int state) {
  if(state == 1) {
    _shift_register[config.sr_data_pin/8] |= _byte_bit_array[config.sr_data_pin%8];
  } else {
    _shift_register[config.sr_data_pin/8] &= (255 - _byte_bit_array[config.sr_data_pin%8]);
  }
  // fireing shift-register
  fire_shift_register_with_print(false);
}

// set last address bit to enable the module
void Flippie::set_enable(unsigned int state) {
  fire_shift_register_with_print(state == 1 ? true : false);
}


// assemble the shift-register and fire it, resetting shift-register and set all output to low afterwards
void Flippie::fill_shift_register_and_fire(unsigned int row, unsigned int module, unsigned int column, unsigned int state, unsigned int duration) {
  unsigned int i;

  // clear shift-register
  for(i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = 0;
  }

  // set state of the selected row
  if(state == 1) {
    _shift_register[config.sr_set_row_pins[row]/8] |= _byte_bit_array[config.sr_set_row_pins[row]%8];
  } else {
    _shift_register[config.sr_rst_row_pins[row]/8] |= _byte_bit_array[config.sr_rst_row_pins[row]%8];
  }

  // set column code (B1-A0)
  for(i = 0; i < 5; ++i) {
    if(fp2800a_column_codes[(28 - config.num_columns[module]) + column][i] == 1) {
      _shift_register[config.sr_column_code_pins[i]/8] |= _byte_bit_array[config.sr_column_code_pins[i]%8];
    }
  }

  // set address (ADDR1-ADDR7)
  for(i = 0; i < 7; ++i) {
    if(config.addresses[module]>>i & 1 == 1) {
      _shift_register[config.sr_address_pins[i]/8] |= _byte_bit_array[config.sr_address_pins[i]%8];
    }
  }

  // set state (DATA)
  if(state == 0) {
    _shift_register[config.sr_data_pin/8] |= _byte_bit_array[config.sr_data_pin%8];
  }

  // set toggle between LED_A/LED_B
  if(_led_a_on) {
    _shift_register[config.sr_led_a_pin/8] |= _byte_bit_array[config.sr_led_a_pin%8];
    _led_a_on = false;
    _shift_register[config.sr_led_b_pin/8] -= _byte_bit_array[config.sr_led_b_pin%8];
    _led_b_on = true;
  } else {
    _shift_register[config.sr_led_a_pin/8] -= _byte_bit_array[config.sr_led_a_pin%8];
    _led_a_on = true;
    _shift_register[config.sr_led_b_pin/8] |= _byte_bit_array[config.sr_led_b_pin%8];
    _led_a_on = false;
  }

  // set LED C to state
  _led_c_on = state == 1;
  if(_led_c_on) {
    _shift_register[config.sr_led_c_pin/8] |= _byte_bit_array[config.sr_led_c_pin%8];
   } else {
      _shift_register[config.sr_led_c_pin/8] -= _byte_bit_array[config.sr_led_c_pin%8];
   }

  // fireing shift-register
  fire_shift_register(true);
}

// fire a given shift-register according to pins given
void Flippie::fire_shift_register(bool enable) {
  // just in case => defined start point
  digitalWrite(config.clock_pin, LOW);
  // just in case => clear shift-register
  digitalWrite(config.clear_pin, LOW);
  digitalWrite(config.clear_pin, HIGH);

  // shift out (reverse order) shift-register byte array
  for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
    digitalWrite(config.serial_data_pin, (_shift_register[i/8] & _byte_bit_array[i%8]) == _byte_bit_array[i%8] ? HIGH : LOW);
    digitalWrite(config.clock_pin, HIGH);
    digitalWrite(config.clock_pin, LOW);
  }
  digitalWrite(config.latch_pin, HIGH);
  digitalWrite(config.latch_pin, LOW);

  if(enable) {
     // fire using ADDR8 aka NOT_EN => FP2800A enable (E)
     digitalWrite(config.enable_pin, HIGH);
     delayMicroseconds(FP2800A_ACTIVE_TIME_IN_USEC);
     digitalWrite(config.enable_pin, LOW);
  }
  yield();
}

// fire a given shift-register according to pins given
// print additional info
void Flippie::fire_shift_register_with_print(bool enable) {
  // shift out (reverse order) shift-register byte array
  Serial.print("SRA: ");
  for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
    Serial.printf("%u", i/8);
  }
  Serial.print("\nSRA: ");
  for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
    Serial.printf("%u", i%8);
  }

  Serial.print("\nSRD: ");
  for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
    if((_shift_register[i/8] & _byte_bit_array[i%8]) == _byte_bit_array[i%8]) {
      Serial.print('H');
    } else {
      Serial.print('L');
    }
  }
  Serial.print('\n');
  fire_shift_register(enable);
}
