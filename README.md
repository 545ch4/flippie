# flippie

## Board

### Schematics

### Layout

## Code

### Prerequisites

Since building and maintaining an ESP8266 toolchain using the [Arduino ESP8266 Framework](https://github.com/esp8266/Arduino) can be rather frustrating, I decided to use [PlatformIO](http://platformio.org/platformio-ide) with this project.

1. [Download PlatformIO](http://platformio.org/platformio-ide) and install
2. Launch and follow on-screen instructions (install Python-2.7 if necessary)
3. [Install Clang/LLVM](http://docs.platformio.org/en/stable/ide/atom.html#ide-atom-installation-clang)
3. Ensure "platformio-ide" and "platformio-ide-terminal" are enabled (Settings > Packages)

### Open the project

Download of clone this repository. Open the directory "./code/server" using "Open project" at PlatformIO IDE.


### Compile and upload firmware

Navigate to "PlatformIO > Build" to compile this project and create the firmware for uploading to the esp8266. Use "PlatformIO > Upload" to upload your firmware using the USB connection. ** Please disconnect the power supply of your flippie board or remove the jumper J1 before connecting your computer to the USB port of the esp8266 (if mounted at the flippie board already). **


### Test

### Firmware API documentation

Flippie is basically a simple web server at port 80 serving the following access points:

#### '/' root page
A simple index page with browser UI controlling the flip-dot. All javascripts and stylesheets are loaded from an external CDN, not the esp8266 itself.

#### '/dots' receiver of base64 encoded dots matrix

Reads the content of HTTP (POST/GET) variable "dots".


### Example ruby client
