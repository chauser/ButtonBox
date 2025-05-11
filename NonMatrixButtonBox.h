#define SWITCHES 14

int pins[SWITCHES] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }

// buttons can be mapped to arbitrary joystick buttons
// remapping may be necessary, e.g., if you need
// a toggle switch at a particular numbered position.
int switchMap[SWITCHES] = {4, 2, 6, 8, 13,
                            5, 3, 7, 12, 14,
                           11, 0, 9, 10, 1};
 
