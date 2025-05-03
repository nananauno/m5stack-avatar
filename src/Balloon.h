// Copyright (c) Shinya Ishikawa. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef BALLOON_H_
#define BALLOON_H_
#define LGFX_USE_V1
#include <LittleFS.h>
#include <M5Unified.h>
#include "DrawContext.h"
#include "Drawable.h"

#ifndef ARDUINO
#include <string>
typedef std::string String;
#endif  // ARDUINO
#include <M5Unified.hpp>

const int16_t TEXT_HEIGHT = 8;
const int16_t TEXT_SIZE = 2;
const int16_t MIN_WIDTH = 40;
const int cx = 240;
const int cy = 220;

namespace m5avatar {
class Balloon final : public Drawable {
 public:
  // constructor
  Balloon() = default;
  ~Balloon() = default;
  Balloon(const Balloon &other) = default;
  Balloon &operator=(const Balloon &other) = default;
  void draw(M5Canvas *spi, BoundingRect rect,
            DrawContext *drawContext) override {
    String text = drawContext->getspeechText();
    const lgfx::IFont *font = drawContext->getSpeechFont();
    bool enableVLW = drawContext->getEnableVLW();
    int16_t text_height;
    int16_t text_size;
    int16_t cyadj = 0;
    if (text.length() == 0) {
      return;
    }
    if(enableVLW){
      text_height = drawContext->getVLWFontSize();
      text_size = 1;
      cyadj = 10;
    }else{
      text_height = TEXT_HEIGHT;
      text_size = TEXT_SIZE;
    }
    ColorPalette* cp = drawContext->getColorPalette();
    uint16_t primaryColor = cp->get(COLOR_BALLOON_FOREGROUND);
    uint16_t backgroundColor = cp->get(COLOR_BALLOON_BACKGROUND);
    M5.Lcd.setTextSize(text_size);
    M5.Lcd.setTextDatum(MC_DATUM);
    spi->setTextSize(text_size);
    spi->setTextColor(primaryColor, backgroundColor);
    spi->setTextDatum(MC_DATUM);
    //M5.Lcd.setFont(font);
    spi->setFont(font);
    int textWidth = spi->textWidth(text.c_str());
    int textHeight = text_height * text_size;
    spi->fillEllipse(cx - 20, cy,textWidth + 2, textHeight * 2 + 2 - cyadj,
                     primaryColor);
    spi->fillTriangle(cx - 62, cy - 42, cx - 8, cy - 10, cx - 41, cy - 8,
                      primaryColor);
    spi->fillEllipse(cx - 20, cy, textWidth, textHeight * 2 - cyadj,
                     backgroundColor);
    spi->fillTriangle(cx - 60, cy - 40 - cyadj, cx - 10, cy - 10, cx - 40, cy - 10,
                      backgroundColor);
    spi->drawString(text.c_str(), cx - textWidth / 6 - 15, cy-cyadj, font);  // Continue printing from new x position
    M5_LOGI("Balloon, textWidth: %d", textWidth);
    M5_LOGI("Balloon, textHeight: %d", textHeight);
    M5_LOGI("Balloon, cx: %d", cx);
    M5_LOGI("Balloon, cy: %d", cy);
  }
};

}  // namespace m5avatar

#endif  // BALLOON_H_
