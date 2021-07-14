/**
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2016 Carl Hauser under the same license.
 */

#include "ButtonBox.h"
#include <Joystick.h>

// Keyboard state variables
boolean prevKeyReadings[ROWS*COLS];
boolean currentKeyReadings[ROWS*COLS];
Joystick_ Joystick = Joystick_(0x03, JOYSTICK_TYPE_JOYSTICK, 16, 0, false, false, false, false, false, false, false, false, false, false, false);

// This is called when the button box is connected and powers up
void setup() {
  Joystick.begin(true);
  for (int i = 0; i < COLS; i++)
    pinMode(colPins[i], INPUT_PULLUP);
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  clearBooleanMatrixes();
}

// Read key states and handle all chord events
void loop() {
  readKeys();

  sendChanges();
  delay(20);
}

int sendCount = 0;

void sendChanges() {
  int always = 0;
  if (sendCount==10) {
    always = 1;
    sendCount = 0;
  }
  else {
    sendCount++;
  };
  for (int i = 0; i < ROWS*COLS; i++) {
    bool currentKeyReading = currentKeyReadings[i];
    if ((currentKeyReading != prevKeyReadings[i]) || always) {
      if (currentKeyReading) {
        Joystick.pressButton(i);
      } else {
        Joystick.releaseButton(i);      
      }
      prevKeyReadings[i] = currentKeyReading;
    }
  }
}
// Set all values of all boolean matrixes to false
void clearBooleanMatrixes() {
  clearBooleanMatrix(prevKeyReadings, false);
  clearBooleanMatrix(currentKeyReadings, false);
}

// Set all values of the passed matrix to the given value
void clearBooleanMatrix(boolean booleanMatrix[ROWS*COLS], boolean value) {
  for (int i = 0; i < ROWS*COLS; i++) {
    booleanMatrix[i] = value;
  }
}

// Read all keys
// Note that with the cathode (black bar end) of the diodes pointing
// to the Row pins, we drive the row pins low to activate a row
// and then sense the values of the column pins. A low value
// indicates that the button at the intersection of the row and column
// is pushed.
void readKeys() {
  for (int i = 0; i < ROWS; i++) {
    digitalWrite(rowPins[i], LOW);
    for (int j = 0; j < COLS; j++)
      currentKeyReadings[i*COLS+j] = !digitalRead(colPins[j]);
    digitalWrite(rowPins[i], HIGH);
  }
}
