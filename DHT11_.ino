/*
  Arduino Humidity and Temperature Sensor with LCD Display
  
  Author: Zuccaro Salvatore
  Date: 04/12/2023
  Description:
  This Arduino program interfaces with a DHT11 sensor to measure humidity and temperature.
  The readings are displayed on a 16x2 LCD screen. The user can select whether to display
  humidity or temperature through the serial monitor by entering 'u' or 't', respectively.

  Hardware:
  - DHT11 sensor connected to digital pin 8
  - 16x2 LCD screen connected to the following pins:
    - RS: 12, EN: 11, D4: 5, D5: 4, D6: 3, D7: 2

  Libraries:
  - LiquidCrystal.h for LCD interfacing
  - DHT.h for DHT sensor communication

  Note: Ensure that the required libraries are installed in the Arduino IDE.

  License: GNU General Public License (GPL)

  References:
  - DHT sensor library: https://github.com/adafruit/DHT-sensor-library
  - LiquidCrystal library: https://www.arduino.cc/en/Reference/LiquidCrystal

*/
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 8        // Define the digital pin to which the DHT sensor is connected
#define DHTTYPE DHT11   // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);   // Create a DHT object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Create a LiquidCrystal object

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // Define the LCD pin connections
float hr, temp;   // Variables to store humidity and temperature readings
char Select;      // Variable to store user selection ('u' for humidity, 't' for temperature)

// Function to show humidity and temperature values on the serial monitor
void showValue(float U, float T) {
  U = dht.readHumidity();      // Read humidity
  Serial.print(F("Humidity: "));
  Serial.print(U);
  T = dht.readTemperature();   // Read temperature
  Serial.print(F("%  Temperature: "));
  Serial.print(T);
  Serial.println(F("°C "));
}

// Function to display temperature on the LCD
void Temperature(float T) {
  T = dht.readTemperature();   // Read temperature
  lcd.setCursor(0, 0);
  lcd.print(F("Temperature:   "));
  lcd.setCursor(0, 1);
  lcd.print(T);
  lcd.write(223);   // Display the degree symbol
  lcd.print(F("C "));
}

// Function to display humidity on the LCD
void Humidity(float H) {
  H = dht.readHumidity();      // Read humidity
  lcd.setCursor(0, 0);
  lcd.print(F("Humidity':  "));
  lcd.setCursor(0, 1);
  lcd.print(H);
  lcd.print(F("%"));
}

void setup() {
  Serial.begin(9600);
  dht.begin();   // Initialize the DHT sensor
  lcd.begin(16, 2);   // Initialize the LCD screen
  lcd.setCursor(0, 0);
  lcd.print(F("Humidity detect"));
  lcd.setCursor(0, 1);
  lcd.print(F("and Temperature"));
  delay(2000);
  lcd.clear();   // Clear the LCD screen
}

void loop() {
  delay(500);
  showValue(hr, temp);   // Call the function to show humidity and temperature values
  Select = Serial.read();   // Read user input from the serial monitor

  // Check user input and display either humidity or temperature on the LCD
  if (Select == 'u')
    Humidity(hr);
  else {
    if (Select == 't')
      Temperature(temp);
  }
}
