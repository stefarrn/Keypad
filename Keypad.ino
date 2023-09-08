#include "Keyboard.h"

//pins
const int col[4] = { 0, 1, 2, 3 };
const int row[3] = { 4, 5, 6 };

const int led_debug = 7;
const int led_mode = 8;

bool keysPressed[4][3];
bool lastKeysPressed[4][3];

//keycodes for single keypress
//https://theasciicode.com.ar/
const char keyMap[3][4] = {
  { KEY_F13, KEY_F14, KEY_F15, KEY_F16 },
  { KEY_F17, KEY_F18, KEY_F19, KEY_F20 },
  { KEY_F21, KEY_F22, KEY_F23, KEY_F24 }
};

//only for key assignments
const int keys[3][4] = {
  { 1, 2, 3, 4 },
  { 5, 6, 7, 8 },
  { 9, 10, 11, 12 }
};

const int numpadKey[] = { KEY_KP_0, KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_7, KEY_KP_8, KEY_KP_9 };

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(col[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(row[i], INPUT_PULLDOWN);
  }

  pinMode(led_mode, OUTPUT);
  pinMode(led_debug, OUTPUT);


  Serial.begin(115200);
  digitalWrite(led_debug, HIGH);
  while (!Serial && millis() < 1000);
  digitalWrite(led_debug, LOW);
  Serial.println("serial initialized");

  Keyboard.begin(KeyboardLayout_de_DE);
}

void loop() {
  updateKeysPressed();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      //key assignments:
      switch (keys[j][i]) {
        //special macros
        case 1:
          numpadAscii(i, j, 231);
          break;
        case 10:
          textMacro(i, j, "max.mustermann@generic-mailservice.com");
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
    if (!lastKeysPressed[i][j]) Serial.println("single keypress " + String(keyMap[j][i]));

    Keyboard.press(keyMap[j][i]);

  //if the key was pressed before, release it
  } else if (lastKeysPressed[i][j]) {
    Keyboard.release(keyMap[j][i]);
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
    digitalWrite(col[i], HIGH);

    for (int j = 0; j < 3; j++) {
      lastKeysPressed[i][j] = keysPressed[i][j];

      if (digitalRead(row[j]) == HIGH) {
        keysPressed[i][j] = true;
      } else {
        keysPressed[i][j] = false;
      }
    }

    digitalWrite(col[i], LOW);
  }
}