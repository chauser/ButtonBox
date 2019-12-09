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
Joystick_ Joystick;

// Other state variables
int ledIntensity = 128; // Min 0 - Max 255

// This is called when the button box is connected and powers up
void setup() {
  Joystick.begin(true);
  for (int i = 0; i < COLS; i++)
    pinMode(colPins[i], INPUT_PULLUP);
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);
  clearBooleanMatrixes();
}

// Read key states and handle all chord events
void loop() {
  readKeys();
  analogWrite(ledPin, 0);
  sendChanges();
  delay(20);
}

void sendChanges() {
  for (int i = 0; i < ROWS*COLS; i++) {
    currentKeyReading = currentKeyReadings[i];
    if (currentKeyReading != prevKeyReadings[i]) {
      Joystick.button(i, currentKeyReadings);
      prevKeyReadings[i] = currentKeyReading;
    }
    if currentKeyReading {
      analogWrite(ledPin, ledIntensity);
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
      currentKeyReadings[i*ROWS+j] = !digitalRead(colPins[j]) 
    digitalWrite(rowPins[i], HIGH);
  }
}
