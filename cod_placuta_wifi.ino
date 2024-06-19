//Cod Placuță Esp8266


#define BLYNK_TEMPLATE_ID "xxxxx"
#define BLYNK_DEVICE_NAME "Gradina Inteligenta"
#define BLYNK_AUTH_TOKEN "xxxxx"
//declarare nume device, token de autentificare si id-ul template-ului

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

BlynkTimer timer;
//declarare unui timer cu ajutorul caruia verificam daca serverul Blynk este conectat

void checkBlynkStatus() { 

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
