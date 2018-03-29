ADVANCED SYSTEMS PROGRAMMING
ASSIGNMENT – 3
NAME: CHARAN TEJA GANDHAM
UFID: 19343642
Email Id: gcteja@ufl.edu

HOW TO RUN:
1. make
2. Plugin the usb keyboard.
3. echo -n "1-2:1.0" > /sys/bus/usb/drivers/usbhid/unbind
4. insmod usbkbdass.ko
5. Run the test cases.
