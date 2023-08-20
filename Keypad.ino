#include "Keyboard.h"

//pins
int row[4] = { 0, 1, 2, 3 };
int col[3] = { 4, 5, 6 };

bool keysPressed[4][3];
bool lastKeysPressed[4][3];

//keycodes for single keypress
const int keyMap[4][3] = {
  { 49, 50, 51 },
  { 52, 53, 54 },
  { 55, 56, 57 },
  { 0, 48, 0 }
};

//only for key assignments
const int keys[4][3] = {
  { 0, 1, 2 },
  { 3, 4, 5 },
  { 6, 7, 8 },
  { 9, 10, 11 }
};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Keyboard.begin(KeyboardLayout_de_DE);

  Serial.println("serial initialized");

  for (int i = 0; i < 4; i++) {
    pinMode(row[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(col[i], INPUT_PULLDOWN);
  }
}

void loop() {
  updateKeysPressed();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      //key assignments:
      switch (keys[i][j]) {
        
        //special macros
        case 9:
          textMacro(i, j, "max.mustermann@generic-mailservice.com");
          break;
        case 11:
          textMacro(i, j, ":-)");
          break;

        //all other keys: press key according to keyMap
        default:
          singleKeypress(i, j);
          break;
      }
    }
  }
}

void singleKeypress(int i, int j) {
  //send keypress if button is pressed
  if (keysPressed[i][j]) {
    if (!lastKeysPressed[i][j]) Serial.println("single keypress " + String(keyMap[i][j]));

    Keyboard.press(keyMap[i][j]);

  //if the key was pressed before, release it
  } else if(lastKeysPressed[i][j]) {
    Keyboard.release(keyMap[i][j]);
  }
}

void textMacro(int i, int j, String s) {
  //only activate on rising edge
  if (keysPressed[i][j] && !lastKeysPressed[i][j]) {
    Serial.println("text macro " + s);

    for (int k = 0; k < s.length(); k++) {
      Keyboard.write(s[k]);
    }
  }
}

void updateKeysPressed() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(row[i], HIGH);

    for (int j = 0; j < 3; j++) {
      lastKeysPressed[i][j] = keysPressed[i][j];

      if (digitalRead(col[j]) == HIGH) {
        keysPressed[i][j] = true;
      } else {
        keysPressed[i][j] = false;
      }
    }

    digitalWrite(row[i], LOW);
  }
}