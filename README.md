# ButtonBox
An Arduino sketch for a switchbox interfaced to a computer as a Joystick. Requires a 32u4-based Arduino or clone.

In your desktop Arduino app you need to select the correct board type and Port (as usual for preparing Arduino
sketches. You also need to add the Joystick library to your Arduino app -- get it from 
https://github.com/MHeironimus/ArduinoJoystickLibrary.

The sketch currently assumes that there are 15 buttons in 3 rows of 5 columns. The columns are attached to
DIO pins 2, 3, 6, 8, and 9. The rows are attached to pins 4, 5, and 9. At each row-column intersection there is a 
switch; it can be either a normally-open pushbutton or normally-open toggle switch. One terminal of the switch is
attached to the column wire. The other is attached to the row wire through a diode, with the cathode (black bar) end
of the diode attached to the wire and the other end attached to the switch.

Other arrangements of rows and columns are possible up to a total (rows+columns) of the number DIOs available on the microcontroller board. The number of switches is rows * columns.
