#include <Servo.h>
#include <SoftwareSerial.h>

//declarar BT y SS
SoftwareSerial mySerial(2, 3);// RXD, TXD
int dataFromBT = 1;
int temp;

//declarar los pines de motoresy servo :v
#define m1a 9
#define m1b 10
#define m1c 11
#define m1d 12
#define m2a 8
#define m2b 7
#define m2c 6
#define m2d 5
#define s 4

int stepSequence[8][4] = {

  {0,0,0,1},
  {0,0,1,1},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0},
  {1,1,0,0},
  {1,0,0,0},
  {1,0,0,1},
};

int ahre;
// valores pal servo
int sv = 30;
int tv;

Servo tor;

void setup() {
  
  Serial.begin(57600);

  // esta parte es para que quede lindo como se ve el monitor serial xD
  Serial.println("inicializando TANK control!");
  Serial.println("by Federico Videla © 2017");
  Serial.print("T");
  delay(100);
  Serial.print("A");
  delay(100);
  Serial.print("N");
  delay(100);
  Serial.print("K");
  delay(100);
  Serial.print("4");
    delay(100);
  Serial.print("c");
    delay(100);
  Serial.print("o");
    delay(100);
  Serial.print("n");
    delay(100);
  Serial.print("t");
    delay(100);
  Serial.print("r");
    delay(100);
  Serial.print("o");
    delay(100);
  Serial.print("l");
    delay(100);
  Serial.println("!!");
    delay(100);
  // fin de la parte del monitor serial

  // my serial para obtener los datos del modulo BT
  mySerial.begin(9600);

  // servo de torreta
  tor.attach(s);
  
  //modos de pines de los motores
  pinMode(13, OUTPUT); 
  pinMode(m1a, OUTPUT); 
  pinMode(m1b, OUTPUT);
  pinMode(m1c, OUTPUT); 
  pinMode(m1d, OUTPUT); 
  pinMode(m2a, OUTPUT); 
  pinMode(m2b, OUTPUT); 
  pinMode(m2c, OUTPUT); 
  pinMode(m2d, OUTPUT); 
}
 
void loop() {
  //función principal que compara los resultados obtenidos de myserial para hacer algo :D
  comparar();
  comparardenuevo();
}

void comparar(){
  //checkea que este disponible el modulo bt y guarda los datos recibidos en dataFromBT
  if (mySerial.available()){
     dataFromBT = mySerial.read();
     //Serial.println(dataFromBT);
  }
  //comparación de resultados, podría haber usado un switch case pero ya lo hice así q ggwp, igual funciona
  if (dataFromBT == '0') {
    // adelante
    adelante();
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    Serial.println("adelante");
  } else if (dataFromBT == '1') {
    // atras
    atras();
    Serial.println("atras");
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  } else if (dataFromBT == '2') {
    // inzquierda
    izquierda();
    Serial.println("izquierda");
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  } else if (dataFromBT == '3') {
    // derecha
    derecha();
    Serial.println("derecha");
    digitalWrite(13, HIGH);
        delay(100);
    digitalWrite(13, LOW);
  } else if (dataFromBT == '4') {
    // detenerse
    detenerse();
    Serial.println("detenerse");
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);  
  } else if (dataFromBT == '5'){
    if (sv <= 180){
      if (sv != 180){
    sv = sv + 1 ;
    tv = map(sv, 0, 60, 0, 180);
    Serial.print("servo : ");
    Serial.print(tv);
    Serial.print("  value: ");
    Serial.println(sv);
    torfuncion(tv);}
    } 
  } else if (dataFromBT == '6'){
    sv = sv - 1;
    if (sv >= 0){
    if (sv != 0){
    tv = map(sv, 0, 60, 0, 180);
    Serial.print("servo : ");
    Serial.print(tv);
    Serial.print("  value: ");
    Serial.println(sv);
    torfuncion(tv);
    }
    }
  } else if (dataFromBT == '7'){
    banear();
    }
  //un pequeño delay entre cada comando :D
  //delay(90);
  }

  void comparardenuevo(){
    if(ahre == 1){
      turnForward();
      nullTurn();
      }
    else if(ahre == 2){
      turnBackward();
      nullTurn();
      }
    else if(ahre == 3){
      turnLeft();
      nullTurn();
      }
    else if(ahre == 4){
      turnRight();
      nullTurn();
      }
    else if(ahre == 5){
      nullTurn();
      }
    }

//
// TODAS LAS FUNCIONES PARA CONTROLAR EL TANQUE
// estan justo abajo :D
//
void banear(){
  digitalWrite(3, 1);
  Serial.println("banea2 xDxdxD");
  }

void torfuncion(int x){
  tor.write(x);
  }

void adelante(){
  ahre = 1; 
}
void atras(){
  ahre = 2;
}
void izquierda(){
  ahre = 3;
}
void derecha(){
  ahre = 4;
}
void detenerse(){
  ahre = 5;
}

void turnForward(){
    for (int i = 0; i <= 7; i++){

      digitalWrite(m1a, stepSequence[i][0]);  
      digitalWrite(m1b, stepSequence[i][1]); 
      digitalWrite(m1c, stepSequence[i][2]); 
      digitalWrite(m1d, stepSequence[i][3]); 
      digitalWrite(m2a, stepSequence[i][0]);  
      digitalWrite(m2b, stepSequence[i][1]); 
      digitalWrite(m2c, stepSequence[i][2]); 
      digitalWrite(m2d, stepSequence[i][3]); 
      delay(1);
    }
}

void turnBackward(){
    for (int i = 7; i >= 0; i--){

     digitalWrite(m1a, stepSequence[i][0]);  
     digitalWrite(m1b, stepSequence[i][1]); 
     digitalWrite(m1c, stepSequence[i][2]); 
     digitalWrite(m1d, stepSequence[i][3]);
     digitalWrite(m2a, stepSequence[i][0]);  
     digitalWrite(m2b, stepSequence[i][1]); 
     digitalWrite(m2c, stepSequence[i][2]); 
     digitalWrite(m2d, stepSequence[i][3]);  
     delay(1);
    }
}

void turnRight(){
    for (int i = 7; i >= 0; i--){

     digitalWrite(m1a, stepSequence[i][0]);  
     digitalWrite(m1b, stepSequence[i][1]); 
     digitalWrite(m1c, stepSequence[i][2]); 
     digitalWrite(m1d, stepSequence[i][3]);
     digitalWrite(m2d, stepSequence[i][0]);  
     digitalWrite(m2c, stepSequence[i][1]); 
     digitalWrite(m2b, stepSequence[i][2]); 
     digitalWrite(m2a, stepSequence[i][3]);  
     delay(1);
    }
}

void turnLeft(){
    for (int i = 7; i >= 0; i--){
     digitalWrite(m1d, stepSequence[i][0]);  
     digitalWrite(m1c, stepSequence[i][1]); 
     digitalWrite(m1b, stepSequence[i][2]); 
     digitalWrite(m1a, stepSequence[i][3]);
     digitalWrite(m2a, stepSequence[i][0]);  
     digitalWrite(m2b, stepSequence[i][1]); 
     digitalWrite(m2c, stepSequence[i][2]); 
     digitalWrite(m2d, stepSequence[i][3]); 
     delay(1);
    }
}

void nullTurn(){
  digitalWrite(m1a, 0);  
  digitalWrite(m1b, 0); 
  digitalWrite(m1c, 0); 
  digitalWrite(m1d, 0); 
  digitalWrite(m2a, 0);  
  digitalWrite(m2b, 0); 
  digitalWrite(m2c, 0); 
  digitalWrite(m2d, 0);
}

