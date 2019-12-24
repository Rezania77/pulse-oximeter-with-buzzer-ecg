#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>
 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
 
int LED = 13;
 
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    digitalWrite(LED,!digitalRead(LED));
}
void setup()
{
   
 
 
    lcd.backlight();
    
    lcd.setCursor(0,0);
    lcd.print("Initializing...");
    delay(1000);
    lcd.setCursor(0,1);
    if (!pox.begin()) {
        lcd.print("FAILED");
        while(1);
    } else {
        lcd.print("SUCCESS");
    }
 
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
    delay(1000);
}
 
void loop()
{
pox.update();
if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
float hr = pox.getHeartRate();
float spo2 = pox.getSpO2();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("HR: ");
lcd.print(hr);
lcd.print(" bpm");
lcd.setCursor(0,1);
lcd.print("SpO2: ");
lcd.print(spo2);
lcd.print("%");
Serial.print("Heart rate:");
Serial.print(hr);
Serial.print("bpm / SpO2:");
Serial.print(spo2);
Serial.println("%");
tsLastReport = millis();
}
}
