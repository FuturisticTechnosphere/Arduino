/*This is a program i made back in 2022 in my High School with the help of one of my class mates (A. Parrino) and the help of my teacher @Andix91. The program features
a Light sensor used within the Arduino community.*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
int led = 11;
int vallux1 = 200;
int vallux2 = 300;
int valled = 0;
void setup(void) 
{
 Serial.begin(9600);
 Serial.println("Light Sensor Test"); Serial.println("");
  pinMode(11, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT); 
  if(!tsl.begin())
  {
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  Serial.println("");
}
void loop(void) 
{   
  sensors_event_t event;
  tsl.getEvent(&event);
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" lux");
  }
  else
  {
    Serial.println("Sensor overload");
  }
  delay(250);
  if (event.light <= vallux1)
  {
    valled = valled + 10;
    analogWrite(11, valled);
  }
  if (event.light >= vallux1 && event.light <= vallux2)
  {
    analogWrite(11, valled);
  }
  if (event.light >= vallux2)
  {
    valled = valled - 10;
    analogWrite(11, valled);
  }
  if (valled = 255)
  {
    valled = valled;
    analogWrite(11, valled);
  }}
