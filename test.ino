/*
Sample program that sends temperature
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

const int buzzer = 9; // Buzzer pin

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();

int temp;
String temp_unit;
const bool temp_f = false; // Switch units
const byte bmp_addr = 0x76; // Address for our BMP280

SoftwareSerial HC12(5,4); // Define serial for the HC-12 module

void setup() {
  Serial.begin(9600);
  while ( !Serial ) delay(100); // wait for native usb
  Serial.println(F("Serial started"));
  
  HC12.begin(9600);
  while ( !Serial ) delay(100); // Wait for HC12
  Serial.println(F("HC-12 started"));
  
  if (temp_f == true) {
    temp_unit = "F";
  }
  else {
    temp_unit = "C";
  }
  Serial.print(F("Unit is: "));
  Serial.println(temp_unit);
  
  unsigned status;
  status = bmp.begin(bmp_addr);
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
}

void loop() {
  tone(buzzer,1000);
  sensors_event_t temp_event;
  bmp_temp->getEvent(&temp_event);
  temp = temp_event.temperature;
  if (temp_f == true) {
    temp = temp_event.temperature * 1.8 + 32;
  }
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *");
  Serial.print(temp_unit);
  Serial.println();

  // Float to char conversion (ugh)
  char sz[20] = {' '} ;
  int temp_int = (int) temp;
  float temp_float = (abs(temp) - abs(temp_int)) * 100000;
  int temp_fra = (int)temp_float;
  sprintf (sz, "%d.%05d", val_int, val_fra);
  HC12.write(send);
  HC12.write("\n");
  noTone(buzzer);
  delay(2000);
}
