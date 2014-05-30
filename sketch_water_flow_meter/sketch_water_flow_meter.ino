/*
  Water flow meter
 
 This sketch obtains input from a water flow meter and pushes data 
 to dweet.io through a web client using an Arduino Wiznet Ethernet shield. 

 */



#include <SPI.h>
#include <Ethernet.h>

volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;                               
int hallsensor = 2;    //The pin location of the sensor

void rpm ()     //This is the function that the interupt calls 
{ 
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
} 


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(173,194,33,104); // Google

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
 pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
 Serial.begin(9600); //This is the setup function where the serial port is initialised,
 attachInterrupt(2, rpm, RISING);
  // Open serial communications and wait for port to open:
 //Serial.begin(9600);
 while (!Serial) {
  ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

}

void loop()
{
  NbTopsFan = 0;      //Set NbTops to 0 ready for calculations
  delay (1000);      //Wait 1 second
  Calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 
  Serial.print (Calc, DEC); //Prints the number calculated above
  Serial.print (" L/hour\r\n"); //Prints "L/hour" and returns a  new line
  
  //int i=0;
  // if you get a connection, report back via serial:
  if (client.connect("dweet.io", 80)) {
      Serial.println("connected");
    // Make a HTTP request:
      client.print("GET /dweet/for/UciUbicompSensor1?data=");
      client.print(Calc);
      client.println(" HTTP/1.1");
      client.println("HOST: dweet.io");
      client.println("Connection: close");
      client.println(); 
      client.stop();
    }
  
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

