#define BLYNK_TEMPLATE_ID "TMPLPWAb0lyB"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "0F_nIUBiVHGTk0IonJ11oDS19ML8Lq4H"

#include<Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

//hardWare Specifics


//#include <DHT.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial(D1,D2);

char auth[] = BLYNK_AUTH_TOKEN;


// Your WiFi credentials.
char ssid[] =  "GradiaBotanica"; //  "WIFI NAME";
char pass[] =  "Botanica";     //  "WIFI PASSWORD"; // Set password to "" for open networks.


bool fetch_blynk_state = true;  //true or false
#define wifiLed   LED_BUILTIN   //D0int 
int wifiFlag = 0;




bool valva1state=0;

BlynkTimer timer;
//BlynkTimer timerdht;





BLYNK_CONNECTED() {
  // Request the latest state from the server
  if (fetch_blynk_state){
    
  }  
}

void checkBlynkStatus() { // called every 2 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    Serial.println("Blynk Not Connected");
    digitalWrite(wifiLed, HIGH);
  }
  if (isconnected == true) {
        
    if (!fetch_blynk_state){
    }
    
    wifiFlag = 0;
    digitalWrite(wifiLed, LOW);
    Serial.println("Blynk Connected");
  }
}

void setup()
{     
       // Debug console
      Serial.begin(115200);
      mySerial.begin(9600);

  // initialize ESP module
  
      
      pinMode(wifiLed, OUTPUT);
  

      Blynk.begin(auth, ssid, pass);
      // You can also specify server:
      //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
      //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

      //Setup a function to be called every second
      timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
      //timerdht.setInterval(1000L, sendSensor);
      delay(1000);
  
      if (!fetch_blynk_state){     
       }
}

void loop()
{
  Blynk.run();
  timer.run();
  //timerdht.run();
  String msg = mySerial.readStringUntil('\r');
  Blynk.virtualWrite(V8,msg);
  delay(2000);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
