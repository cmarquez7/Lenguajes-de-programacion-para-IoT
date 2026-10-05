#include <Arduino.h>
// ALARMA PUERTA ABIERTA
const int puertaAbiertaPin = 14;

bool leePinDigitalAntirebote(int pin, int tiempo) {
  static int estadoAnterior = HIGH;
  static unsigned long tiempoUltimaLectura = 0;   
  unsigned long tiempoInicio = millis();
  int lecturaActual = digitalRead(pin);
  if (lecturaActual != estadoAnterior) {
    Serial.print("Cambio de estado detectado: ");
    Serial.println(lecturaActual);  
    tiempoUltimaLectura = tiempoInicio;
  }
  if ((tiempoInicio - tiempoUltimaLectura) >= tiempo) {
    estadoAnterior = lecturaActual;
  }
  return estadoAnterior;
}
void setup( ) {
  Serial.begin(115200);
  Serial.println("Sistema iniciado");
  pinMode(puertaAbiertaPin,INPUT_PULLUP);

}

void loop() {
 if (leePinDigitalAntirebote(puertaAbiertaPin, 100 ) == LOW) {
   Serial.println("ALARMA: Puerta abierta");
 }
}

 