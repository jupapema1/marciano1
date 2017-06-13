#include <Servo.h>

//
//DECLARACION DE LAS COSTANTES Y VALORES INICIALES
//

int mensaje = 0;
int liminfx = 10; //limite inferior x 
int limsupx = 170; //limite superior x 
int liminfy = 90; //limite inferior y
int limsupy = 160; //limite superior y
int velocidad = 8; //velocidad de giro
int estado = 0;
int posy = 115;
int led = 13;
int derM1 = 10;
int izqM1 = 9;
int derM2 = 6;
int izqM2 = 5;
int x=115;
int y=90;
int ang=0;
int posx = 90;
Servo servo1;
Servo servo2;

//
//ASIGNACION DE LOS PINES DE SALIDA DEL ARDUINO
//
//SALIDAS:
//    -pin 13 -> servomotor eje x
//    -pin 12 -> servomotor eje y
//    -pin 10 -> giro motor derecho
//    -pin 9 -> giro motor derecho
//    -pin 6 -> giro motor izquiedo
//    -pin 5 -> giro motor izquierdo
//
void setup() {
  Serial.begin(9600);
  servo1.attach(13);
  servo2.attach(12);
  pinMode(derM1, OUTPUT);
  pinMode(izqM1, OUTPUT);
  pinMode(derM2, OUTPUT);
  pinMode(izqM2, OUTPUT);
}

//
//FUNCIONES DE CONTROL DE MOTORES Y SERVOMOTORES
//

void motor1(int a){
  if(a==0){
    digitalWrite(izqM1, 0);
    digitalWrite(derM1, 0);
  }
  if(a==1){
    digitalWrite(izqM1, 1);
    digitalWrite(derM1, 0);
  }
  if(a==2){
    digitalWrite(izqM1, 0);
    digitalWrite(derM1, 1);
  }
}

void motor2(int a){
  if(a==0){
    digitalWrite(izqM2, 0);
    digitalWrite(derM2, 0);
  }
  if(a==1){
    digitalWrite(izqM2, 1);
    digitalWrite(derM2, 0);
  }
  if(a==2){
    digitalWrite(izqM2, 0);
    digitalWrite(derM2, 1);
  }
}


void giro1(int ang) {
  if (ang > liminfx && ang <= limsupx)
    servo1.write(ang);
}

void giro2(int ang) {
  if (ang > liminfy && ang <= limsupy)
    servo2.write(ang);
}

//
//FUNCION PRINCIPAL
//
//Descripcion:
//    Esta es la funcion principal que segun lo ingresado por el bluetooth activa sus respectivas salidas.
//Entrada:
//    -Serial
//Salidas:
//    -Las salidas están definidas en la funcion setup
//

void loop() {

  mensaje = Serial.read();

  //delay(500);
  giro2(posy);
  giro1(posx);

  if (mensaje=='0'){
    motor2(0);
    motor1(0);
  }
  if (mensaje=='1'){
    motor1(1);
    motor2(1);
  }
  if (mensaje=='2'){
    motor2(2);
    motor1(2);
  }
  if (mensaje=='3'){
    motor1(1);
    motor2(2);
  }
  if (mensaje=='4'){
    motor1(2);
    motor2(1);
  }

  if (mensaje == '5') {
    if (posy < limsupy) {
      posy += velocidad;
    }
  }
  if (mensaje == '6') {
    if (posy > liminfy) {
      posy -= velocidad;
    }
  }
  if (mensaje == '7') {
    if (posx > liminfx) {
      posx -= velocidad;
    }
  }
  if (mensaje == '8') {
    if (posx < limsupx)
      posx += velocidad;
  }
}

