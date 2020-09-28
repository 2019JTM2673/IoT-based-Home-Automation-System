/**********************************************************ASSIGNMENT 5 ****************************************************************************/

#define BLYNK_PRINT Serial
#include "esp_wpa2.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TimeLib.h>
#include <WidgetRTC.h>


int counter, value;

char auth[] = "kf89zRc-ck21LUK80wkcLGSt9ue7aDYE";    // apply token

// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid = "IITD_WIFI";
const char* password =  "";
 #define EAP_IDENTITY "jtm192673"
 #define EAP_PASSWORD "Ayushjtm@2673"



int pin1 = 26;
int pin2 =33;
float p1;
float p2;

float money;
float moneyhr, totalmoney, amount, totabill, current_time, last_time;


float totalpower=0;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 10; 

int temp=0;
const int tempre = 4;
int threshold;
int pinvalue;

 WidgetLED led1(V3);
 WidgetLED led2(V4);




#define LED_PIN 2

BlynkTimer timer;
WidgetRTC rtc;
int t1;

WiFiClientSecure client;


///////////////// Get data /////////


//BLYNK_WRITE(V1)
//{
//  value = param.asInt(); // assigning incoming value from pin V1 to a variable
//  // You can also use:
//  // String i = param.asStr();
//  // double d = param.asDouble();
//  Serial.print("V1 Slider value is: ");
//  Serial.println(value);
//  ledcWrite(pin,value);
//  digitalWrite(LED_PIN, value);
//  
//  
//  
//}

/////////////////////////////////////



////////////////////////////////////////// send data to arduino ///////////////////////

void myTimerEvent()
{
   money = money + totalpower;
   moneyhr= money/3600;
  totalmoney= moneyhr*100;
}








/////////////////////////////////// Stroboscope   ///////////////////////////////////////////////


//////////////// led blink fuction ///////
//void ledBlynk()
//{
//  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
//}

/////////////////////////////////////////////////////////




//BLYNK_WRITE(V1)
//{
//  if (param.asInt()) {
//    timer.enable(t1);
//  } 
//  else {
//    timer.disable(t1);
//    digitalWrite(LED_PIN, LOW);
//  }
//}


//BLYNK_WRITE(V2)
//{
//  long interval = param.asLong();
//  boolean wasEnabled = timer.isEnabled(t1);
//  timer.deleteTimer(t1);
//  t1 = timer.setInterval(interval, ledBlynk);
//  if (!wasEnabled) {
//    timer.disable(t1);
//  }
//}
////////////////////////////////////////////////////////////////////////////////////////





BLYNK_WRITE(V1)  // Button Widget on V1 to activate LED
{
  int ACTION = param.asInt();      // it is used to get input from 
  if (ACTION == 1) {
//    Blynk.email("geetaraj1510@gmail.com", "esp32", "My Blynk project is online.");
    Serial.println("Button1 is pressed."); 
//    Serial.println("keep move");
    digitalWrite(pin1, ACTION);
    digitalWrite(V3, HIGH);
//    Serial.print("Got a value: ");
//    Serial.println(param.asStr());   // used for timer 
    Serial.println(ACTION);
    Serial.println("led1 is on");
   
    if(digitalRead(pin1)==HIGH)
    {
    
     led1.on();
     p1 = float(random(9,11));
     Serial.println("power of led1:");
     Serial.println(p1);
     

    }

//    else
//    {
//      led1.off();
//    }
    
  }  
  if(ACTION ==0)
  {
    p1 = 0;
    Serial.println("button1 is off");
    Serial.println(ACTION);
    Serial.println("led1 is off");
    digitalWrite(pin1, ACTION);

    if(digitalRead(pin1)==LOW)
    {
      
    led1.off();
    }
}
   totalpower= p1+p2;
   Serial.println("total power of applicances:");
   Serial.println(totalpower);
   Blynk.virtualWrite(V5, totalpower); 
   last_time= current_time;
   current_time= millis();
   amount= totalpower*((current_time -last_time)/3600000.0);
   totabill= amount*100;
   Serial.println("totalbill is:");
   Serial.println(totabill);
//   Serial.println(myTimerEvent(totalpower)) ;
   

}


BLYNK_WRITE(V2)  // Button Widget on V1 to activate LED
{
  int ACTION = param.asInt();      // it is used to get input from 
  if (ACTION == 1) {
//    Blynk.email("geetaraj1510@gmail.com", "esp32", "My Blynk project is online.");
    Serial.println("Button2 is pressed."); 
//    Serial.println("keep move");
    digitalWrite(pin2, ACTION);
    digitalWrite(V4, HIGH);
//    Serial.print("Got a value: ");
//    Serial.println(param.asStr());   // used for timer 
    Serial.println(ACTION);
    Serial.println("led2 is on");
    

    if(digitalRead(pin2)==HIGH)
    {
     WidgetLED led2(V4); //register to virtual pin 1
//   
    led2.on();
    Serial.println("power of led2:");
    p2= float(random(19,21));
    Serial.println(p2);

      
      }

 }  
  
  if(ACTION ==0)
  { p2=0;
    Serial.println("button2 is off");
    Serial.println(ACTION);
    Serial.println("led1 is off");
    digitalWrite(pin2, ACTION);

    if(digitalRead(pin2)==LOW)
    {
       WidgetLED led2(V4);
    led2.off();

      }
   }

   totalpower= p1+p2;
   Serial.println("total power of applicances:");
   Serial.println(totalpower);
   Blynk.virtualWrite(V5, totalpower); 
   last_time= current_time;
   current_time= millis();
   amount= totalpower*((current_time -last_time)/3600000.0);
   totabill= amount*100;
   Serial.println("totalbill is:");
   Serial.println(totabill); 
   

   
}
//////////////////////////////*************Appliances end **********************/////////////////////////


    







//BLYNK_WRITE(V5)
//{
//
//  int value= param.asInt();
//  Serial.println(param.asStr());   // used for timer upto that led would glow
//  Serial.println(value);
//  digitalWrite(pin, value);
//  
// }


/////////////////////////////////// Zoystick //////////////////

//BLYNK_WRITE(V2) {
//  int x = param[0].asInt();
//  int y = param[1].asInt();
//
//  // Do something with x and y
//  Serial.print("X = ");         // recieve x and y cordinates  from joystick
//  Serial.print(x);
//  Serial.print("; Y = ");
//  Serial.println(y);
//
//  if(x==0)
//  {
//    Serial.println("left side");
//    digitalWrite(pin, HIGH);
//     
//  }
//
//  else if (x==1023)
//  {
//
//    Serial.println("right side");
//    digitalWrite(pin2, HIGH);
//}
//  
//  else
//  {
//    digitalWrite(pin, LOW);
//    digitalWrite(pin2, LOW);
//  }
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////






  
//void clockDisplay()
//{
//  // You can call hour(), minute(), ... at any time
//  // Please see Time library examples for details
//
//  String currentTime = String(hour()) + ":" + minute() + ":" + second();
//  String currentDate = String(day()) + " " + month() + " " + year();
//  Serial.print("Current time: ");
//  Serial.print(currentTime);
//  Serial.print(" ");
//  Serial.print(currentDate);
//  Serial.println();
//
//  // Send time to the App
//  Blynk.virtualWrite(V1, currentTime);    // to display output
//  // Send date to the App
//  Blynk.virtualWrite(V2, currentDate);
//}






void emailOnButtonPress()
{
  // * WARNING: You are limited to send ONLY ONE E-MAIL PER 15 SECONDS! *

  // Let's send an e-mail when you press the button
  // connected to digital pin 2 on your Arduino

  int isButtonPressed = !digitalRead(V1); // Invert state, since button is "Active LOW"

  if (isButtonPressed) // You can write any condition to trigger e-mail sending
  {
    Serial.println("Button is pressed."); // This can be seen in the Serial Monitor
    Blynk.email("geetaraj1510@gmail.com", "esp32", "You just pushed the button...");

    // Or, if you want to use the email specified in the App (like for App Export):
    //Blynk.email("Subject: Button Logger", "You just pushed the button...");
  }
}


//BLYNK_READ(V6) //Blynk app has something on V5
//{  temp= touchRead(tempre);
//    Serial.println("temperature is:");
//    Serial.println(temp);
//  
//  Blynk.virtualWrite(V6, temp); //sending to Blynk
//  
//  if (temp <= 5 ){
//    Blynk.email("geetaraj1510@gmail.com","Thersold_tem","temprature is low");
//    return;
//    }
//}

BLYNK_WRITE(V5)
{
  pinvalue = param.asInt(); 
  Serial.println("temperature is:");
   Serial.println(temp);
  
  
  Serial.println(pinvalue);
  if (temp < pinvalue) 
  {
    Blynk.email("geetraj1510@gmail.com", "Subject: Temperature warning", "Alert. Temperature is increasing");
  }
}







void setup() { 

  // Begin synchronizing time
  rtc.begin();
//  timer.setInterval(10000L, clockDisplay); 


  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
//  pinMode(2, OUTPUT);
  pinMode( V3, INPUT);
  pinMode( V4, INPUT);
  pinMode(LED_PIN, OUTPUT);

 timer.setInterval(1000L, myTimerEvent);

 
  
  ////////////////////////////////////////////////////////////////////////
//  t1 = timer.setInterval(500L, ledBlynk);    ///  delay for 
//  timer.disable(t1);
  ///////////////////////////////////////////////////


 
  Serial.begin(115200);
  delay(10);
  Serial.println();
  
 
  
  ////////////   connection of network //////////////////////////////////////////////////////
  
  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
  esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
  WiFi.begin(ssid); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      ESP.restart();
    }
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  



  Serial.println("WiFi connected");
  Serial.println("IP address set: "); 
  Serial.println(WiFi.localIP()); //print LAN IP

  
  Blynk.begin("kf89zRc-ck21LUK80wkcLGSt9ue7aDYE", ssid, EAP_PASSWORD);
  Blynk.email("geetaraj1510@gmail.com", "esp32", "My Blynk project is online.");


  ////////////////////////display temp/////////////////////////

    
//    Blynk.virtualWrite(V5, temp);  
   
  
}

void loop(){
    Blynk.run();
    
    timer.run();
    temp= touchRead(tempre);
     Blynk.virtualWrite(V3, temp); 

    
}
