/*
     Arduino IR Remote Control
	
Mario Pérez Esteso
http://www.geekytheory.com
https://www.youtube.com/user/telecoreference

https://twitter.com/geekytheory

Facebook page! Join us with a LIKE!
https://www.facebook.com/geekytheory
*/
#include <IRremote.h>
#define led1 12
#define led2 11
#define led3 10
#define led4 9
#define led5 8
#define led6 7
#define led7 6
#define led8 5
#define ventilador 4
int sensor_pin = 3;
int boton_pin = 7;
int estado_pin = 13;
IRrecv irrecv(sensor_pin);
IRsend irsend;
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //Inicializo el receptor IR
  pinMode(boton_pin, INPUT);
  pinMode(estado_pin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(ventilador, OUTPUT);
}
int tipo_codigo = -1; //Tipo de código
unsigned long valor_codigo; //Valor del código
unsigned int codigos_desconocidos[RAWBUF]; //Duración si no es conocido
int longitud_codigo; //Long
void storeCode(decode_results *results) {
  tipo_codigo = results->decode_type;
  int count = results->rawlen;
  if (tipo_codigo == UNKNOWN) {
    Serial.println("TIPO DE CóDIGO DESCONOCIDO");
    longitud_codigo = results->rawlen - 1;
    for (int i = 1; i <= longitud_codigo; i++) {
      if (i % 2) {
        codigos_desconocidos[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      } 
      else {
        codigos_desconocidos[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(codigos_desconocidos[i - 1], DEC);
    }
    Serial.println("");
  }
  else {
    if (tipo_codigo == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        //No guardará un valor repetido al instante
        Serial.println("REPETIDO->IGNORADO");
        return;
      }
    } 
    else if (tipo_codigo == SONY) {
      Serial.print("Received SONY: ");
    } 
    else if (tipo_codigo == RC5) {
      Serial.print("RECIBIDO RC5: ");
    } 
    else if (tipo_codigo == RC6) {
      Serial.print("RECIBIDO RC6: ");
    } 
    else {
      Serial.print("TIPO DE CóDIGO DESCONOCIDO");
      Serial.print(tipo_codigo, DEC);
      Serial.println("");
    }
    Serial.println(results->value, HEX);
    valor_codigo = results->value;
    longitud_codigo = results->bits;
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    digitalWrite(estado_pin, HIGH);
    storeCode(&results);
    if (valor_codigo == 0xFF02FD) {//ENTER
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(ventilador,HIGH);
    }
    if (valor_codigo == 0xFF48B7) {//POWER
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(ventilador,LOW);
    }
    if (valor_codigo == 0xFF827D) {//#1
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFFB24D) {//#2
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFFA25D) {//#3
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFF42BD) {//#4
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFF728D) {//#5
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFF629D) {//#6
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFFC23D) {//#7
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFFF20D) {//#8
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,HIGH);
    }
      if (valor_codigo == 0xFFE21D) {//#9
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
    }
    if (valor_codigo == 0xFF00FF) {//#0
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
    }
    if (valor_codigo == 0xFFE817) {//PLAY
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      delay(100);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      delay(100);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,HIGH);
      delay(100);
      digitalWrite(led2,HIGH);
      digitalWrite(led7,HIGH);
      delay(100);
      digitalWrite(led1,HIGH);
      digitalWrite(led8,HIGH);
      delay(100);
      digitalWrite(led8,LOW);
      delay(100);
      digitalWrite(led7,LOW);
      delay(100);
      digitalWrite(led6,LOW);
      delay(100);
      digitalWrite(led5,LOW);
      delay(100);
      digitalWrite(led4,LOW);
      delay(100);
      digitalWrite(led3,LOW);
      delay(100);
      digitalWrite(led2,LOW);
      delay(100);
      digitalWrite(led1,LOW);
      delay(100);
      digitalWrite(led1,HIGH);
      delay(100);
      digitalWrite(led2,HIGH);
      delay(100);
      digitalWrite(led3,HIGH);
      delay(100);
      digitalWrite(led4,HIGH);
      delay(100);
      digitalWrite(led5,HIGH);
      delay(100);
      digitalWrite(led6,HIGH);
      delay(100);
      digitalWrite(led7,HIGH);
      delay(100);
      digitalWrite(led8,HIGH);
      delay(100);
      digitalWrite(led1,LOW);
      delay(100);
      digitalWrite(led2,LOW);
      delay(100);
      digitalWrite(led3,LOW);
      delay(100);
      digitalWrite(led4,LOW);
      delay(100);
      digitalWrite(led5,LOW);
      delay(100);
      digitalWrite(led6,LOW);
      delay(100);
      digitalWrite(led7,LOW);
      delay(100);
      digitalWrite(led8,LOW);
      delay(100);
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,LOW);
      digitalWrite(led8,HIGH);
      delay(500);
      digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
      digitalWrite(led4,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,LOW);
      digitalWrite(led5,HIGH);
      digitalWrite(led8,LOW);
      digitalWrite(led7,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,LOW);
      digitalWrite(led8,HIGH);
      delay(500);
      digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
      digitalWrite(led4,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,LOW);
      digitalWrite(led5,HIGH);
      digitalWrite(led8,LOW);
      digitalWrite(led7,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,LOW);
      digitalWrite(led8,HIGH);
      delay(500);
      digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
      digitalWrite(led4,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,LOW);
      digitalWrite(led5,HIGH);
      digitalWrite(led8,LOW);
      digitalWrite(led7,HIGH);
      delay(250);
      digitalWrite(led1,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led7,LOW);
      delay(100);
      digitalWrite(led1,HIGH);
      digitalWrite(led8,HIGH);
      delay(100);
      digitalWrite(led2,HIGH);
      digitalWrite(led7,HIGH);
      delay(100);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,HIGH);
      delay(100);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      delay(100);
      digitalWrite(led1,LOW);
      digitalWrite(led8,LOW);
      delay(100);
      digitalWrite(led2,LOW);
      digitalWrite(led7,LOW);
      delay(100);
      digitalWrite(led3,LOW);
      digitalWrite(led6,LOW);
      delay(100);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      delay(500);
      digitalWrite(led1,HIGH);
      digitalWrite(led8,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,LOW);
      delay(500);
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,LOW);
      delay(500);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,LOW);
      delay(500);
      delay(500);
      digitalWrite(led4,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led5,LOW);
      delay(500);
      digitalWrite(led3,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led6,LOW);
      delay(500);
      digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(led7,LOW);
      delay(1000);
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      delay(1000);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      delay(100);
    }
    if (valor_codigo == 0xFF807F) {//Flecha arriba
      digitalWrite(ventilador,HIGH);
    }
     if (valor_codigo == 0xFF906F) {//Flecha abajo
      digitalWrite(ventilador,LOW);
    }

    irrecv.resume();//Reanuda el receptor
    digitalWrite(estado_pin, LOW);
  }

}
