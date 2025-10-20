#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // Pines CE, CSN
const uint64_t address = 0xE8E8F0F0E1LL;  // Dirección única para la comunicación

const int buttonPin = 2;  // Pin del pulsador
bool buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Resistencia pull-up interna
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();  // Modo transmisor
}

void loop() {
  buttonState = digitalRead(buttonPin); // Leer el estado del botón
  bool ledState = (buttonState == LOW) ? HIGH : LOW;  // Botón presionado → LED ENCENDIDO

  radio.write(&ledState, sizeof(ledState));  // Enviar estado del LED
  delay(100);  // Pequeño retraso para estabilizar la comunicación
}
