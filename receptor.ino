#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // Pines CE, CSN
const uint64_t address = 0xE8E8F0F0E1LL;  // Misma dirección que el transmisor

const int ledPin = 3;  // Pin del LED

void setup() {
  pinMode(ledPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();  // Modo receptor
}

void loop() {
  if (radio.available()) {
    bool receivedState;
    radio.read(&receivedState, sizeof(receivedState));  // Recibir datos
    digitalWrite(ledPin, receivedState);  // Controla el LED
  }
}
