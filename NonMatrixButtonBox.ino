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
 * Copyright 2025 Carl Hauser under the same license.
 */

// This is set up to use the Arduino HID library for RP2040 -- i.e. Pi Pico

#include "NonMatrixButtonBox.h"
#include <Joystick.h>

// Keyboard state variables
boolean prevKeyReadings[SWITCHES];
boolean currentKeyReadings[SWITCHES];
Joystick_ Joystick = Joystick_(0x03, JOYSTICK_TYPE_JOYSTICK, 14, 0, false, false, false, false, false, false, false, false, false, false, false);

// This is called when the button box is connected and powers up
void setup() {
  Joystick.begin(true);
  for (int i = 0; i < SWITCHES; i++)
    pinMode(pins[i], INPUT_PULLUP);
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
  for (int i = 0; i < SWITCHES; i++) {
    bool currentKeyReading = currentKeyReadings[i];
    if ((currentKeyReading != prevKeyReadings[i]) || always) {
      if (currentKeyReading) {
        Joystick.pressButton(switchMap[i]);
      } else {
        Joystick.releaseButton(switchMap[i]);      
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
void clearBooleanMatrix(boolean booleanMatrix[SWITCHES], boolean value) {
  for (int i = 0; i < SWITCHES; i++) {
    booleanMatrix[i] = value;
  }
}

// Read all keys
// Note that the pins are configured to PULLUP and switches
// are wired to connect the pin to ground.
// A LOW value indicates that the button is pushed
void readKeys() {
  for (int j = 0; j < SWITCHES; j++)
    currentKeyReadings[j] = !digitalRead(pins[j]);
  }
}
