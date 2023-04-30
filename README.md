Log of Things Done:

1. Separated .ino code into src and header files for readablity
	- This meant working through a lot of arudino quirks
	- also meant learning the meaning of the "extern" keyword
	- needed to make all global variables in the header extern
	- assignments for global variables go in src file

2. Added FreeRTOS
    - This involved a number of hurdles working on adding the library
    - needed to be added via zip file
    - needed a custom version to work with the Teensy board
    - needed to change all uses of Arduino-specific macros to custom macros because this freertos had its      own macros which is annoying
