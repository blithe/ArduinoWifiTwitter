#include <SPI.h> // needed in Arduino 0019 or later
#include <WiFi.h>
#include "twtr.h"

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter("YourToken");

char ssid[] = "YourNetwork"; //  your network SSID (name) 
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)

char msgLight[] = "I'm Arduino! Someone is shining a light on me...";
char msgDark[] = "I'm Arduino! It's so dark in here. Anyone have a flashlight?";

bool lights_on = false;

void setup()
{
  Serial.println("Connecting to network...");
  delay(1000);
  WiFi.begin(ssid, pass);
  // or you can use DHCP for automatic IP address configuration.
  // WiFi.begin(mac);
  delay(10000);
  Serial.println("...");  
  Serial.begin(9600);
}

void loop()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage);
  
  if(voltage > 2) {
    // Lighted
    if(!lights_on) {
      Serial.println("Shining...");
      lights_on = true;
      sendTweet(msgLight);      
    }
  } else {
    // Dark
    if(lights_on) {
      Serial.println("Dark...");
      lights_on = false;
      sendTweet(msgDark);
    }
  }
}

void sendTweet(char *msg)
{
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    // Specify &Serial to output received response to Serial.
    // If no output is required, you can just omit the argument, e.g.
    // int status = twitter.wait();
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}
