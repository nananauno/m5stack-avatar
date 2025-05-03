# Notice

This repository is temporarily frozen at v0.10.0. (Due to the absence of the administrator) We cannot respond to pull requests or ISSUE received.

- We may update this repository in the future when we find bugs due to version upgrades of related libraries.
- If there is anyone who can maintain this repository, please let us know.

# M5Stack-Avatar

[![Powered By PlatformIO](https://img.shields.io/badge/powered-PlatformIO-brightgreen)](https://platformio.org/)
[![Build Status](https://travis-ci.com/meganetaaan/m5stack-avatar.svg?branch=master)](https://travis-ci.com/meganetaaan/m5stack-avatar)

![M5Stack-Avatar](docs/image/avatar.gif)

Video: https://www.youtube.com/watch?v=C1Hj9kfY5qc

[日本語](README_ja.md)

## Features

* :neutral_face:     Draw avatar face
* :smile:            Expression(Happy, Angry, Sad etc.)
* :smiley_cat:       Customize face
* :kiss:             Lip sync
* :art:              Color Palette
* :arrows_clockwise: Move, Zoom and Rotation
* :two:              Compatible with M5Stack Core2

## VLW Font Support

This library now supports VLW fonts for speech text display. You can use custom VLW fonts to display text in different styles, including Japanese fonts.

### Using VLW Fonts

1. Place your `.vlw` font files in the `data` directory
2. Upload the font files to LittleFS using Platform IO's "Upload Filesystem Image" or Arduino IDE's ESP32 Sketch Data Upload
3. Load and use the font in your code:

```cpp
M5GFX vlwfont;

void setup() {
  // ... other setup code ...
  
  // Load the font from LittleFS
  if(!vlwfont.loadFont(LittleFS, "/YourFont.vlw")){
    // Handle error
  }
  
  // Set the font for speech
  avatar.setSpeechFont(vlwfont.getFont(), true, 24);  // Enable VLW font with size 24
  avatar.init(16);
}
```

Check the `examples/vlwfont` and `examples/multiple-vlwfont` directories for complete examples.

### Included Fonts

The following VLW fonts are included in the `data` directory:
- `BIZ_UDPGothic_24.vlw` - A Japanese Gothic font
- `HachiMaruPop_24.vlw` - A cute Japanese handwriting-style font

### License

- `BIZ_UDPGothic_24.vlw`: [SIL Open Font License Version 1.1](LICENSE_BIZ_UDPGOTHIC.txt)
- `HachiMaruPop_24.vlw`: [SIL Open Font License Version 1.1](LICENSE_HACHIMARU.txt)

## Installation

### Prerequisites

* USB Driver is installed throwgh [Getting Started: Installing the USB Driver](http://www.m5stack.com/assets/docs/)
* Any of IDE is set up
  * This library is confirmed on __Arduino IDE__ and __Platform IO__ for now

### Using Arduino IDE

* On Arduino IDE, Select "Sketch > Include Library > Manage Libraries..."
* Search "m5stack avatar"
* Select "M5Stack_Avatar" from the results then click "Install"
* The library gets installed

### Using Platform IO

* Initialize your Platform IO project
```sh
mkdir my-avatar
cd my-avatar
platformio init -d . -b m5stack-core-esp32
```
* Install the library and its dependency
```sh
platformio lib install M5Unified
platformio lib install M5Stack-Avatar
```
* The library gets downloaded from repository to .piolibdeps directory

## Usage

```cpp

#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;

void setup()
{
  M5.begin();
  avatar.init(); // start drawing
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
```

### Using LipSync

* setup AquesTalk-ESP32 (http://blog-yama.a-quest.com/?eid=970195).
  * (For parsing Kainji statement) Copy the dictionary file from above link to the microSD card.
  * You don't need to copy AquesTalkTTS files. They are included in this library.

* Write below to open avatar mouth according to the audio output.

```cpp
#include <AquesTalkTTS.h>
#include <M5Unified.h>
#include <Avatar.h>
#include <tasks/LipSync.h>

using namespace m5avatar;

// AquesTalk License Key
// NULL or wrong value is just ignored
const char* AQUESTALK_KEY = "XXXX-XXXX-XXXX-XXXX";
Avatar avatar;

void setup() {
  int iret;
  M5.begin();
  // For Kanji-to-speech mode (requires dictionary file saved on microSD)
  // iret = TTS.createK(AQUESTALK_KEY);
  iret = TTS.create(AQUESTALK_KEY);
  avatar.init();
  avatar.addTask(lipSync, "lipSync");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    // For Kanji-to-speech mode
    // TTS.play("こんにちは。", 80);
    TTS.play("konnichiwa", 80);
  }
}

```

### Further usage

see `examples` directory.

### Migration from 0.7.x to 0.8.x

`M5Stack-Avatar` now depends on `M5Unified`, the integrated library for all devices of M5Stack series.
Since 0.8.0, Sketches with avatar should include `M5Unified.h` instead of `M5Stack.h` or `M5Core2.h`

### Notes for v0.10.0

Some applications may reboot due to insufficient stack size for other tasks. In such cases, increase the stack size of the relevant task.