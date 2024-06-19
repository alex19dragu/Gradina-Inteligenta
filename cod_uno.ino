
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 13

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

const int AirValue0 = 520;   //you need to replace this value with Value_1
const int WaterValue0 = 220;
int soilvalue0 = 0;
int soilpercent0 = 0;
const int AirValue1 = 520;   //you need to replace this value with Value_1
const int WaterValue1 = 220;
int soilvalue1 = 0;
int soilpercent1 = 0;
const int AirValue2 = 520;   //you need to replace this value with Value_1
const int WaterValue2 = 220;
int soilvalue2 = 0;
int soilpercent2 = 0;

const int valva1 = 9;
const int valva2 = 11;
const int valva3 = 10;

//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(valva1,OUTPUT);
  pinMode(valva2,OUTPUT);
  pinMode(valva3,OUTPUT);
  dht.begin();
  
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  
  lcd.print("Smart Garden");
  lcd.setCursor(0,1);
  lcd.print("Alex Dragu");
  delay(3000);
  lcd.clear();
}

void loop() {
  soilvalue0= analogRead(A0);
  soilpercent0 = map(soilvalue0, AirValue0, WaterValue0, 0, 100);
  if(soilpercent0 >= 100)
{
  soilpercent0=100;
}
else if(soilpercent0 <=0)
{
  soilpercent0=0;
}
  Serial.println("H%Zona1=");Serial.println(soilpercent0);
  lcd.setCursor(0,1);
  lcd.print("H%Zona1=");
  lcd.setCursor(8,1);
  lcd.print(soilpercent0);
  delay(3000);
  lcd.clear();

  if(soilpercent0<=60)
  {
    digitalWrite(valva1,HIGH);
    Serial.println("Valva1Pornit");
    lcd.setCursor(0,1);
    lcd.print("Valva1Pornit");
  }
  else
  {
    digitalWrite(valva1,LOW);   
  }
  delay(3000);
  lcd.clear();
  
  soilvalue1= analogRead(A1);
  soilpercent1 = map(soilvalue1, AirValue1, WaterValue1, 0, 100);
  if(soilpercent1 >= 100)
{
  soilpercent1=100;
}
else if(soilpercent1 <=0)
{
  soilpercent1=0;
}
  Serial.println("H%Zona2=");Serial.println(soilpercent1);
  lcd.setCursor(0,1);
  lcd.print("H%Zona2=");
  lcd.setCursor(8,1);
  lcd.print(soilpercent1);
  delay(3000);
  lcd.clear();

  if(soilpercent1<=50)
  {
    //digitalWrite(valva2,HIGH);
    Serial.println("Valva2Pornit");
    lcd.setCursor(0,1);
    lcd.print("Valva2Pornit");
  }
  else
  {
    //digitalWrite(valva2,LOW);   
  }
  delay(3000);
  lcd.clear();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("HAer=");Serial.println(h);
  lcd.setCursor(0,1);
  lcd.print("HAer=");
  lcd.setCursor(5,1);
  lcd.print(h);
  delay(3000);
  lcd.clear();

  if(h>75) {digitalWrite(valva3,HIGH);
  lcd.setCursor(0,1);
  lcd.print("Valva3Pornit");
  }
  else digitalWrite(valva3,LOW);
  delay(3000);
  lcd.clear();
  
  Serial.println("TAer=");Serial.println(t);
  lcd.setCursor(0,1);
  lcd.print("TAer=");
  lcd.setCursor(5,1);
  lcd.print(t);
  delay(3000);
  lcd.clear();


  sensors.requestTemperatures();
  Serial.println("TSol=");Serial.println(sensors.getTempCByIndex(0));
  lcd.setCursor(0,1);
  lcd.print("TSol=");
  lcd.setCursor(5,1);
  lcd.print(sensors.getTempCByIndex(0));
  delay(3000);
  lcd.clear();
}
