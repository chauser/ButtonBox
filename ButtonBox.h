#define ROWS 3
#define COLS 5
#define ledPin 13
 
int rowPins[ROWS] = { 4, 5, 7 };
int colPins[COLS] = { 2, 3, 6, 8, 9 };

// buttons can be mapped to arbitrary joystick buttons
// The standard mapping is top row: 0..4, middle row: 5..9,
// last row (toggle switches: 10..14
// remapping may be necessary, e.g., if you need
// a toggle switch at a particular numbered position.
int switchMap[ROWS*COLS] = {0, 1, 2, 3, 4,
                        5, 6, 7, 8, 9,
                        10, 11, 12, 13, 14};
 
