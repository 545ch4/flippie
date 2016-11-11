# flippie

![first flippie test](https://github.com/545ch4/flippie/raw/master/board/docs/flippie_first_test.gif "first flippie test")


## Basic idea and some background

Usual story: no money, lots of deadlines, unsustainable promises, social responsibility, no time at all, but the unique opportunity to get an additional time-sink. Yeah. Seconds later, I got two huge flip-dot displays I couldn't even carry myself and a lot of single modules. Soon (measured in seasons) it became obvious, that reverse engineering the RS484 based IBIS bus would not make me very happy in the long run. So I decided to throw away the original controller board and drive the flip-dot modules myself. This is the story of that effort...

### Flip-dot display in general

A flip-dot display consists of a grid of small magnet embedded discs that are black on one side and a bright color on the other (typically white or yellow). The discs are attached to an axle with separate solenoids arranged at the ends or side. By pulsing the solenoid coil with the appropriate electrical polarity, the permanent magnet on the discs align itself with the magnetic field and thus turning (flipping) the disc.

The matrix schematic arranged on a two-dimensional area is shown below.

<img src="https://github.com/545ch4/flippie/raw/master/board/docs/flipdot.png" alt="flip-dot solenoid schematic" title="flip-dot solenoid schematic" width="400px" />

### BROSE flip-dot

Most BROSE flip-dots are equipped with an [origial FP2800A (or clone)](https://reaktor23.org/_media/projects/flipdot/fp2800-datasheet.pdf) decoder driver as column-selector. It drives one line addressed by 5-bits (A0, A1, A2, B1 and B2) in the direction of D (GND or +VS).  Based on the truth-table, 28 independent column-lines can be driven.

The address lines (ADDR1..ADDR8) are compared to an DIP-switch on each module using a 74HC688. The ADDR8 line also drives the ENABLE pin of the FP2800A.

All data and address lines are at 24V logic level. The +VS line should be current limited to 350-400 mA, because the coils and/or the FP2800A may blow at higher current.


### BROSE 60-pin connector

![Specification of the common 60-pin BROSE connector](https://github.com/545ch4/flippie/raw/master/board/docs/brose_connector.png "Specification of the common 60-pin BROSE connector")


## flippie board

The board was designed to drive every serial assembly of modules or single ones without soldering or modifying the module(s) - simply by connection the proprietary 60-pin BROSE connector. The main MCU [ESP3266](https://espressif.com/en/products/hardware/esp8266ex/overview) is mounted on a USB-interfaced USB-to-Serial converter for convenient programming and WiFi on board. Please see [wemos D1 mini](https://www.wemos.cc/product/d1-mini.html) documentation.


### Block diagram

![flippie block diagram](https://github.com/545ch4/flippie/raw/master/board/block_diagram.png "flippie block diagram")


### Schematics

Since this is my first PCB, the schematic may be slightly unusual. But it works... Suggestions are very welcome. Get the [Eagle SCH file](https://github.com/545ch4/flippie/raw/master/board/flippie.sch) or see the [PDF file](https://github.com/545ch4/flippie/raw/master/board/flippie_schematics.pdf).

### Layout

![flippie board top view](https://github.com/545ch4/flippie/raw/master/board/board_top.png "flippie board top view")
![flippie board bottom view](https://github.com/545ch4/flippie/raw/master/board/board_bottom.png "flippie board bottom view")

Download the [Eagle BRD](https://github.com/545ch4/flippie/board/flippie.brd) file and/or the generated [GERBER files as ZIP archive](https://github.com/545ch4/flippie/raw/master/board/flippie_gerber.zip). All design rules are taken from [SparkFuns Extended Gerber Format](https://github.com/sparkfun/SparkFun_Eagle_Settings/blob/master/cam/sfe-gerb274x-withGBP.cam).


### BOM

| Part | Value      | Device        | Package       | Description |
|------|------------|---------------|---------------|-------------|
| C1   | 100u/25V   | CPOL          | PANASONIC_C   | POLARIZED CAPACITOR |
| C2   | 22u/25V    | CPOL          | PANASONIC_B   | POLARIZED CAPACITOR |
| D1   | BZV55-C3V6 | ZENER-DIODE   | SOD80C        | Z-Diode 3.6V |
| ..   |            |               |               |              |
| D14  | BZV55-C3V6 | ZENER-DIODE   | SOD80C        | Z-Diode 3.6V |
| J1   | INT_3V3    | 1X02          | 1X02X2MM      | JUMPER |
| JP1  | PWR        | 1X05X2MM      | 1X05X2MM      | CONNECTOR |
| LED1 | C          | LED-SMD-1206  | 1206          | LED |
| LED2 | B          | LED-SMD-1206  | 1206          | LED |
| LED3 | A          | LED-SMD-1206  | 1206          | LED |
| MCU1 | WEMOS      | WEMOS_D1_MINI | WEMOS_D1_MINI | WEMOS D1 mini board |
| R1   | 680K       | R-SMD-1206    | 1206          | RESISTOR |
| R2   | 100K       | R-SMD-1206    | 1206          | RESISTOR |
| R3   | 10K        | R-SMD-1206    | 1206          | RESISTOR |
| R4   | 10K        | R-SMD-1206    | 1206          | RESISTOR |
| R5   | 10K        | R-SMD-1206    | 1206          | RESISTOR |
| R6   | 150        | R-SMD-1206    | 1206          | RESISTOR |
| R7   | 150        | R-SMD-1206    | 1206          | RESISTOR |
| R8   | 150        | R-SMD-1206    | 1206          | RESISTOR |
| R9   | 100K       | R-SMD-1206    | 1206          | RESISTOR |
| ..   |            |               |               |          |
| R22  | 100K       | R-SMD-1206    | 1206          | RESISTOR |
| U1   | FPF2702MX  | FPF270x       | SO8N          | AccuPower 0.4~2 A current limiter |
| U2   | SN74AHC595D| 74HC595       | SO16N         | 8 bit Shift register |
| ..   |            |               |               |                      |
| U8   | SN74AHC595D| 74HC595       | SO16N         | 8 bit Shift register |
| U9   | ULN2803ADW | ULN2803ADW    | SO18N         | NMOS Darlington transistor array |
| U10  | ULN2803ADW | ULN2803ADW    | SO18N         | NMOS Darlington transistor array |
| U11  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U12  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U13  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U14  | ULN2803ADW | ULN2803ADW    | SO18N         | NMOS Darlington transistor array |
| U15  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U16  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| X1   | BROSE-60-PO| 30X02X2MM     | 057-060-1     | CONNECTOR |

---

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

> **Please disconnect the power supply of your flippie board or remove the jumper J1 before connecting your computer to the USB port of the ESP8266 (if mounted at the flippie board already).**

Navigate to *"PlatformIO > Build"* to compile this project and create the firmware for uploading to the ESP8266. Use *"PlatformIO > Upload"* to upload your firmware using the USB connection.


### Test

Disconnect flippie and press the reset button of the wemos D1 mini board. All three LEDs should flash three times. Now, point your browser to `http://<flippie IP>/`. You should be able to do some tests (clearing, filling etc).

If you want to test using the bundled client, please head yourself to the directory `./client/` and initialize the ruby environment with:
```shell
gem install bundler
bundle install
```

You are now ready to send messages to your flippie board using the ruby tool. Example:
```shell
./cli.rb "my precious"
```
You should see an visual response on your command line.


### Firmware API documentation

Flippie is basically a simple web server at port 80 serving the following access points:

**`/ui` – UI pages**  
A simple index page with browser UI controlling the flip-dot. All javascript and stylesheets are loaded from an external CDN, not from the ESP8266 itself. Except the flip-dot configuration, this will be rendered as JSON.

**`/dots` – A receiver of base64 encoded dots vector**  
This method reads the content of HTTP (POST/GET) variable `dots` which is a base64 encoded string. This string is build of four  from four 8-bit characters of a 32-bit wide integer where each bit (0-31) represents the state of one column. Those integers are ordered by rows and then modules:
```
[row 1 column 1-32* module 1], [row 1 column 1-32* module 2], ..., [row 1 column 1-32* module M], [row 2 column 1-32* module 1], [row 2 column 1-32* module 2], ..., ..., [row R column 1-32* module M]
```
\* max, could be less, ignoring excess bits. Each integer is split into 4 8-bit characters in LSB order.

**`/flippie` – Directly alter the shift register at flippie (possibly dangerous)**

Low level access to flippie. Set using HTTP variables (POST) and retrieve values as JSON using GET. POST request will retung JSON `true`.

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

Basic mechanism to set a dot (column 2, row 3) at module 0 with address 0x01 (DIP switch 1-0-0-0-0-0-0-1):
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

For further information you may have a look at the example ruby code.
