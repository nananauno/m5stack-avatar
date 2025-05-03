#include <LittleFS.h>
#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;
const char* lyrics[] = {"こんにちは", "なでなでして", "わーい", "やったー", "うれしいな", "ありがとう", "なでなで？"};
const int lyricsSize = sizeof(lyrics) / sizeof(char*);
int lyricsIdx = 0;

M5GFX vlwfont;

void setup()
{
  M5.begin();
  M5.Log.setLogLevel(m5::log_target_serial, esp_log_level_t::ESP_LOG_INFO);
  if(!LittleFS.begin()){
    M5.Display.println("LittleFS begin failed");
    M5.delay(3000);
    esp_restart();
  }
  if(!vlwfont.loadFont(LittleFS, "/HachiMaruPop_24.vlw")){
    M5.Lcd.println("Font load failed");
    M5.delay(3000);
    esp_restart();
  }
  avatar.setSpeechFont(vlwfont.getFont());
  avatar.setSpeechVlwFont(true, 24);
  avatar.init(16);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    const char* l = lyrics[lyricsIdx++ % lyricsSize];
    avatar.setSpeechText(l);
    avatar.setMouthOpenRatio(0.7);
    delay(200);
    avatar.setMouthOpenRatio(0);
  }
}
