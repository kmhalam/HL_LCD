// DHT Readme
// ==============================
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor


// include the library code:
#include <LiquidCrystal.h>

#include "DHT.h"

#define DHTPIN 7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));
  dht.begin();


  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.write("Humidity & Temp");
  lcd.setCursor(0,1);
  lcd.write("H:");
  lcd.setCursor(4,1);
  lcd.write("%");  
  lcd.setCursor(7,1);
  lcd.write("T:");
  lcd.setCursor(11,1);
  lcd.write((char)223);
  lcd.setCursor(12,1);
  lcd.write("C");
}


void loop() {


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  
  int humidity_sensorValue = h;
  lcd.setCursor(2,1);
  lcd.print(humidity_sensorValue);

  int temperature_sensorValue = t;
  lcd.setCursor(9,1);
  lcd.print(temperature_sensorValue);

  // Wait a few seconds between measurements.
  delay(2000);
  

}
