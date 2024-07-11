#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//declarare ecran LCD

#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE DHT11
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

  lcd.init();
  lcd.backlight();
  //initializare ecran LCD

  lcd.print("Smart Garden");
  lcd.setCursor(0, 1);
  lcd.print("Alex Dragu");
  delay(3000);
  lcd.clear();
  //afisarea unui mesaj la pornire
}

void loop() {
  lcd.clear();
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
  Serial.println("H%Zona1="); Serial.println(soilpercent0);
  lcd.setCursor(0, 1);
  lcd.print("H%Zona1=");
  lcd.setCursor(8, 1);
  lcd.print(soilpercent0); //afisare umiditate zona 1
  delay(3000);
  lcd.clear();

  if (soilpercent0 <= 60)
  {
    digitalWrite(valva1, HIGH);
    Serial.println("Valva1Pornit");
    lcd.setCursor(0, 1);
    lcd.print("Valva1Pornit");
    //daca umiditatea zonei scade sub 60%, valva se deschide
  }
  else
  {
    digitalWrite(valva1, LOW);
    //altfel valva este inchisa
  }
  delay(3000);
  lcd.clear();

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
  Serial.println("H%Zona2="); Serial.println(soilpercent1);
  lcd.setCursor(0, 1);
  lcd.print("H%Zona2=");
  lcd.setCursor(8, 1);
  lcd.print(soilpercent1); //afisare umiditate zona 2
  delay(3000);
  lcd.clear();

  if (soilpercent1 <= 50)
  {
    digitalWrite(valva2,HIGH);
    Serial.println("Valva2Pornit");
    lcd.setCursor(0, 1);
    lcd.print("Valva2Pornit");
    //daca umiditatea zonei scade sub 50%, valva se deschide
  }
  else
  {
    digitalWrite(valva2,LOW);
    //altfel valva este inchisa
  }
  delay(3000);
  lcd.clear();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //citire senzor de umiditate si temperatura aer
  
  Serial.println("HAer="); Serial.println(h);
  lcd.setCursor(0, 1);
  lcd.print("HAer=");
  lcd.setCursor(5, 1);
  lcd.print(h);
  delay(3000);
  lcd.clear();
  //afisare umiditate aer

  if (h > 75) {
    digitalWrite(valva3, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Valva3Pornit");
    //daca umiditatea aeruui e mai mare decat 75%, un ventilator se porneste  
  }
  else digitalWrite(valva3, LOW); //altfel se inchide
  delay(3000);
  lcd.clear();

  Serial.println("TAer="); Serial.println(t);
  lcd.setCursor(0, 1);
  lcd.print("TAer=");
  lcd.setCursor(5, 1);
  lcd.print(t);
  delay(3000);
  lcd.clear();
  //afisare temperatura aer

  sensors.requestTemperatures();
  Serial.println("TSol="); Serial.println(sensors.getTempCByIndex(0));
  lcd.setCursor(0, 1);
  lcd.print("TSol=");
  lcd.setCursor(5, 1);
  lcd.print(sensors.getTempCByIndex(0));
  delay(3000);
  lcd.clear();
  //afisare temperatura sol
}
