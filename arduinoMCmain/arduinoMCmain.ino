/*  Arduino Motor Controller Firmware */
#include <math.h>
//#include <LiquidCrystal.h>
int SensorA;
int SensorB;
int SensorC;

int led_pinAlto = 10; 
int led_pinBajo = 11;
int led_pinAlto2 = 6; 
int led_pinBajo2 = 9;
int led_pinAlto3 = 3; 
int led_pinBajo3 = 5;
int HA = A1;
int HB = A2; 
int HC = A3;
int pot_pin = A4;
int output;
int led_value;

void setup() {
  pinMode(led_pinAlto, OUTPUT);
  pinMode(led_pinBajo, OUTPUT);
  pinMode(led_pinAlto2, OUTPUT);
  pinMode(led_pinBajo2, OUTPUT);
  pinMode(led_pinAlto3, OUTPUT);
  pinMode(led_pinBajo3, OUTPUT);
  pinMode(HA, INPUT_PULLUP);
  pinMode(HB, INPUT_PULLUP);
  pinMode(HC, INPUT_PULLUP);
  // Serial.begin(9600);
}


void loop() {
  //Reading from potentiometer
  output = analogRead(pot_pin);

  //Mapping the Values between 0 to 255 because we can give output
  //from 0 -255 using the analogwrite funtion
  led_value = map(output, 0, 1023, 0, 255);
  SensorA = analogRead(HA);
  SensorB = analogRead(HB);
  SensorC = analogRead(HC);
  //  Serial.print("***SensorA***");
  //  Serial.println(SensorA);
  //  Serial.print("***SensorB***");
  //  Serial.println(SensorB);
  //  Serial.print("***SensorC***");
  //  Serial.println(SensorC);
  
 
//  int valorAHigh = ((SensorA&(!SensorB)&(!SensorC)) | (SensorA&SensorB&(!SensorC)));
//  int valorALow = (((!SensorA)&SensorB&SensorC) | ((!SensorA)&(!SensorB)&SensorC));
 
//  Serial.print("***Valor A high***");
//  Serial.println(valorAHigh);
//  Serial.print("***Valor A Low***");
//  Serial.println(valorALow);  
 
//  int valorBHigh = (((!SensorA)&SensorB&(!SensorC)) | ((!SensorA)&SensorB&SensorC));
//  int valorBLow = ((SensorA&(!SensorB)&SensorC) | (SensorA&(!SensorB)&(!SensorC)));  // if B LOW equation 
 
//  Serial.print("***Valor B high***");
//  Serial.println(valorBHigh);
//  Serial.print("***Valor B Low***");
//  Serial.println(valorBLow);  
 
//  int valorCHigh = ((SensorA&(!SensorB)&SensorC) | ((!SensorA)&(!SensorB)&SensorC));
//  int valorCLow = (SensorA&SensorB&(!SensorC)) | ((!SensorA)&SensorB&(!SensorC));

//  Serial.print("***Valor C high***");
//  Serial.println(valorCHigh);
//  Serial.print("***Valor C Low***");
//  Serial.println(valorCLow);  
  
  if(digitalRead(HA)==HIGH && digitalRead(HB) ==LOW && digitalRead(HC) == HIGH){
  //Imprimir
    int a = digitalRead(HA);
  int b = digitalRead(HB);
  int c = digitalRead(HC);
  

  //Paso 1
  //Secuencia dejar parte alta de fase A en 0  
  analogWrite(led_pinBajo, 0);
  analogWrite(led_pinAlto, 0);
  //prender parte baja de fase B
  analogWrite(led_pinAlto2, 0);
  analogWrite(led_pinBajo2, led_value);
  //y parte alta de fase C
  analogWrite(led_pinAlto3, led_value);
  analogWrite(led_pinBajo3, 0);
  delay(10);
  }
  
  if(digitalRead(HA)==HIGH && digitalRead(HB) ==LOW && digitalRead(HC) == LOW){
  //Imprimir
    int a = digitalRead(HA);
  int b = digitalRead(HB);
  int c = digitalRead(HC);
  

  //Paso 2
  //Parte Alta Fase A
  analogWrite(led_pinBajo, 0);
  analogWrite(led_pinAlto, led_value);
  // Parte baja de Fase B
  analogWrite(led_pinBajo2, led_value);
  analogWrite(led_pinAlto2, 0);
  // Parte en 0 de Fase C
  analogWrite(led_pinBajo3, 0);
  analogWrite(led_pinAlto3, 0); 
  delay(10);
  }
  
  if(digitalRead(HA)==HIGH && digitalRead(HB) ==HIGH && digitalRead(HC) == LOW){
  //Imprimir
    int a = digitalRead(HA);
  int b = digitalRead(HB);
  int c = digitalRead(HC);
  

  //Paso 3
  //Parte Alta Fase A
  analogWrite(led_pinBajo, 0);
  analogWrite(led_pinAlto, led_value);
  // Parte en 0 de Fase B
  analogWrite(led_pinBajo2, 0);
  analogWrite(led_pinAlto2, 0);
  // Parte baja de Fase C
  analogWrite(led_pinBajo3, led_value);
  analogWrite(led_pinAlto3, 0); 
  delay(10);
  }
  
  if(digitalRead(HA)==LOW && digitalRead(HB) ==HIGH && digitalRead(HC) == LOW){
  //Imprimir
    int a = digitalRead(HA);
  int b = digitalRead(HB);
  int c = digitalRead(HC);
  

  //Paso 4
  //Parte en 0 Fase A
  analogWrite(led_pinBajo, 0);
  analogWrite(led_pinAlto, 0);
  // Parte alta de Fase B
  analogWrite(led_pinBajo2, 0);
  analogWrite(led_pinAlto2, led_value);
  // Parte baja de Fase C
  analogWrite(led_pinBajo3, led_value);
  analogWrite(led_pinAlto3, 0); 
  delay(10);
  }
  
  if(digitalRead(HA)==LOW && digitalRead(HB) ==HIGH && digitalRead(HC) == HIGH){
  //Imprimir
    int a = digitalRead(HA);
  int b = digitalRead(HB);
  int c = digitalRead(HC);

  //Paso 5
  //Parte baja Fase A
  analogWrite(led_pinBajo, led_value);
  analogWrite(led_pinAlto, 0);
  // Parte alta de Fase B
  analogWrite(led_pinBajo2, 0);
  analogWrite(led_pinAlto2, led_value);
  // Parte en 0 de Fase C
  analogWrite(led_pinBajo3, 0);
  analogWrite(led_pinAlto3, 0); 
  delay(10);
  }
  
  if(digitalRead(HA)==LOW && digitalRead(HB) ==LOW && digitalRead(HC) == HIGH){
  //Imprimir
    int a = digitalRead(HA);
  int b = digitalRead(HB);
  int c = digitalRead(HC);
  

  //Paso 6
  //Parte baja Fase A
  analogWrite(led_pinBajo, led_value);
  analogWrite(led_pinAlto, 0);
  // Parte en 0 de Fase B
  analogWrite(led_pinBajo2, 0);
  analogWrite(led_pinAlto2, 0);
  // Parte alta de Fase C
  analogWrite(led_pinBajo3, 0);
  analogWrite(led_pinAlto3, led_value); 
  delay(10);
  }
  
}

