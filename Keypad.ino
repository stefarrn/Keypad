#include "Keyboard.h"

//pins
int row[4] = { 0, 1, 2, 3 };
int col[3] = { 4, 5, 6 };

bool keysPressed[4][3];
bool lastKeysPressed[4][3];

//keycodes for single keypress
//https://theasciicode.com.ar/
const char keyMap[4][3] = {
  { 65, 66, 67 },
  { 68, 69, 70 },
  { 71, 72, 73 },
  { 0, 48, 0 }
};

//only for key assignments
const int keys[4][3] = {
  { 0, 1, 2 },
  { 3, 4, 5 },
  { 6, 7, 8 },
  { 9, 10, 11 }
};

const int numpadKey[] = {KEY_KP_0, KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_7, KEY_KP_8, KEY_KP_9};

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
        case 0:
          numpadAscii(i, j, 231);
          break;
        case 1:
          numpadAscii(i, j, 232);
          break;
        case 2:
          numpadAscii(i, j, 233);
          break;
        case 9:
          textMacro(i, j, "max.mustermann@generic-mailservice.com");
          break;
        case 11:
          numpadAscii(i, j, 236);
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
  } else if (lastKeysPressed[i][j]) {
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

void numpadAscii(int i, int j, int c) {
  //only activate on rising edge
  if (keysPressed[i][j] && !lastKeysPressed[i][j]) {
    Serial.println("numpad ascii macro " + String(c));

    Keyboard.press(KEY_LEFT_ALT);

    //max. code length 4
    char s[4];
    itoa(c, s, 10);

    for (int k = 0; k < 4; k++) {
      if (s[k] == 0) continue;
      int n = int(s[k]) - 48;

      Keyboard.write(numpadKey[n]);
    }

    Keyboard.release(KEY_LEFT_ALT);
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