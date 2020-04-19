# minimalLinux
###### uboot_gpio: Custom minimal linux kernels incorporated into a system with a custom bootloader allowing to choose Utility or Admin filesystem on startup. The former automatically starts a flask file server allowing authenticated upload and download onto a SD card, while the latter lets the user format and partition the SD card according to his needs
```
cd uboot_gpio/Utility
./build.sh
./copy_to_admin.sh
cd ../Admin && ./build.sh
./runme
```
###### gpio: with use of the new C API and library libgpio custom linux 4.19 kernel with a C application based on the flashing leds
```
cd gpio
./build.sh
./GUI/gui2.py
# in a different window
./runme
```
