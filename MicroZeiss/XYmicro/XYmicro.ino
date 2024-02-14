const int pinIN3 = 11;
const int pinIN4 = 12;
const int pinTA3 = 2;
const int pinArriba = 3;
const int pinIzquierda = 4;
const int pinTA1 = 5;
const int pinAbajo = 6;
const int pinTA4 = 7;
const int pinTA2 = 8;
const int pinDerecha = 9;
const int pinBtnCentrar = 10;
const int pinIN2 = 1;
const int pinIN1 = 0;
bool centrando=LOW;

 
void setup()
{
  //Serial.begin(115200);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinTA3, INPUT_PULLUP);
  pinMode(pinArriba, INPUT_PULLUP);
  pinMode(pinIzquierda, INPUT_PULLUP);
  pinMode(pinTA1, INPUT_PULLUP);
  pinMode(pinAbajo, INPUT_PULLUP);
  pinMode(pinTA4, INPUT_PULLUP);
  pinMode(pinTA2, INPUT_PULLUP);
  pinMode(pinDerecha, INPUT_PULLUP);
  pinMode(pinBtnCentrar, INPUT_PULLUP);
}
 
void loop()
{
   if (digitalRead(pinBtnCentrar)==LOW){
    centrando = LOW;
    Serial.print("Boton Centrado pulsado, centrando...............");
    while(!centrando){
      Serial.print("Estado de: TA1: ");
      Serial.print(digitalRead(pinTA1));
      Serial.print(" TA2: ");
      Serial.print(digitalRead(pinTA2));
      Serial.print(" TA3: ");
      Serial.print(digitalRead(pinTA3));
      Serial.print(" TA4: ");
      Serial.print(digitalRead(pinTA4));
      if(digitalRead(pinTA1)==LOW && digitalRead(pinTA2)==HIGH){
        abajo();
      }else if(digitalRead(pinTA1)==HIGH && digitalRead(pinTA2)==LOW){
        arriba();
      }else{
        pararY();
      }
      if(digitalRead(pinTA3)==HIGH && digitalRead(pinTA4)==LOW){
        derecha();
      }else if(digitalRead(pinTA3)==LOW && digitalRead(pinTA4)==HIGH){
        izquierda();
      }else {
        pararX();
      }
      if(digitalRead(pinDerecha)==LOW || digitalRead(pinIzquierda)==LOW || digitalRead(pinAbajo)==LOW || digitalRead(pinArriba)==LOW){
        pararX();
        pararY();
        centrando = HIGH;
      }
    }
   }else{
    if (digitalRead(pinArriba)==LOW){
      //Serial.println("presionado pedal ARRIBA");
      arriba();
    }
    if (digitalRead(pinAbajo)==LOW){
      //Serial.println("presionado pedal ABAJO");
      abajo();
    }
    if (digitalRead(pinIzquierda)==LOW){
      //Serial.println("presionado pedal IZQUIERDA");
      izquierda();
    }
    if (digitalRead(pinDerecha)==LOW){
      //Serial.println("presionado pedal DERECHA");
      derecha();
    }
    if (digitalRead(pinDerecha)==HIGH && digitalRead(pinIzquierda)==HIGH && digitalRead(pinAbajo)==HIGH && digitalRead(pinArriba)==HIGH){
      pararX();
      pararY();
      delay(100);
    }
   }
   
}
void derecha(){
  digitalWrite(pinIN1,HIGH);
  digitalWrite(pinIN2,LOW);
  Serial.println("Moviendo a la derecha...");
}
void izquierda(){
  digitalWrite(pinIN1,LOW);
  digitalWrite(pinIN2,HIGH);
  Serial.println("Moviendo a la izquierda...");
}
void arriba(){
  digitalWrite(pinIN3,HIGH);
  digitalWrite(pinIN4,LOW);
  //Serial.println("Moviendo a la arriba...");
}
void abajo(){
  digitalWrite(pinIN3,LOW);
  digitalWrite(pinIN4,HIGH);
  Serial.println("Moviendo a la abajo...");
}
void pararY(){
  digitalWrite(pinIN3,LOW);
  digitalWrite(pinIN4,LOW);
  Serial.println("motores en Y detenidos");
}
void pararX(){
  digitalWrite(pinIN1,LOW);
  digitalWrite(pinIN2,LOW);
  Serial.println("motores en X detenidos");
}
