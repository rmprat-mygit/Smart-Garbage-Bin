#include <Ultrasonic.h>
//#include <ESP8266WiFi.h>

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
//Ultrasonic ultrasonic(12, 13);
//int distance;
//ultrasonic sensor pm
const int trigPin = 12;
const int echoPin = 13;

float duration, distance;

//methane sensor pm
int sensorPin=A0;
int sensorData;


//#include <LiquidCrystal_I2C.h>    //If you don't have the LiquidCrystal_I2C library, download it and install it
//LiquidCrystal_I2C lcd(0x27,16,2);
float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(9,10);//tx,rx(9,10)
SoftwareSerial gsmm(7,8);//tx,rx
TinyGPSPlus gps;// create gps object


void setup()
{

//digitalWrite(2,LOW);
//digitalWrite(3,HIGH);

//ultrasonic pin configuration
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
//////////////////////////used level///////////////////////////////////////////////

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
delay(100);


//////////////////////////methane level///////////////////////////////////////////////

  //methane sensor pin config
    pinMode(sensorPin,INPUT);

  sensorData = analogRead(sensorPin);       
  Serial.print("Sensor Data:");
  Serial.print(sensorData);
  Serial.print("\n");
  
  delay(100);
////////////////////////////////////////////////////////////////////////
Serial.begin(9600);


  //lcd.init();
  //lcd.backlight();// connect serial
//lcd.begin(16, 2);
gpsSerial.begin(9600);
gpsSerial.listen();
 textgps();
 gsmm.begin(9600);
  gsmm.print("\r");
  delay(1000);                  
 // gsmm.print("AT+CMGF=1\r"); 
 gsmm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode   
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
 gsmm.print("AT+CMGS=\"+94719856450\"\r");    
  //gsmm.println("AT+CMGS=\"+94713589223\"\r"); // Replace x with mobile number

  delay(1000);
  //The text of the message to be sent.
  //gsmm.print(lattitude,longitude);
// gsmm.print(lattitude); 
//  gsmm.print(longitude); 
gsmm.print("distance:");
gsmm.print(distance);
gsmm.print("\n");
gsmm.print("sensorData:");
gsmm.print(sensorData);
gsmm.print("\n");
gsmm.print(" BIN NO 01 : FULL\n");
gsmm.print(" Please get the location\n");
  gsmm.print("https://www.google.com/maps/place/");
 
      gsmm.print(lattitude, 6);
      gsmm.print(",");
      gsmm.print(longitude, 6);
      gsmm.print(",");
      
  delay(1000);
  gsmm.write(0x1A);
  
  delay(1000); 
//connect gps sensor


}
void loop(){
    
//ultrasonic();

//delay(1000);


}

void textgps()
{

    while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
      break;
      }
  
   
  
}

 Serial.print("LATTITUDE="); Serial.println(lattitude,6);
 Serial.print("LONGITUDE="); Serial.println(longitude,6);
 
 //lcd.print("LAT ");lcd.print(lattitude,6);
 //lcd.setCursor(0, 1);
 //lcd.print("LONG ");lcd.print(longitude,6);
 delay(1000);
// lcd.clear();
}

//ultrasonic sensor 
void ultrasonic()
 {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
delay(100);
}

//methane sensor function
void methane()
{
  sensorData = analogRead(sensorPin);       
  Serial.print("Sensor Data:");
  delay(100);
}