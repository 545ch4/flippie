#include "flippie.h"

Flippie::Flippie() {
}

void Flippie::init(flippie_t f) {
  unsigned int i;

  _f = f;

  // set rows and columns for easier access
  rows = _f.num_rows;
  modules = _f.num_modules;
  columns = 0;
  for(i = 0; i < _f.num_modules; ++i) {
    columns += _f.num_columns[i];
  }

  // define pins (not srPins) as outputs
  pinMode(_f.address_enable_pin, OUTPUT);
  digitalWrite(_f.address_enable_pin, LOW);

  // tristate all outputs
  pinMode(_f.output_enable_pin, OUTPUT);
  digitalWrite(_f.output_enable_pin, HIGH);

  pinMode(_f.clock_pin, OUTPUT);
  digitalWrite(_f.clock_pin, LOW);

  pinMode(_f.serial_data_pin, OUTPUT);
  digitalWrite(_f.serial_data_pin, LOW);

  pinMode(_f.latch_pin, OUTPUT);
  digitalWrite(_f.latch_pin, LOW);

  pinMode(_f.clear_pin, OUTPUT);
  digitalWrite(_f.clear_pin, LOW);

  // reset shift-register
  digitalWrite(_f.clear_pin, LOW);
  delayMicroseconds(SHIFT_REGISTER_CLEAR_TIME_IN_USEC);
  digitalWrite(_f.clear_pin, HIGH);

  // setting all shift-register outputs to low
  digitalWrite(_f.output_enable_pin, LOW);
  digitalWrite(_f.latch_pin, HIGH);
  delayMicroseconds(SHIFT_REGISTER_LATCH_TIME_IN_USEC);
  digitalWrite(_f.latch_pin, LOW);

  // initialze _dots and _next_dots
  _dots = (unsigned int **)malloc(_f.num_rows * sizeof(unsigned int *));
  _next_dots = (unsigned int **)malloc(_f.num_rows * sizeof(unsigned int *));
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    _dots[i] = (unsigned int *)calloc(_f.num_modules, sizeof(unsigned int));
    _next_dots[i] = (unsigned int *)calloc(_f.num_modules, sizeof(unsigned int));
  }

  // initialze shift-register as NUMBER_OF_SHIFT_REGISTERS * 8 (unsigned char)
  // one for outputs and one for clearing (keep leds)
  _shift_register = (byte *)calloc(NUMBER_OF_SHIFT_REGISTERS, sizeof(byte));
  _shift_register_clear = (byte *)calloc(NUMBER_OF_SHIFT_REGISTERS, sizeof(byte));

  // shift-register activity LEDs
  _activity = 0;

  // shift-register status LED
  _status_led = 0;

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

// paint content of _next_dots
void Flippie::paint(bool override) {
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    for(unsigned int j = 0; j < _f.num_modules; ++j) {
      for(unsigned int k = 0; k < _f.num_columns[j]; ++k) {
//        if(override || (_dots[i][j] & _int_bit_array[k]) != (_next_dots[i][j] & _int_bit_array[k])) {
          fill_shift_register_and_fire(i, j, k, (_next_dots[i][j] & _int_bit_array[k]) == _int_bit_array[k] ? 1 : 0, FP2800A_ACTIVE_TIME_IN_USEC);
//        }
      }
    }
  }
  // copy current state
  memcpy(_dots, _next_dots, _f.num_rows * sizeof(unsigned int *));
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    memcpy(_dots[i], _next_dots[i], _f.num_modules * sizeof(unsigned int));
  }
}

void Flippie::magnitize(unsigned int state, unsigned int duration) {
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    for(unsigned int j = 0; j < _f.num_modules; ++j) {
      for(unsigned int k = 0; k < _f.num_columns[j]; ++k) {
          fill_shift_register_and_fire(i, j, k, state, duration);
      }
    }
  }
  // copy current state
  memcpy(_dots, _next_dots, _f.num_rows * sizeof(unsigned int *));
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    memcpy(_dots[i], _next_dots[i], _f.num_modules * sizeof(unsigned int));
  }
}


// set content of _next_dots and paint
void Flippie::paint(unsigned int ** dots) {
  memcpy(_next_dots, dots, _f.num_rows * sizeof(unsigned int *));
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    memcpy(_next_dots[i], dots[i], _f.num_modules * sizeof(unsigned int));
  }
  paint(false);
}

// clear all dots and paint
void Flippie::clear() {
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    for(unsigned int j = 0; j < _f.num_modules; ++j) {
      _next_dots[i][j] = 0;
      _dots[i][j] = 0;
    }
  }
  paint(true);
}

// calc inverse of _dots, save to _next_dots and paint
void Flippie::inverse() {
  unsigned int x = 0;
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    for(unsigned int j = 0; j < _f.num_modules; ++j) {
      _next_dots[i][j] = UINT_MAX - _dots[i][j];
    }
  }
  paint(true);
}

// fill all dots, save to _next_dots and paint
void Flippie::fill() {
  unsigned int x = 0;
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    for(unsigned int j = 0; j < _f.num_modules; ++j) {
      _next_dots[i][j] = UINT_MAX;
      _dots[i][j] = UINT_MAX;
    }
  }
  paint(true);
}

// clear both shift-registers
void Flippie::clear_shift_registers() {
  for(unsigned int i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = 0;
    _shift_register_clear[i] = 0;
  }
  // fireing shift-register
  fire_shift_register(_shift_register);
}

// set LEDs (filling the shift-register and fire it)
void Flippie::paint_leds(unsigned int led1_state, unsigned int led2_state, unsigned int led3_state) {
  unsigned int i;

  // clear shift-register
  for(i = 0; i < NUMBER_OF_SHIFT_REGISTERS; ++i) {
    _shift_register[i] = 0;
  }

  if(led1_state == 1) {
    _shift_register[_f.sr_led1_pin/8] |= _byte_bit_array[_f.sr_led1_pin%8];
  }

  if(led2_state == 1) {
    _shift_register[_f.sr_led2_pin/8] |= _byte_bit_array[_f.sr_led2_pin%8];
  }

  if(led3_state == 1) {
    _shift_register[_f.sr_led3_pin/8] |= _byte_bit_array[_f.sr_led3_pin%8];
  }

  // fireing
  fire_shift_register_with_print(_shift_register);
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
  fire_shift_register_with_print(_shift_register);
}

void Flippie::set_row_plusvs(unsigned int row) {
  // reset all GND rows
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    _shift_register[_f.sr_set_row_plusvs_pins[i]/8] &= (255 - _byte_bit_array[_f.sr_set_row_plusvs_pins[i]%8]);
  }
  _shift_register[_f.sr_set_row_plusvs_pins[row]/8] |= _byte_bit_array[_f.sr_set_row_plusvs_pins[row]%8];

  // fireing shift-register
  fire_shift_register_with_print(_shift_register);
}

void Flippie::set_row_gnd(unsigned int row) {
  // reset all +VS rows
  for(unsigned int i = 0; i < _f.num_rows; ++i) {
    _shift_register[_f.sr_set_row_gnd_pins[i]/8] &= (255 - _byte_bit_array[_f.sr_set_row_gnd_pins[i]%8]);
  }
  _shift_register[_f.sr_set_row_gnd_pins[row]/8] |= _byte_bit_array[_f.sr_set_row_gnd_pins[row]%8];

  // fireing shift-register
  fire_shift_register_with_print(_shift_register);
}

void Flippie::set_column(unsigned int column){
  for(unsigned int i = 0; i < 5; ++i) {
    if(fp2800a_column_codes[column][i] == 1) {
        _shift_register[_f.sr_column_code_pins[i]/8] |= _byte_bit_array[_f.sr_column_code_pins[i]%8];
    } else {
      _shift_register[_f.sr_column_code_pins[i]/8] &= (255 - _byte_bit_array[_f.sr_column_code_pins[i]%8]);
    }
  }

  // fireing shift-register
  fire_shift_register_with_print(_shift_register);
}

void Flippie::set_column_code(unsigned int fp2800a_column_code, unsigned int state){
  for(unsigned int i = 0; i < 5; ++i) {
    if(state == 1) {
      _shift_register[_f.sr_column_code_pins[fp2800a_column_code]/8] |= _byte_bit_array[_f.sr_column_code_pins[fp2800a_column_code]%8];
    } else {
      _shift_register[_f.sr_column_code_pins[fp2800a_column_code]/8] &= (255 - _byte_bit_array[_f.sr_column_code_pins[fp2800a_column_code]%8]);
    }
  }
  // fireing shift-register
  fire_shift_register_with_print(_shift_register);
}

// set address (ADDR0-ADDR6)
void Flippie::set_address(byte address) {
  for(unsigned int i = 0; i < 7; ++i) {
    if((address>>i) & 1 == 1) {
      _shift_register[_f.sr_address_pins[i]/8] |= _byte_bit_array[_f.sr_address_pins[i]%8];
    }
  }
  // fireing shift-register
  fire_shift_register_with_print(_shift_register);
}

// set FP2800A direction HIGH => switches +VS, LOW switches GND
void Flippie::set_data(unsigned int state) {
  if(state == 1) {
    _shift_register[_f.sr_data_pin/8] |= _byte_bit_array[_f.sr_data_pin%8];
  } else {
    _shift_register[_f.sr_data_pin/8] &= (255 - _byte_bit_array[_f.sr_data_pin%8]);
  }
  // fireing shift-register
  fire_shift_register_with_print(_shift_register);
}

// set last address bit to enable the module
void Flippie::set_enable(unsigned int state) {
  if(state == 1) {
    digitalWrite(_f.address_enable_pin, HIGH);
  } else {
    digitalWrite(_f.address_enable_pin, LOW);
  }
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
    _shift_register[_f.sr_set_row_plusvs_pins[row]/8] |= _byte_bit_array[_f.sr_set_row_plusvs_pins[row]%8];
  } else {
    _shift_register[_f.sr_set_row_gnd_pins[row]/8] |= _byte_bit_array[_f.sr_set_row_gnd_pins[row]%8];
  }

  // set column code (B1-A0)
  for(i = 0; i < 5; ++i) {
    if(fp2800a_column_codes[(28 - _f.num_columns[module]) + column][i] == 1) {
      _shift_register[_f.sr_column_code_pins[i]/8] |= _byte_bit_array[_f.sr_column_code_pins[i]%8];
    }
  }

  // set address (ADDR0-ADDR6)
  for(i = 0; i < 7; ++i) {
    if(_f.addresses[module]>>i & 1 == 1) {
      _shift_register[_f.sr_address_pins[i]/8] |= _byte_bit_array[_f.sr_address_pins[i]%8];
    }
  }

  // set state (DATA)
  if(state == 0) {
    _shift_register[_f.sr_data_pin/8] |= _byte_bit_array[_f.sr_data_pin%8];
  }

  // set toggle between LED1/LED2 and keep leds in both shift-registers
  if(_activity == 1) {
    _shift_register[_f.sr_led1_pin/8] |= _byte_bit_array[_f.sr_led1_pin%8];
    _shift_register_clear[_f.sr_led1_pin/8] |= _shift_register_clear[_f.sr_led1_pin%8];
    _activity = 0;
  } else {
    _shift_register[_f.sr_led2_pin/8] |= _byte_bit_array[_f.sr_led2_pin%8];
    _shift_register_clear[_f.sr_led2_pin/8] |= _shift_register_clear[_f.sr_led2_pin%8];
    _activity = 1;
  }

  //set LED1 to state and keep led in both shift-registers
  if(state == 1) {
    _shift_register[_f.sr_led3_pin/8] |= _byte_bit_array[_f.sr_led3_pin%8];
    _shift_register_clear[_f.sr_led3_pin/8] |= _shift_register_clear[_f.sr_led3_pin%8];
  }

  // fireing shift-register
  fire_shift_register(_shift_register);

  // fire using ADDR7 aka FP2800A enable (E)
  digitalWrite(_f.address_enable_pin, HIGH);
  delayMicroseconds(duration);
  digitalWrite(_f.address_enable_pin, LOW);


  //fireing shift-register to clear outputs (all low except LEDs)
  fire_shift_register(_shift_register_clear);
}

// fire a given shift-register according to pins given
void Flippie::fire_shift_register(byte * shift_register) {
  // just in case => defined start point
  digitalWrite(_f.clock_pin, LOW);
  // just in case => clear shift-register
  digitalWrite(_f.clear_pin, LOW);
  digitalWrite(_f.clear_pin, HIGH);

  // shift out (reverse order) shift-register byte array
  for(unsigned int i = NUMBER_OF_SHIFT_REGISTERS * 8; 0 < i--;) {
    digitalWrite(_f.serial_data_pin, (shift_register[i/8] & _byte_bit_array[i%8]) == _byte_bit_array[i%8] ? HIGH : LOW);
    digitalWrite(_f.clock_pin, HIGH);
    digitalWrite(_f.clock_pin, LOW);
  }
  digitalWrite(_f.latch_pin, HIGH);
  digitalWrite(_f.latch_pin, LOW);
}

// fire a given shift-register according to pins given
// print additional info
void Flippie::fire_shift_register_with_print(byte * shift_register) {
  // just in case => defined start point
  digitalWrite(_f.clock_pin, LOW);
  // just in case => clear shift-register
  digitalWrite(_f.clear_pin, LOW);
  digitalWrite(_f.clear_pin, HIGH);

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
    if((shift_register[i/8] & _byte_bit_array[i%8]) == _byte_bit_array[i%8]) {
      Serial.print('H');
      digitalWrite(_f.serial_data_pin, HIGH);
    } else {
      Serial.print('L');
      digitalWrite(_f.serial_data_pin, LOW);
    }
    digitalWrite(_f.clock_pin, HIGH);
    digitalWrite(_f.clock_pin, LOW);
  }
  Serial.print('\n');
  digitalWrite(_f.latch_pin, HIGH);
  digitalWrite(_f.latch_pin, LOW);
}
