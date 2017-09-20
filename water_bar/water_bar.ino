#include <NeoPixelBus.h>
#include <stdlib.h>

#define Moisture A3
#define PixelPin A2


const uint8_t PixelCount = 8;
uint8_t ColorSaturation = 60;
uint8_t Brightness = 0;
uint8_t Fadeness = 1;
uint8_t PixelIndex = 0;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
RgbColor black(0);

void setup() {
  pinMode(Moisture, INPUT);
  Serial.begin(9600);
  strip.Begin();
  strip.Show();
}

void loop() {

  for (int j = 0; j < PixelCount; j++) {
    strip.SetPixelColor(j, black);
  }

  int moisture = analogRead(Moisture);
  //Serial.println(moisture);

  if (moisture > 400) {
    for (int i = 0; i < (moisture / 87); i++) {
      strip.SetPixelColor(PixelCount - 1 - i, RgbColor(0, Brightness, 0));
    }
    Brightness = Brightness + Fadeness;
    if (Brightness <= 0 || Brightness >= ColorSaturation) {
      Fadeness = -Fadeness;
    }
  }

  else if (moisture > 200 && moisture <= 400) {
    for (int i = 0; i < (moisture / 87); i++) {
      strip.SetPixelColor(PixelCount - 1 - i, RgbColor(Brightness, Brightness, 0));
    }
    Brightness = Brightness + Fadeness;
    if (Brightness <= 0 || Brightness >= ColorSaturation) {
      Fadeness = -Fadeness;
    }
  }

  else if (moisture > 100 && moisture <= 200) {
    for (int i = 0; i < (moisture / 87); i++) {
      strip.SetPixelColor(PixelCount - 1 - i, RgbColor(Brightness, 0, 0));
    }
    Brightness = Brightness + Fadeness;
    if (Brightness <= 0 || Brightness >= ColorSaturation) {
      Fadeness = -Fadeness;
    }
  }

  else if (moisture <= 100) {
    for (int i = 0; i < PixelCount; i++) {
      for (int j = 0; j < PixelCount; j++) {
        strip.SetPixelColor(j, RgbColor(0, 0, 0));
      }
      strip.SetPixelColor(i, RgbColor(128, 0, 0));
      strip.SetPixelColor(i - 1 < 0 ? PixelCount + (i - 1) : i - 1, RgbColor(78, 0, 0));
      strip.SetPixelColor(i - 2 < 0 ? PixelCount + (i - 2) : i - 2, RgbColor(28, 0, 0));
      strip.Show();
      delay(100);
    }
  }
  strip.Show();
  delay(15);
}
