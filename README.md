TinyBasicPlus
=============

A C implementation of Tiny Basic, with a focus on support for
Arduino.  It was originally written by Gordon Brandly in the form
of "68000 Tiny Basic", and then ported to C by Michael Field as
"Arduino Basic", though still called "Tiny Basic" in the source
files.

TinyBasicPlus is an extension and modification upon Michael''s work,
adding support for a few more devices, configurable at build time.
It is designed for use on the Arduino, although builds will soon
be easily possible for other platforms through command line makefiles.

Features added include support for fileio (SD Library), smaller
footprint (PROGMEM), and soon support for pin data IO as well as
PS2 input devices and LCD output devices.


# Current Device Support
    - Arduino - ATMega 168 (~400 bytes available)
    - Arduino - ATMega 368 (~1400 bytes available)
    - SD cards (via SD Library, for FILES, LOAD, SAVE commands)
    - Serial IO - command console

# Future Device Support
    - Arduino Digital/Analog IO control
    - PS2 Keyboard for standalone use
    - LCD Panel for standalone use


# Known Quirks and Limitations
    - If LOAD or SAVE are called, FILES fails subsequent listings
    - SD cards are not hot-swappable. A reset is required between swaps.

# Authors

    - Tiny Basic 68k - Gordon Brandly [Project Page](http://members.shaw.ca/gbrandly/68ktinyb.html)
    - Arduino Basic / Tiny Basic C - Michael Field [Project Page](http://ec2-122-248-210-243.ap-southeast-1.compute.amazonaws.com/mediawiki/index.php/Arduino_Basic)
    - Tiny Basic Plus - Scott Lawrence <yorgle@gmail.com> [Github Page](http://github.com/BleuLlama/TinyBasicPlus]

# Links
    - [Arduino Microcontroller](http://arduino.cc)

# MIT License

Copyright (c) 2012

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
