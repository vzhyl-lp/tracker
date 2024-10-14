#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Налаштування GPS і LoRa
TinyGPSPlus gps;
SoftwareSerial gpsSerial(3, 4); // GPS TX на D3, GPS RX на D4

// Піни для LoRa
#define SCK 13
#define MISO 12
#define MOSI 11
#define SS 10
#define RST 9
#define DIO0 2

void setup() {
  // Налаштування серійного монітора
  Serial.begin(9600);
  gpsSerial.begin(9600);

  // Налаштування LoRa
  LoRa.setPins(SS, RST, DIO0); 

  if (!LoRa.begin(433E6)) {
    Serial.println("Помилка запуску LoRa!");
    while (1);
  }
  Serial.println("LoRa модуль запущений!");
}

void loop() {
  // Читання даних з GPS
  while (gpsSerial.available() > 0) {
  gps.encode(gpsSerial.read());
  }


  // Перевірка наявності нових даних GPS gps.location.isUpdated() gps.location.isValid()
  if (gps.location.isValid()) {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    // Виведення координат у серійний монітор
    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    

    // Передача координат через LoRa
    LoRa.beginPacket();
    LoRa.print(latitude, 6);
    LoRa.print(',');
    LoRa.print(longitude, 6);
    LoRa.endPacket();

    // Затримка між передачами
     
   }
  delay(10000);
}