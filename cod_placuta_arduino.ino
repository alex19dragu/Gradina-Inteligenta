//Cod Placuță Arduino


#include <DHT.h>
#define DHTPIN 12     
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//declarare senzor de umidititate si temperatura aer

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//declarare senzor de temperatura sol

const int AirValue0 = 520;
const int WaterValue0 = 220;
int soilvalue0 = 0;
int soilpercent0 = 0;
//parametrii zona 1

const int AirValue1 = 520;
const int WaterValue1 = 220;
int soilvalue1 = 0;
int soilpercent1 = 0;
//parametrii zona 2

const int AirValue2 = 520;
const int WaterValue2 = 220;
int soilvalue2 = 0;
int soilpercent2 = 0;
//parametrii zona 3

const int valva1 = 9;
const int valva2 = 11;
const int valva3 = 10;
//declarare valve

void setup() {
  
  Serial.begin(9600);
  
  pinMode(valva1, OUTPUT);
  pinMode(valva2, OUTPUT);
  pinMode(valva3, OUTPUT);
  
  dht.begin();
  //initializare valve si senzor de umiditate si temperatura aer
}

void loop() {
  
  soilvalue0 = analogRead(A0); //citire senzor de umiditate sol zona 1
  soilpercent0 = map(soilvalue0, AirValue0, WaterValue0, 0, 100); //transformarea datelor in intervalul 0-100
  if (soilpercent0 >= 100)
  {
    soilpercent0 = 100;
  }
  else if (soilpercent0 <= 0)
  {
    soilpercent0 = 0;
  }
  Serial.println("H%Zona1="); Serial.println(soilpercent0); //afisare umiditate zona 1
  delay(2000);

  if (soilpercent0 <= 60)
  {
    digitalWrite(valva1, HIGH);
    Serial.println("Valva1Pornit");
    //daca umiditatea zonei scade sub 60%, valva se deschide
  }
  else
  {
    digitalWrite(valva1, LOW);
    //altfel valva este inchisa
  }
  delay(2000);

  soilvalue1 = analogRead(A1); //citire senzor de umiditate sol zona 2
  soilpercent1 = map(soilvalue1, AirValue1, WaterValue1, 0, 100); //transformarea datelor in intervalul 0-100
  if (soilpercent1 >= 100)
  {
    soilpercent1 = 100;
  }
  else if (soilpercent1 <= 0)
  {
    soilpercent1 = 0;
  }
  Serial.println("H%Zona2="); Serial.println(soilpercent1); //afisare umiditate zona 2
  delay(2000);


  if (soilpercent1 <= 50)
  {
    digitalWrite(valva2, HIGH);
    Serial.println("Valva2Pornit");
    //daca umiditatea zonei scade sub 50%, valva se deschide
  }
  else
  {
    digitalWrite(valva2, LOW);
    //altfel valva este inchisa
  }
  delay(2000);


  soilvalue2 = analogRead(A2); //citire senzor de umiditate sol zona 3
  soilpercent2 = map(soilvalue2, AirValue2, WaterValue2, 0, 100); //transformarea datelor in intervalul 0-100
  if (soilpercent2 >= 100)
  {
    soilpercent2 = 100;
  }
  else if (soilpercent2 <= 0)
  {
    soilpercent2 = 0;
  }
  Serial.println("H%Zona3="); Serial.println(soilpercent2); //afisare umiditate zona 3
  delay(2000);

  if (soilpercent2 <= 40)
  {
    digitalWrite(valva3, HIGH);
    Serial.println("Valva3Pornit");
    //daca umiditatea zonei scade sub 40%, valva se deschide
  }
  else
  {
    digitalWrite(valva3, LOW);
    //altfel valva este inchisa
  }
  delay(2000);


  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //citire senzor de umiditate si temperatura aer
  
  Serial.println("HAer="); Serial.println(h); //afisare umiditate aer
  delay(2000);

  Serial.println("TAer="); Serial.println(t); //afisare temperatura aer
  delay(2000);


  sensors.requestTemperatures(); //citire senzor temperatura sol
  
  Serial.println("TSol="); Serial.println(sensors.getTempCByIndex(0)); //afisare temperatura sol
  delay(2000);
}



Cod Placuță Arduino


#include <DHT.h>
#define DHTPIN 12     
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//declarare senzor de umidititate si temperatura aer

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//declarare senzor de temperatura sol

const int AirValue0 = 520;
const int WaterValue0 = 220;
int soilvalue0 = 0;
int soilpercent0 = 0;
//parametrii zona 1

const int AirValue1 = 520;
const int WaterValue1 = 220;
int soilvalue1 = 0;
int soilpercent1 = 0;
//parametrii zona 2

const int AirValue2 = 520;
const int WaterValue2 = 220;
int soilvalue2 = 0;
int soilpercent2 = 0;
//parametrii zona 3

const int valva1 = 9;
const int valva2 = 11;
const int valva3 = 10;
//declarare valve

void setup() {
  
  Serial.begin(9600);
  
  pinMode(valva1, OUTPUT);
  pinMode(valva2, OUTPUT);
  pinMode(valva3, OUTPUT);
  
  dht.begin();
  //initializare valve si senzor de umiditate si temperatura aer
}

void loop() {
  
  soilvalue0 = analogRead(A0); //citire senzor de umiditate sol zona 1
  soilpercent0 = map(soilvalue0, AirValue0, WaterValue0, 0, 100); //transformarea datelor in intervalul 0-100
  if (soilpercent0 >= 100)
  {
    soilpercent0 = 100;
  }
  else if (soilpercent0 <= 0)
  {
    soilpercent0 = 0;
  }
  Serial.println("H%Zona1="); Serial.println(soilpercent0); //afisare umiditate zona 1
  delay(2000);

  if (soilpercent0 <= 60)
  {
    digitalWrite(valva1, HIGH);
    Serial.println("Valva1Pornit");
    //daca umiditatea zonei scade sub 60%, valva se deschide
  }
  else
  {
    digitalWrite(valva1, LOW);
    //altfel valva este inchisa
  }
  delay(2000);

  soilvalue1 = analogRead(A1); //citire senzor de umiditate sol zona 2
  soilpercent1 = map(soilvalue1, AirValue1, WaterValue1, 0, 100); //transformarea datelor in intervalul 0-100
  if (soilpercent1 >= 100)
  {
    soilpercent1 = 100;
  }
  else if (soilpercent1 <= 0)
  {
    soilpercent1 = 0;
  }
  Serial.println("H%Zona2="); Serial.println(soilpercent1); //afisare umiditate zona 2
  delay(2000);


  if (soilpercent1 <= 50)
  {
    digitalWrite(valva2, HIGH);
    Serial.println("Valva2Pornit");
    //daca umiditatea zonei scade sub 50%, valva se deschide
  }
  else
  {
    digitalWrite(valva2, LOW);
    //altfel valva este inchisa
  }
  delay(2000);


  soilvalue2 = analogRead(A2); //citire senzor de umiditate sol zona 3
  soilpercent2 = map(soilvalue2, AirValue2, WaterValue2, 0, 100); //transformarea datelor in intervalul 0-100
  if (soilpercent2 >= 100)
  {
    soilpercent2 = 100;
  }
  else if (soilpercent2 <= 0)
  {
    soilpercent2 = 0;
  }
  Serial.println("H%Zona3="); Serial.println(soilpercent2); //afisare umiditate zona 3
  delay(2000);

  if (soilpercent2 <= 40)
  {
    digitalWrite(valva3, HIGH);
    Serial.println("Valva3Pornit");
    //daca umiditatea zonei scade sub 40%, valva se deschide
  }
  else
  {
    digitalWrite(valva3, LOW);
    //altfel valva este inchisa
  }
  delay(2000);


  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //citire senzor de umiditate si temperatura aer
  
  Serial.println("HAer="); Serial.println(h); //afisare umiditate aer
  delay(2000);

  Serial.println("TAer="); Serial.println(t); //afisare temperatura aer
  delay(2000);


  sensors.requestTemperatures(); //citire senzor temperatura sol
  
  Serial.println("TSol="); Serial.println(sensors.getTempCByIndex(0)); //afisare temperatura sol
  delay(2000);
}
