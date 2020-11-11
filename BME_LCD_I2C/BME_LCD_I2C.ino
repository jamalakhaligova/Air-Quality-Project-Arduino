#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
int sensorValue;
LiquidCrystal_I2C lcd(0x3f,16,2);
int co2ppm =0;
unsigned long previousMillis = 0;       
const long interval = 1000; 
Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
float temp, humidity;


void setup() {
  // put your setup code here, to run once:
  unsigned status;
  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    while (1);
  }
  lcd.begin();

}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
 
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(0);
  co2ppm = map(sensorValue,0,1023,400,5000);
  
  lcd.clear();
  temp = bme.readTemperature();
  humidity = bme.readHumidity();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" *C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0,2);
  lcd.print("ArQ=");
  lcd.print(co2ppm);
  lcd.print(" PPM");
  }
  
  
}
