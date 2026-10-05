#include <Arduino.h>
// ALARMA PUERTA ABIERTA
const int puertaAbiertaPin = 14;
bool puertaAbierta=true;
bool alarmaPuertaAbierta=false;
String comandoActual = "";

bool leePinDigitalAntirebote(int pin, int tiempo) {
  static int estadoAnterior = HIGH;
  static int estadoPIN = HIGH;
  static unsigned long tiempoUltimaLectura = 0;   
  unsigned long tiempoInicio = millis();
  int lecturaActual = digitalRead(pin);
  if (lecturaActual != estadoAnterior) {
    estadoAnterior = lecturaActual; 
    tiempoUltimaLectura = tiempoInicio;  
  }
  else if ((tiempoInicio - tiempoUltimaLectura) >= tiempo) {
    estadoPIN = lecturaActual;    
 
  }      
  return(estadoPIN);    
}
void setup( ) {
  Serial.begin(115200);
  Serial.println("Sistema iniciado");
  pinMode(puertaAbiertaPin,INPUT_PULLUP);

}

void loop() {
  bool lecturaActualPuerta=leePinDigitalAntirebote(puertaAbiertaPin, 50 );
  if ((!alarmaPuertaAbierta) && (lecturaActualPuerta==LOW)) {
    alarmaPuertaAbierta=true;
    Serial.println("ALARMA: Puerta abierta");
  }
   
 if (Serial.available() > 0) {
        char c = Serial.read();        
        Serial.print(c);
        // Si detectamos fin de línea, evaluamos el comando completo
        if (c == '\n' || c == '\r') {
            comandoActual.trim(); // Limpiamos espacios o retornos de carro
            Serial.println(c);
            if (comandoActual.length() > 0) {
                if (comandoActual.equalsIgnoreCase("RESET")) {
                  alarmaPuertaAbierta=false;
                  Serial.println("ALARMA: Reset");                 
                }
            }    
            comandoActual="";                    
        }
        else {
          comandoActual += c;
        }
  }


//LECTURA SIN REBOTES 
/*bool lecturaActualPuerta=leePinDigitalAntirebote(puertaAbiertaPin, 100 );
if (lecturaActualPuerta!=puertaAbierta)
 {
  puertaAbierta=lecturaActualPuerta;
  if (lecturaActualPuerta==LOW) {
    Serial.println("ALARMA: Puerta abierta");
  }  
 }*/

  //LECTURA CON REBOTES 
 /*bool lecturaActualPuerta=digitalRead(puertaAbiertaPin);
 if (lecturaActualPuerta!=puertaAbierta)
 {
  puertaAbierta=lecturaActualPuerta;
  Serial.println("ALARMA: Puerta abierta");
 }*/

 
 // LECTURA CONTINUA MIESTRAS ESTA PULSADO
 /*if (digitalRead(puertaAbiertaPin)==LOW) {
  Serial.println("ALARMA: Puerta abierta");
 }*/

}

 