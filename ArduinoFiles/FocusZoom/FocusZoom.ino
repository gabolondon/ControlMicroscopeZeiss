#include <Arduino.h>
const int pinPOTluz = A4;
const int pinPOTfocus = A7;
const int pinPWMfocus = 5; // conector J2 cable morado
const int pinPOTzoom = A6; 
const int pinPWMzoom = 3; // conector J2 cable rojo
const int pinIN1 = 7;  // conector J2 cable cafe
const int pinIN2 = 8; // conector J2 cable negro
const int pinIN3 = 9; // conector J2 cable blanco
const int pinIN4 = 10; // conector J2 cable gris
const int pinZoomUP = A3; // cambiar cables para salida en A4
const int pinZoomDown = A2; // cambiar cables para salida en A3
const int pinFocusDown = A0;// cambiar cables para salida en A2
const int pinFocusUp = A1;// cambiar cables para salida en A1
const int pinLightUp = 6; // crear cables con conector J3
const int pinLightDown = A5; // crear cables con conector J3
const int pinLightPWM = 12;// crear cables con conector J3
const int pinRelay = 4;    // control del relé


unsigned long tiempoOn;     
unsigned long tiempoOff;
unsigned long timer = 1500;
int valPWMfocus=0;
int valPWMzoom=0;
int valPWMluz=0;
int cambioPotLight=0;
String modoLight = "pot";
boolean botonUpPresionado = HIGH;
boolean botonDownPresionado = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(pinPWMfocus, OUTPUT);
  pinMode(pinPWMzoom, OUTPUT);
  pinMode(pinLightPWM, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinLightUp, INPUT_PULLUP);
  pinMode(pinLightDown, INPUT_PULLUP);
  pinMode(pinZoomUP, INPUT_PULLUP);
  pinMode(pinZoomDown, INPUT_PULLUP);
  pinMode(pinFocusDown, INPUT_PULLUP);
  pinMode(pinFocusUp, INPUT_PULLUP);
  pinMode(pinRelay, OUTPUT);
  

}

void loop() {
  valPWMfocus = map(analogRead(pinPOTfocus), 0, 1023, 100, 255);  // convertir a valor PWM arrancando desde 100 porque los motores no aceptan bajos niveles de V
  Serial.print("valor de PWM focus: ");
  Serial.print(valPWMfocus);
  analogWrite(pinPWMfocus,valPWMfocus);
  valPWMzoom = map(analogRead(pinPOTzoom), 0, 1023, 100, 255);  // convertir a valor PWM arrancando desde 100 porque los motores no aceptan bajos niveles de V
  Serial.print(" ; valor de PWM zoom: ");
  Serial.print(valPWMzoom);
  analogWrite(pinPWMzoom,valPWMzoom);
  //if (analogRead(pinLightPWM)!=cambioPotLight){
   // modoLight = "pot";
  //}
  //if (modoLight == "pot"){
  //  valPWMluz = map(analogRead(pinLightPWM), 0, 1023, 50, 255);  // convertir a valor PWM arrancando desde 100 porque los motores no aceptan bajos niveles de V
  //  Serial.print(" ; valor de PWM light: ");
  //  Serial.println(valPWMluz);  
  //  analogWrite(pinLightPWM,valPWMluz);
  //}
  //if (digitalRead(pinLightUp) == LOW or digitalRead(pinLightDown)== LOW){
  //  tiempoOn=millis();
  //  modoLight= "pedal";
  //}else{
  //  tiempoOff=millis();
  //}
  //if (modoLight == "pedal"){
  //  if (digitalRead(pinLightUp) == LOW){
  //    if (tiempoOn-tiempoOff >= timer && valPWMluz < 255){
          //Serial.print("Cumplida espera de 1.5 seg, subiendo luz PWM ");
  //        valPWMluz++;
  //        delay(20);
  //    } 
  //  }else {
  //    if (tiempoOn-tiempoOff < timer && botonUpPresionado ==LOW){
  //      valPWMluz=255;
  //    }
  //  }
  //  if (digitalRead(pinLightDown) == LOW){
  //    if (tiempoOn-tiempoOff >= timer && valPWMluz > 100){
          //Serial.print("Cumplida espera de 1.5 seg, bajando luz PWM ");
  //        valPWMluz--;
  //        delay(20);
  //    } 
  //  }else {
  //    if (tiempoOn-tiempoOff < timer && botonDownPresionado ==LOW){
  //      valPWMluz=0;
  //    }
  //  } 
  //analogWrite(pinLightPWM,valPWMluz);
  //}
  if (digitalRead(pinLightUp) == LOW){
      LightOn();
  }
  if (digitalRead(pinLightDown) == LOW){
      LightOff();
  }

  if (digitalRead(pinZoomUP)==LOW){
      Serial.println("presionado pedal ZoomUP");
      zoomup();
    }
  if (digitalRead(pinZoomDown)==LOW){
      Serial.println("presionado pedal ZoomDOWN");
      zoomdown();
    }
  if (digitalRead(pinFocusDown)==LOW){
      Serial.println("presionado pedal FocusDOWN");
      focusdown();
    }
    if (digitalRead(pinFocusUp)==LOW){
      Serial.println("presionado pedal FocusUP");
      focusup();
    }
    if (digitalRead(pinZoomUP)==HIGH && digitalRead(pinZoomDown)==HIGH){ //Se detiene solo el ZOOM al no presionar nada porque sino se puede quedar metida la orden de FOCUS
      pararzoom();
      delay(100);
    }
    if (digitalRead(pinFocusDown)==HIGH && digitalRead(pinFocusUp)==HIGH){ //Se detiene solo el FOCUS al no presionar nada porque sino se puede quedar metida la orden de ZOOM
      pararfocus();
      delay(100);
    }
  cambioPotLight = analogRead(pinLightPWM);    
  botonUpPresionado =digitalRead(pinLightUp);
  botonDownPresionado =digitalRead(pinLightDown);
}
void zoomup(){
  digitalWrite(pinIN1,HIGH);
  digitalWrite(pinIN2,LOW);
  Serial.println("Moviendo zoom para arriba...");
}
void zoomdown(){
  digitalWrite(pinIN1,LOW);
  digitalWrite(pinIN2,HIGH);
  Serial.println("Moviendo zoom para abajo...");
}
void focusup(){
  digitalWrite(pinIN3,HIGH);
  digitalWrite(pinIN4,LOW);
  Serial.println("moviendo focus para arriba...");
}
void focusdown(){
  digitalWrite(pinIN3,LOW);
  digitalWrite(pinIN4,HIGH);
  Serial.println("Moviendo focus para abajo...");
}
void pararzoom(){
  digitalWrite(pinIN1,LOW);
  digitalWrite(pinIN2,LOW);
  Serial.println("motores zoom detenidos detenidos");
}
void pararfocus(){
  digitalWrite(pinIN3,LOW);
  digitalWrite(pinIN4,LOW);
  Serial.println("motores focus detenidos detenidos");
}

void LightOn(){
  digitalWrite(pinRelay,LOW);
  Serial.println("encendiendo luz");
  
}
void LightOff(){
  digitalWrite(pinRelay, LOW);  
  Serial.println ("apagando luz");
 
}
