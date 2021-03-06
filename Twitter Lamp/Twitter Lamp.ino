/*
    idIoTWare Twitter Lamp
    Attention: Please install all libraries from our Github Repository to enable this example to run.
    
    In this example we are using ESP8266-01 Wifi Module  and onboard WS2812 multicolor led.
    
    In this example we are using Blynk HTTP RESTful API and IFTTT.
    Blynk HTTP RESTful API allows to easily read and write values to/from Pins in Blynk apps and 
    Hardware (microcontrollers and microcomputers like Arduino, Raspberry Pi, ESP8266, Particle, etc.).
    Every PUT request will update Pin's state both in apps and on the hardware. Every GET request will 
    return current state/value on the given Pin. We also provide simplified API so you can do updates via GET requests.
    You can read on how to do it here //http://docs.blynkapi.apiary.io/#reference/0/get-pin-value/write-pin-value-via-get?console=1
    Use your Auth Token number in url to get data from server.
    
    We are also using a custom built Python webserver code that connects to Twitter every 75 seconds, and fetches the last top tweets,
	parses the text using a regular expression and finds which color hashtag has been added to the tweet. It finds out all unique 
	colors from the tweet, and then makes a webrequest to the Blynk HTTP Restful API, which in turn changes the LED color.
*/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include <idIoTwareShield.h>
#include <Wire.h>         // Require for I2C communication
idIoTwareShield fs;             // Instanciate CGShield instance

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8ae41dd66020477a85c1b23d63e22203";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CuriosityGym-BCK";
char pass[] = "XXXXXXXX";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial debugSerial(10, 9); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void setup()
    {
      // Set console baud rate
      debugSerial.begin(9600);
      delay(10);
      // Set ESP8266 baud rate
      EspSerial.begin(ESP8266_BAUD);
      delay(10);

      Blynk.begin(auth, wifi, ssid, pass);
    }

//http://blynk-cloud.com/yourAPIkey/update/V0?value=250?pin=V0&value=0&pin=V0&value=0

//create virtual pin 1 and read value from that pin
BLYNK_WRITE(V0)
           {
             int red = param[0].asInt();
             int green = param[1].asInt();
             int blue = param[2].asInt();
             color(red,green,blue); //Set color received from Blynk API 
           }

void loop()
{
  Blynk.run();
}

