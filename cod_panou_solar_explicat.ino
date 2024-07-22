#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//declarare ecran LCD

#include <BH1750.h>
BH1750 lightMeter;
//declarare senzor de intensitate lumina

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 7
//declarare senzor de umiditate si temperatura aer

#include <Servo.h>
Servo lr_servo; //declarare servo axa X
Servo ud_servo; //declarare servo axa Y

int lr_angle = 90; //declarare unghi initial servo axa X
int ud_angle = 10; //declarare unghi initial servo axa Y

int l_state = A0;
int r_state = A1;
int u_state = A2;
int d_state = A3;
//declarare pini voltaj servo

int buzzer = 6;  //declarare pin buzzer
int lr_servopin = 9; //declarare pin control servo axa X
int ud_servopin = 10; //declarare pin control servo axa Y 

int error = 15; //declarare eroare
int accuracy = 1; //declarare acuratete

int light; //declarare variabila intensitate lumina
int temperature; //declarare variabila temperatura
int humidity; //declarare variabila umiditate

void setup() {
  Serial.begin(9600); 
  Wire.begin();
  lightMeter.begin();
  //initializare senzor de intensitate lumina 

  lr_servo.attach(lr_servopin); //setare pin de control servo axa X
  ud_servo.attach(ud_servopin); //setare pin de control servo axa Y
  pinMode(l_state, INPUT);
  pinMode(r_state, INPUT);
  pinMode(u_state, INPUT);
  pinMode(d_state, INPUT);
  
  lcd.init();
  lcd.backlight();
  //initializare ecran LCD

  lr_servo.write(lr_angle);
  delay(1000);
  //setare unghi initial servo axa X
  
  ud_servo.write(ud_angle);
  delay(1000);
  //setare unghi initial servo axa Y
}

void loop() {
  servo();
  //setare unghiuri servouri
  
  Light();
  //citire intensitate lumina
  
  Dht();
  //citire umiditate si temperatura aer
  
  LCD();
  //afisare date pe ecran LCD
}

void servo(){
  int L = analogRead(l_state);
  int R = analogRead(r_state);
  int U = analogRead(u_state);
  int D = analogRead(d_state);
  //citire voltaj
 
  if (abs(L - R) > error && L >= R) 
  {
    //daca eroarea nu este in intervalul dorit si servoul este orientat spre dreapta
    
    lr_angle -= accuracy;
    //unghiul se ajusteaza
    
    if (lr_angle < 0) lr_angle = 0;
    //limitare unghi servo
    
    lr_servo.write(lr_angle);
    delay(10);
    //seteaza unghiul servoului
  }
  else if (abs(L - R) > error && L < R) 
  { 
    //daca eroarea nu este in intervalul dorit si servoul este orientat spre stanga
    
    lr_angle += accuracy;
    //unghiul se ajusteaza
    
    if (lr_angle > 180) lr_angle = 180;
    //limitare unghi servo
    
    lr_servo.write(lr_angle);
    delay(10);
    //seteaza unghiul servoului
  }
  else lr_servo.write(lr_angle); //altfel se seteaza unghiul servoului
  
  if (abs(U - D) > error && U >= D) 
  {
    //daca eroarea nu este in intervalul dorit si servoul este orientat spre jos
    
    ud_angle -= accuracy;
    //unghiul se ajusteaza
    
    if (ud_angle < 0) ud_angle = 0;
    //limitare unghi servo
    
    ud_servo.write(ud_angle);
    delay(10);
    //seteaza unghiul servoului
  }
  else if (abs(U - D) > error && U < D) 
  { 
    //daca eroarea nu este in intervalul dorit si servoul este orientat spre stanga
    
    ud_angle += accuracy;
    //unghiul se ajusteaza
    
    if (ud_angle > 180) ud_angle = 180;
    //limitare unghi servo
    
    ud_servo.write(ud_angle);
    delay(10);
    //seteaza unghiul servoului
  }
  else ud_servo.write(ud_angle); //altfel se seteaza unghiul servoului
}

void LCD() {
  char str1[5];
  char str2[2];
  char str3[2];
  dtostrf(light, -5, 0, str1);
  dtostrf(temperature, -2, 0, str2);
  dtostrf(humidity, -2, 0, str3);
  //afisarea intensitatii luminii, temperaturii si umiditatii aerului sub forma de siruri de caractere

  lcd.setCursor(0, 0);
  lcd.print("Light:");
  lcd.setCursor(6, 0);
  lcd.print(str1);
  lcd.setCursor(11, 0);
  lcd.print("lux");
  //afisare intensitate lumina
  
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.setCursor(2, 1);
  lcd.print("C");
  //afisare temperatura aer
  
  lcd.setCursor(5, 1);
  lcd.print(humidity);
  lcd.setCursor(7, 1);
  lcd.print("%");
  //afisare umiditate aer

  lcd.setCursor(11, 1);
  lcd.print("res:");
  lcd.setCursor(15, 1);
  lcd.print(accuracy);
  //afisare acuratete servouri
}

void Light(){
  light = lightMeter.readLightLevel();
  //citire intensitate lumina
}

void Dht(){
  temperature = DHT.temperature;
  //citire temperatura aer
  
  humidity = DHT.humidity;
  //citire umidiatte aer
}

void adjust_accuracy() {
  tone(buzzer, 800, 100);
  delay(10);
  //redare sunet prin buzzer
  
  if(accuracy < 5) accuracy++;
  else accuracy = 1;
  //modificare acuratete servouri
}
