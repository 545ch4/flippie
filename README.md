# flippie

![first flippie test](https://github.com/545ch4/flippie/raw/master/board/docs/flippie_first_test.gif "first flippie test")


## Basic idea and some background

Usual story: no money, lots of deadlines, unsustainable promises, social responsibility, no time at all, but the unique opportunity to get an additional time-sink. Yeah. Seconds later, I got two huge flip-dot displays I couldn't even carry myself and a lot of single modules. Soon (measured in seasons) it became obvious, that reverse engineering the RS485 based IBIS bus would not make me very happy in the long run. So I decided to throw away the original controller board and drive the flip-dot modules myself. **The goal would be a non intrusive board to directly connect any BROSE display (or array of the same) through the proprietary 60-pin connector...**  So, this is the story of that effort...


### Flip-dot display in general

A flip-dot display consists of a grid of small magnet embedded discs that are black on one side and a bright color on the other (typically white or yellow). The discs are attached to an axle with separate solenoids arranged at the ends or side. By pulsing the solenoid coil with the appropriate electrical polarity, the permanent magnet on the discs align itself with the magnetic field and thus turning (flipping) the disc.

The matrix schematic arranged on a two-dimensional area is shown below.

<img src="https://github.com/545ch4/flippie/raw/master/board/docs/flipdot.png" alt="flip-dot solenoid schematic" title="flip-dot solenoid schematic" width="400px" />


### BROSE flip-dot

Most BROSE flip-dots are equipped with an [origial FP2800A (or clone)](https://reaktor23.org/_media/projects/flipdot/fp2800-datasheet.pdf) decoder driver as column-selector. It drives one line addressed by 5-bits (A0, A1, A2, B1 and B2) in the direction of D (GND or +VS).  Based on the truth-table, 28 independent column-lines can be driven.

The address lines (ADDR1..ADDR8) are compared to an DIP-switch on each module using a 74HCT688. The output of that comparison drives the ENABLE pin of the FP2800A (through a discrete inverter).

All data and address lines are at 24V logic level. The VS line should be current limited to 350-400 mA, because the coils and/or the FP2800A may blow at higher current.

I did a reverse engineering of the 24V logic at the BROSE display just for illustration. Download as [PDF](https://github.com/545ch4/flippie/raw/master/board/docs/brose_24v_logic.pdf) or [Eagle SCH](https://github.com/545ch4/flippie/raw/master/board/docs/brose_24v_logic.sch).


### BROSE 60-pin connector

![Specification of the common 60-pin BROSE connector](https://github.com/545ch4/flippie/raw/master/board/docs/brose_connector.png "Specification of the common 60-pin BROSE connector")


## flippie board

The board was designed to drive every serial assembly of modules or single ones non-intrusively - without soldering or modifying the module(s) - simply by connection the proprietary 60-pin BROSE connector. The main MCU [ESP8266](https://espressif.com/en/products/hardware/esp8266ex/overview) is mounted on a USB-interfaced USB-to-Serial converter for convenient programming and WiFi on board. Please see [wemos D1 mini](https://www.wemos.cc/product/d1-mini.html) documentation. Usually you need some driver for the converter to be detected as serial port depending on your OS. The wemos D1 mini comes with a Jiangsu Qinheng CH340/CH341/CH34X or Silicon Labs CP210x chip.


### Block diagram

![flippie block diagram](https://github.com/545ch4/flippie/raw/master/board/block_diagram.png "flippie block diagram")


### Schematics

Since this is my first PCB, the schematic may be slightly unusual. But it works... Suggestions are very welcome. Get the [Eagle SCH file](https://github.com/545ch4/flippie/raw/master/board/flippie.sch) or see the [PDF file](https://github.com/545ch4/flippie/raw/master/board/flippie_schematics.pdf).


### Layout

![flippie board](https://github.com/545ch4/flippie/raw/master/board/board.png "flippie board")

Download the [Eagle BRD](https://github.com/545ch4/flippie/board/flippie.brd) file and/or the generated [GERBER files as ZIP archive](https://github.com/545ch4/flippie/raw/master/board/gerber.zip). All design rules are taken from [SparkFuns Extended Gerber Format](https://github.com/sparkfun/SparkFun_Eagle_Settings/blob/master/cam/sfe-gerb274x-withGBP.cam).


### BOM

| Part | Value      | Device        | Package       | Description |
|------|------------|---------------|---------------|-------------|
| Part Value | Device | Package | Description |
| C1 | 100uF/50V | CPOL-EU_E | PANASONIC_E | Polarized capacitor, 50V |
| C2 | 10uF/50V | C-EU_C1206 | C1206 | X7R Ceramic Capacitor, 50V |
| C3 | 1uF/50V | C-EU_C1206 | C1206 | X7R Ceramic Capacitor, 50V |
| IC1 | 74HCT245DW | 74HCT245DW | SO20W | Octal BUS TRANSCEIVER, 3-state, TTL/CMOS |
| IC2 | FPF2702MX | FPF2700 | SO8N | AccuPower 0.4~2 A Adjustable Over-Current Protection Load Switch |
| IC3 | SN74AHC595D | SN74AHC595D | SO16N | 8 bit Shift registers |
| ... | ... | ... | ... | ... |
| IC9 | SN74AHC595D | SN74AHC595D | SO16N | 8 bit Shift registers |
| IC10 | TD62783AFG | UDN2981LW | SO18W | PMOS Darlington transistor array |
| IC11 | TD62783AFG | UDN2981LW | SO18W | PMOS Darlington transistor array |
| IC12 | TD62783AFG | UDN2981LW | SO18W | PMOS Darlington transistor array |
| IC13 | ULN2803A | ULN2803ADW | SO18W | NMOS Darlington transistor array |
| ... | ... | ... | ... | ... |
| IC17 | ULN2803A | ULN2803ADW | SO18W | NMOS Darlington transistor array |
| JP1 | 3V3 | JP1E | JP1 | 3.3V Rail Jumper |
| JP2 | 24V | JP1E | JP1 | 24V Rail Jumper |
| JP3 | 5V | JP1E | JP1 | 5V(VCC) Rail Jumper |
| JP4 | VS | JP1E | JP1 | 24V(VS) Jumper |
| LED1 C (red) | LED_SMT1206 | 1206 | LED |
| LED2 B (yellow) | LED_SMT1206 | 1206 | LED |
| LED3 A (green) | LED_SMT1206 | 1206 | LED |
| MCU1 | WEMOS D1 mini | WEMOS D1 mini | WEMOS D1 mini MCU |
| PAD1 (24V) | 2,15/1,0 | 2,15/1,0 | THROUGH-HOLE PAD |
| PAD2 (VS) | 2,15/1,0 | 2,15/1,0 | THROUGH-HOLE PAD |
| R1 | 680K | R-EU_R1206 | R1206 | Current limiter Resistor R_set |
| R2 | 100K | R-EU_R1206 | R1206 | Resistor |
| R3 | 10K | R-EU_R1206 | R1206 | Resistor |
| R4 | 10K | R-EU_R1206 | R1206 | Resistor |
| R5 | 10K | R-EU_R1206 | R1206 | Resistor |
| R6 | 220 | R-EU_R1206 | R1206 | Resistor |
| R7 | 220 | R-EU_R1206 | R1206 | Resistor |
| R8 | 220 | R-EU_R1206 | R1206 | Resistor |
| X1 | 3V3 | JST-XH-02 | JST-XH-02-PACKAGE-LONG-PAD | JST XH Connector 2 Pin |
| X2 | 5V | JST-XH-02 | JST-XH-02-PACKAGE-LONG-PAD | JST XH Connector 2 Pin |
| X3 | 24V | JST-XH-02 | JST-XH-02-PACKAGE-LONG-PAD | JST XH Connector 2 Pin |
| X4 | ~EN_PWR | JST-XH-02 | JST-XH-02-PACKAGE-LONG-PAD | JST XH Connector 2 Pin |
| X5 | BROSE-60-POL | 057-060-1 | 057-060-1 | 60-pol. BROSE CONNECTOR |


### Soldering notes

You can override the whole current limit circuit by shorting/bridging PAD1 (24V) and PAD2 (VS). If you decided to do so, you don't need to populate C1, C2, C3, R1, R2 and IC2.

> **Close JP1 (3V3) and JP2 (24V) but not JP4 (VS) yet.**


## Code

### Prerequisites

Since building and maintaining an ESP8266 toolchain using the [Arduino ESP8266 Framework](https://github.com/ESP8266/Arduino) can be rather frustrating, I decided to use [PlatformIO](http://platformio.org/platformio-ide) with this project.

1. [Download PlatformIO](http://platformio.org/platformio-ide) and install
2. Launch and follow on-screen instructions (install Python-2.7 if necessary)
3. [Install Clang/LLVM](http://docs.platformio.org/en/stable/ide/atom.html#ide-atom-installation-clang)
4. Ensure `platformio-ide` and `platformio-ide-terminal` are enabled (*"Settings > Packages"*)


### Open the project

Download or clone this repository. Open the directory `./code/server` using *"Open project"* at PlatformIO IDE.


### Necessary adoptions

Review you flip-dot addresses: **ADDR8 (8 on the DIP-switch) must be in ON state. We are emulating an overall-enable-pin with that one. Further, the addresses are inverted. So, address 0x01 matches the DIP-switch configuration 1-OFF, 2-ON, ..., 7-ON an 8-ON.**

Before you compile and upload your custom firmware to the ESP8266, there are some values specific to your setup/environment to be defined.
**Flip-dot configuration at `code/server/flippie_device.cpp`:**
```c++
// TODO: How many modules does your display consists of?
const unsigned int num_modules = 4;
config.num_modules = num_modules;
// TODO: What are the addresses (as decimal) of the modules? (see DIP-switches at each module)
config.addresses = new unsigned int[num_modules]{1, 2, 4, 8};
// TODO: How many rows does your display have? (equal over all modules)
config.num_rows = 18;
// TODO: How many columns does each module of your display have? (same order as the addresses)
config.num_columns = new unsigned int[num_modules]{28, 28, 28, 21};
// TODO: Should LED C toggle on each shift-register firing?
config.led_mode = LED_MODE_FLASHING;
```

**WiFi configuration at `code/server/main.cpp`:**
```c++
// TODO: What's the SSID of your WiFi?
const char* ssid = "SSID";
// TODO: What's the PASSWORD of your WiFi?
const char* password = "PASSWORD";
// TODO: If you don't want to use DHCP, provide a static IP (uncomment the following lines). Otherwise leave this commented.
// IPAddress ip(192, 168, 1, 23);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);
// WiFi.config(ip, gateway, subnet);
```


### Compile and upload firmware

> **Please disconnect the power supply of your flippie board or remove the jumper JP1 und JP3 before connecting your computer to the USB port of the ESP8266 (if mounted at the flippie board already).**

Navigate to *"PlatformIO > Build"* to compile this project and create the firmware for uploading to the ESP8266. Use *"PlatformIO > Upload"* to upload your firmware using the USB connection.


### Test

Disconnect flippie from USB or press the reset button of the wemos D1 mini board. Plug the wemos D1 mini to flippie, ensure to close JP1 (3V3), JP2 (24V) and JP3 (5V) **but not JP4 (VS) yet**. All three LEDs should flash three times. If not, the shift-register(s) doesn't seems to work properly... [So, check your soldering.](http://www.infidigm.net/articles/solder/)

If the LEDs were flashing during boot-up, don't yet connect the display itself. Point your browser to `http://<flippie IP>/`. That's the web-interface of flippie. You've done well so far.

Since you don't want to damage your display, we will try to set and reset some dots in a dry run first (**AKA: don't connect your flipdot display yet**):

0. Make sure your display is **not** connected (X5), jumper JP4 (VS) is **closed/shorted** and all three power rails (3V3, 5V and 24V) are enabled through JP1, JP2, JP3.
1. Head to "Low Level" in at flippies web-interface.
2. Fill the form for
   1. Select the address of one of your panels (e.g. 1)
   2. Select a column we are going to use (Column, e.g. 10)
   3. Set "Row SET" to '0' (first row)
   4. Leave "Row RST" undefined
   5. Set the direction D to "1" (D=1 when setting (ROW_SET) and D=0 when reseting (ROW_RST) a pixel)
4. Press "Fire shift-register (PERSISTENT)"
   1. IC12 pin 11 should drive +24V (first row rail, same as pin 1 at X5)
   2. IC16 pin 18 should go to GND (our simulated ENABLE signal, same as pin 60 at X5)
5. Press "Fire shift-register (ENABLE)" to quit "PERSISTENT" mode.

Repeat the test with flipdot display connected (X5):

0. Make sure your display **is** connected (X5), jumper JP4 (VS) is **open** and all three power rails (3V3, 5V and 24V) are enabled through JP1, JP2, JP3.
1. Head to "Low Level" in at flippies web-interface.
2. Fill the form for
   1. Select the address of one of your panels (e.g. 1)
   2. Select a column we are going to use (Column, e.g. 10)
   3. Set "Row SET" to '0' (first row)
   4. Leave "Row RST" undefined
   5. Set the direction D to "1" (D=1 when setting (ROW_SET) and D=0 when reseting (ROW_RST) a pixel)
4. Press "Fire shift-register (PERSISTENT)"
5. Now take a jumper and use it to **shortly bypass** (close shortly and then open again) JP4 (VS): **The dot should flip!**
6. Repeat the procedure with "Row SET" undefined, "Row RST" set to '0' and D set to '0'. **The dot should flip back!**
5. Press "Fire shift-register (ENABLE)" to quit "PERSISTENT" mode.

**Well done!** You're ready to use your flippie! [Simply head over to "Paint" and draw something.](#paint)


### Firmware API documentation

Flippie is basically a simple web server at port 80 serving the following access points:

**`/ui` – UI pages**  
A simple index page with browser UI controlling the flip-dot. All javascript and stylesheets are loaded from an external CDN, not from the ESP8266 itself. So, you need to be connected to the internet... (Yes, it's an TODO.)

The UI does have a nice drawing pane, where every pixel can be set/reset like painting using a HTML5 canvas.

<a name="paint"></a>
<img src="https://github.com/545ch4/flippie/raw/master/board/ui_paint.png" alt="flippie ui paint pane" title="flippie ui paint pane" width="320px" />

**`/dots` – A receiver of base64 encoded dots vector**  
This method reads the content of HTTP (POST/GET) variable `dots` which is a base64 encoded string. This string is build of 32-bit wide integers (four bytes) where each bit (0-31) represents the state of one column. Those integers are ordered by rows and then modules:
```
[row 1 column 1-32* module 1], [row 1 column 1-32* module 2], ..., [row 1 column 1-32* module M], [row 2 column 1-32* module 1], [row 2 column 1-32* module 2], ..., ..., [row R column 1-32* module M]
```
\* max, could be less, ignoring unnecessary bits. Each integer is packed as four 8-bit characters in LSB order.

**`/flippie` – Directly alter the shift register at flippie (possibly dangerous)**

Low level access to flippie. Set using HTTP variables (POST) and retrieve values as JSON using GET. POST request will return JSON `true`.

| HTTP verb | Variable       | Value           | Description                   |
|-----------|----------------|---------------- |-------------------------------|
| GET/POST  | led_X          | 0, 1            | Get/Set the state of LED X (A, B, C) |
| GET/POST  | address        | 0 - 127         | Get/Set the module address |
| GET/POST  | column         | 0 - 27          | Get/Set the active column |
| GET/POST  | d              | 0, 1            | Set FP2800A D pin (1 = selected column set to GND, 0 = selected column set to +VS) |
| GET/POST  | row_set        | 0 - 19          | Set the selected row to +VS |
| GET/POST  | row_rst        | 0 - 19          | Set the selected row to GND |
| GET/POST  | enable         | 0, 1            | Set enable if 1 (dangerous) |
| POST      | clear          | 0, 1            | Clear shift-register if 1 |
| GET       | shiftregister  | String          | Get contents of the shift-register as sequence of zeros and ones. |
| POST      | task           | clear           | Clear the whole display |
| POST      | task           | fill            | Fill the whole display (set all dots) |
| POST      | task           | inverse         | Inverse the whole display |
| POST      | task           | magnetize       | Magnetize the whole display |

Basic mechanism to set a dot (column 2, row 3) at module 0 with address 0x01 (DIP switch 0-1-1-1-1-1-1-0) using raw HTTP:
```shell
$ telnet <flippie IP> 80
> POST /flippie HTTP/1.0
> Content-Length: 41
>
> address=1&column=1&row_set=2&d=1&enable=1
```

**`/pixel` – Set individual pixels**

| HTTP Variable          | Description |
|------------------------|-------------|
| r(0-31)                | Row |
| m(0-128)               | Module |
| c(0-31)                | Column |
| state(0/1)             | Set of reset the pixel |

A GET request will reveal the state of an pixel and a POST will set the state.


## Demo ruby client

There's a simple demo-like ruby implementation to write text at a given display. To use it, please head yourself to the directory `./client/` and initialize the ruby environment with:
```shell
gem install bundler
bundle install
```

Adjust flippies credentials in `cli.rb`:
```ruby
# initialize new flippie client
fc = FlippieClient.new(
   '192.168.1.23',     # IP address of your flippie board
   18,                  # number of rows of your flip-dot display
   [21],                # number of columns per module (usually some 28ers an one 21er)
   false                # debug => true
)
```

You are now ready to send messages/text to your flippie board using the ruby tool. Example:
```shell
./cli.rb YES
```
You should see an visual response of "YES" on your command line as well as the same text on your flip-dot display, obviously. See the source for further options.
