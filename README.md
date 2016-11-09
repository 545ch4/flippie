# flippie

## Board

### Schematics

Since it's my first electronic project with an own design, the schematic may be slightly unusual. But it works... Suggestions are very welcome. Get the [Eagle SCH file](https://github.com/545ch4/flippie/board/flippie.sch) or see the [PDF file](https://github.com/545ch4/flippie/board/flippie_schematics.pdf).

![flippie schematics](https://github.com/545ch4/flippie/board/schematics.png "flippie schematics")

### Layout

![flippie board top view](https://github.com/545ch4/flippie/board/board_top.png "flippie board top view")
![flippie board bottom view](https://github.com/545ch4/flippie/board/board_bottom.png "flippie board bottom view")

You are welcome to use the [Eagle BRD](https://github.com/545ch4/flippie/board/flippie.brd) file and/or generated [GERBER files as ZIP archive](https://github.com/545ch4/flippie/board/flippie_gerber.zip) using [SparkFuns Extended Gerber Format](https://github.com/sparkfun/SparkFun_Eagle_Settings/blob/master/cam/sfe-gerb274x-withGBP.cam)

### BOM

| Part | Value      | Device        | Package       | Description |
|-----:|-----------:|--------------:|--------------:|------------:|
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
| U2   | SN74AHC595D| SN74AHC595D   | SO16N         | 8 bit Shift register |
| U8   | SN74AHC595D| SN74AHC595D   | SO16N         | 8 bit Shift register |
| U9   | ULN2803ADW | ULN2803ADW    | SO18N         | NMOS Darlington transistor array |
| U10  | ULN2803ADW | ULN2803ADW    | SO18N         | NMOS Darlington transistor array |
| U11  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U12  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U13  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U14  | ULN2803ADW | ULN2803ADW    | SO18N         | NMOS Darlington transistor array |
| U15  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| U16  | TD62783AP  | UDN2981LW     | SO18W         | PMOS Darlington transistor array |
| X1   | BROSE-60-PO| 30X02X2MM     | 057-060-1     | CONNECTOR |


## Code

### Prerequisites

Since building and maintaining an ESP8266 toolchain using the [Arduino ESP8266 Framework](https://github.com/esp8266/Arduino) can be rather frustrating, I decided to use [PlatformIO](http://platformio.org/platformio-ide) with this project.

1. [Download PlatformIO](http://platformio.org/platformio-ide) and install
2. Launch and follow on-screen instructions (install Python-2.7 if necessary)
3. [Install Clang/LLVM](http://docs.platformio.org/en/stable/ide/atom.html#ide-atom-installation-clang)
3. Ensure `platformio-ide` and `platformio-ide-terminal` are enabled (*Settings > Packages*)

### Open the project

Download or clone this repository. Open the directory `./code/server` using *Open project* at PlatformIO IDE.


### Compile and upload firmware

Navigate to *PlatformIO > Build* to compile this project and create the firmware for uploading to the esp8266. Use *PlatformIO > Upload* to upload your firmware using the USB connection. ** Please disconnect the power supply of your flippie board or remove the jumper J1 before connecting your computer to the USB port of the esp8266 (if mounted at the flippie board already). **


### Test

### Firmware API documentation

Flippie is basically a simple web server at port 80 serving the following access points:

#### '/' root page
A simple index page with browser UI controlling the flip-dot. All javascripts and stylesheets are loaded from an external CDN, not the esp8266 itself.

#### '/dots' receiver of base64 encoded dots matrix

Reads the content of HTTP (POST/GET) variable "dots".


### Example ruby client
