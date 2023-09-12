# Keypad

 The Hardware and software for a simple 3x4 Keypad featuring a USB-C Interface
 
![image](https://github.com/stefarrn/Keypad/assets/80580541/bdeb77ec-5635-4f0e-80fb-e7b482ba2235)

<details>
  <summary>Sources</summary>

    https://wiki.seeedstudio.com/Seeeduino-XIAO/#resourses
    https://grabcad.com/library/5x5mm-smd-tactile-button-1
    https://grabcad.com/library/kailh-polia-switch-cherry-mx-compatible-1

</details>

# How to use

## Setup
- Install the newest version of [arduino IDE](https://docs.arduino.cc/software/ide-v2)
- In arduino IDE, under preferences add this board URL
```
https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
```
- Install the newest version of the `Seeed SAMD Boards` package from the boards manager
- Install the newest version of the `Keyboard` library from the library manager
- Clone or download `Keypad` into your Arduino project folder

## Changing keyboard layout
```c
Keyboard.begin(KeyboardLayout_de_DE);
```
The keyboard layout can be changed in `Keypad.ino` by substituting `KeyboardLayout_de_DE` with any of the following layouts supported by the arduino keyboard library:
```
KeyboardLayout_de_DE
KeyboardLayout_en_US
KeyboardLayout_es_ES
KeyboardLayout_fr_FR
KeyboardLayout_it_IT
KeyboardLayout_sv_SE
KeyboardLayout_da_DK
```

## Editing macros
Open Keypad.ino with the arduino IDE. Functions of the keypad can be configured by editing the code inside the switch statement inside `loop()`. Two examples are already filled in.

```c
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
```

To configure a specific key, look up its number in the `keys` variable:

```c
const int keys[3][4] = {
  { 1, 2, 3, 4 },
  { 5, 6, 7, 8 },
  { 9, 10, 11, 12 }
};
```

Then, add a special case to the switch statement (in this example key number 2 was chosen):

```c
case 2:

    ...

    break;
```
### Predefined macros
Several common macros are already implemented:

**act as single key:**
```c
case 2:
    singleKeypress(i, j, keycode);
    break;
```
where keycode is a either [an integer corrosponding to a key](https://theasciicode.com.ar/) or one of the following special keys:
<details>
    <summary>list of special keys</summary>

    KEY_LEFT_CTRL
    KEY_LEFT_SHIFT
    KEY_LEFT_ALT
    KEY_LEFT_GUI
    KEY_RIGHT_CTRL
    KEY_RIGHT_SHIFT
    KEY_RIGHT_ALT
    KEY_RIGHT_GUI

    KEY_UP_ARROW
    KEY_DOWN_ARROW
    KEY_LEFT_ARROW
    KEY_RIGHT_ARROW
    KEY_BACKSPACE
    KEY_TAB
    KEY_RETURN
    KEY_MENU
    KEY_ESC
    KEY_INSERT
    KEY_DELETE
    KEY_PAGE_UP
    KEY_PAGE_DOWN
    KEY_HOME
    KEY_END
    KEY_CAPS_LOCK
    KEY_PRINT_SCREEN
    KEY_SCROLL_LOCK
    KEY_PAUSE

    KEY_NUM_LOCK
    KEY_KP_SLASH
    KEY_KP_ASTERISK
    KEY_KP_MINUS
    KEY_KP_PLUS
    KEY_KP_ENTER
    KEY_KP_1
    KEY_KP_2
    KEY_KP_3
    KEY_KP_4
    KEY_KP_5
    KEY_KP_6
    KEY_KP_7
    KEY_KP_8
    KEY_KP_9
    KEY_KP_0
    KEY_KP_DOT

    KEY_F1
    KEY_F2
    KEY_F3
    KEY_F4
    KEY_F5
    KEY_F6
    KEY_F7
    KEY_F8
    KEY_F9
    KEY_F10
    KEY_F11
    KEY_F12
    KEY_F13
    KEY_F14
    KEY_F15
    KEY_F16
    KEY_F17
    KEY_F18
    KEY_F19
    KEY_F20
    KEY_F21
    KEY_F22
    KEY_F23
    KEY_F24

</details>


**Type text macro:**
```c
case 2:
    textMacro(i, j, "your-text-here");
    break;
```

**Ascii character macro**
(where 231 is an example):

```c
case 2:
    numpadAscii(i, j, 231);
    break;
```

### Custom code for macro

**activate while key is held**
```c
case 2:
    if (keysPressed[i][j]) {

    ...
    
    }
    break;
```
**activate on rising edge (keypress)**
```c
case 2:
    if (keysPressed[i][j] && !lastKeysPressed[i][j]) {

    ...
    
    }
    break;
```

### Flashing
After changes have been made to `Keypad.ino` the program has to be uploaded to the microcontroller.

In Arduino IDE:
- select `Seeduino XIAO` as your board
- select the correct Port
- upload the sketch