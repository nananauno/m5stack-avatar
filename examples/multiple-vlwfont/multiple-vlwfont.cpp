#include <LittleFS.h>
#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;

M5GFX vlwfont1;
M5GFX vlwfont2;
bool enableVLW = true;
uint8_t fontIdx = 0;

void setup()
{
  M5.begin();
  M5.Log.setLogLevel(m5::log_target_serial, esp_log_level_t::ESP_LOG_INFO);
  if(!LittleFS.begin()){
    M5.Display.println("LittleFS begin failed");
    M5.delay(3000);
    esp_restart();
  }
  
  if(!vlwfont1.loadFont(LittleFS, "/BIZ_UDPGothic_24.vlw")){
    M5.Lcd.println("vlwfont1 load failed");
    M5.delay(3000);
    esp_restart();
  }
  if(!vlwfont2.loadFont(LittleFS, "/HachiMaruPop_24.vlw")){
    M5.Lcd.println("vlwfont2 load failed");
    M5.delay(3000);
    esp_restart();
  }
  avatar.setSpeechFont(vlwfont1.getFont(), enableVLW, 24);
  avatar.init(16);
}

void loop()
{
  M5.update();
  uint32_t sum=0;
  for(uint8_t i = 0; i < 100; i++)
  {
    sum+=touchRead(6);
    delay(1);
  }
  M5.Log.printf("%d\n",sum);
  if(sum<5420000){
    avatar.setExpression(Expression::Neutral);
    avatar.setSpeechText("Touch me!");
  }else if(sum>6000000){
    avatar.setExpression(Expression::Happy);
    avatar.setSpeechText("I'm happy!");
  }

  if(M5.BtnA.wasPressed()){
    fontIdx++;
    switch(fontIdx%3){
      case 0:
        avatar.setSpeechFont(vlwfont1.getFont(), enableVLW, 24);
        break;
      case 1:
        avatar.setSpeechFont(vlwfont2.getFont(), enableVLW, 24);
        break;
      case 2:
        avatar.setSpeechFont(NULL);
        break;
    }
  }
  delay(50);

}
