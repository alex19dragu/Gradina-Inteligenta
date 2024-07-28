#define BLYNK_TEMPLATE_ID "xxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxx"
#define BLYNK_AUTH_TOKEN "xxxxx"
//declarare nume device, token de autentificare si id-ul template-ului

#include<Blynk.h>
#define BLYNK_PRINT Serial
//declarare canal de comunicare catre Blynk

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(D1,D2);
//declarare placuta Esp8266

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] =  "xxxxx";
char pass[] =  "xxxxx";
//declarare token de autentificare, numele retelei Wi-Fi si parola acesteia

#define wifiLed   LED_BUILTIN
//declarare led de pe placuta Wi-Fi

bool stareValva = 0;
bool stareFan1 = 0;
bool stareFan2 = 0;
//declarare stari valva si ventilator

#define pinValvaVirtual V19
#define pinFanVirtual1 V29
#define pinFanVirtual2 V7
//declarare pini virtuali valva si ventilator

#define pinValvaEsp D3
#define pinFanEsp1 D4
#define pinFanEsp2 D5
//declarare pini digitali valva si ventilator

BlynkTimer timer;
//declarare unui timer cu ajutorul caruia verificam daca serverul Blynk este conectat

BLYNK_WRITE(pinValvaVirtual)
{      
  stareValva = param.asInt();
  digitalWrite(pinValvaEsp, stareValva);    
  //schimbare stare valva
}

BLYNK_WRITE(pinFanVirtual1)
{      
  stareFan1 = param.asInt();
  digitalWrite(pinFanEsp1, stareFan1);    
  //schimbare stare pin 1 ventilator
}

BLYNK_WRITE(pinFanVirtual2)
{      
  stareFan2 = param.asInt();
  digitalWrite(pinFanEsp2, stareFan2);
  //schimbare stare pin 2 ventilator
}

void checkBlynkStatus() 
{
  //verificam daca serverul Blynk este conectat
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    Serial.println("Blynk Not Connected");
    digitalWrite(wifiLed, HIGH);
    //daca nu este conectat, ledul de pe placuta Wi-Fi se aprinde
  }
  if (isconnected == true) {
    digitalWrite(wifiLed, LOW);
    Serial.println("Blynk Connected");
    //altfel se stinge
  }
}

void setup()
{     
  Serial.begin(115200);
  mySerial.begin(9600);
  //initializare placuta Esp8266
           
  pinMode(wifiLed, OUTPUT);
  //initializare led

  pinMode(pinValvaEsp, OUTPUT);
  pinMode(pinFanEsp1, OUTPUT);
  pinMode(pinFanEsp2, OUTPUT);    
  //initializare pini valva si ventilator
  
  Blynk.begin(auth, ssid, pass);
  //initializare server Blynk

  timer.setInterval(2000L, checkBlynkStatus); 
  //la fiecare 2 secunde verificam daca serverul este conectat
      
  delay(1000);
}

void loop()
{
  Blynk.run();
  //pornire server Blynk
  
  timer.run();
  //pornire timer
  
  String msg = mySerial.readStringUntil('\r'); //citire date
  Blynk.virtualWrite(V8,msg); //afisare date
  delay(2000);
}
