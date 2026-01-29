#include <Wire.h>
#include <SPI.h>
#include <NRFLite.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

struct WxPacket {
  uint8_t nodeId;
  uint32_t seq;
  int16_t tempC_x100;
  uint16_t press_hPa_x10;
};

const uint8_t RADIO_ID = 0;

NRFLite radio;
RTC_DS3231 rtc;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

bool haveRTC = false;

WxPacket lastPkt{};
bool havePkt = false;
uint32_t lastRxMillis = 0;

static float cToF(float c) { return (c * 9.0f / 5.0f) + 32.0f; }

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  haveRTC = rtc.begin();

  if (!radio.init(RADIO_ID, 9, 10)) {
    Serial.println("NRF init failed");
    while (1) delay(100);
  }

  Serial.println("Base RX ready");
}

void loop() {
  while (radio.hasData()) {
    radio.readData(&lastPkt);
    havePkt = true;
    lastRxMillis = millis();

    Serial.print("RX node=");
    Serial.print(lastPkt.nodeId);
    Serial.print(" seq=");
    Serial.print(lastPkt.seq);
    Serial.print(" tempC_x100=");
    Serial.print(lastPkt.tempC_x100);
    Serial.print(" press_hPa_x10=");
    Serial.println(lastPkt.press_hPa_x10);
  }

  drawScreen();
  delay(150);
}

void drawScreen() {
  display.clearDisplay();
  display.setCursor(0, 0);

  // Time line
  if (haveRTC) {
    DateTime now = rtc.now();
    char tbuf[12];
    snprintf(tbuf, sizeof(tbuf), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    display.print("Time ");
    display.println(tbuf);
  } else {
    display.println("Time (no RTC)");
  }

  display.println("----------------");

  if (!havePkt) {
    display.println("Waiting for WX...");
    display.display();
    return;
  }

  float tempC = lastPkt.tempC_x100 / 100.0f;
  float tempF = cToF(tempC);
  float presshPa = lastPkt.press_hPa_x10 / 10.0f;

  display.print("Node ");
  display.print(lastPkt.nodeId);
  display.print("  Seq ");
  display.println(lastPkt.seq);

  display.print("Temp ");
  display.print(tempF, 1);
  display.println(" F");

  display.print("Pres ");
  display.print(presshPa, 1);
  display.println(" hPa");

 uint32_t ageS = (millis() - lastRxMillis) / 1000;

display.print("Age  ");
display.print(ageS);
display.print(" s  ");

if (ageS > 6) {
  display.println("STALE");
} else {
  display.println("LIVE");
}

  display.display();
}
