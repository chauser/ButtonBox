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
// This particular map corresponds to the CCI switch box
// used for the FRC 4061 robot drivestation in 2020-2022.
// 11 - Drivebase enable
// 0 - Climber enable
// 10 - Collector enable
// 11 - Shooter enable
// the CCI box has a toggle on 8 labeled Control, but we don't have enough
// 1 - Camera Front/back flip
// 4 - labeled UP
// 5 - labeled DOWN
// 2 - labeled 2
// 3 - labeled 3
int switchMap[ROWS*COLS] = {4, 2, 6, 8, 13,
                            5, 3, 7, 12, 14,
                           11, 0, 9, 10, 1};
 
