#include <SPI.h>
#include <LoRa.h>

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

  // Налаштування LoRa
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Помилка запуску LoRa!");
    while (1);
  }
}

void loop() {
  // Перевірка, чи є прийняті дані
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Якщо пакет є, зчитуємо його
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }

    // Виведення отриманих координат на серійний монітор
    Serial.println(received);
  }
}