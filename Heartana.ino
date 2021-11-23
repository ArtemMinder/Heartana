const int MOOVING_TRESHOLD = 150;
const int UNAVAILABLE = 0;
const int SITTING = 5;
const int BACK = 1;
const int STOMACK = 2;
const int LEFT = 4;
const int RIGHT = 3;
const int UPSIDE = 6;
int LastTime=0;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;


#include "HX711.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <ADXL345.h>
#include <Adafruit_ADXL345_U.h>

/////////////////////////////////////////////////////////////

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
#define UpperThreshold 550
#define LowerThreshold 500
#define DOUT A1
#define CLK  A2
HX711 scale;
ADXL345 adxl;

const int chipSelect = 4;
float calibration_factor = -7050;

void setup() {
 
  axel();
  pinMode(9, INPUT); // Setup for leads off detection LO +
  pinMode(10, INPUT); // Setup for leads off detection LO -

  Serial.begin(9600);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();  
  while (!Serial) {
    ; 
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

   File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println("");
  dataFile.close();

}

void loop() {
  int pos = 0;
  scale.set_scale(calibration_factor); 


 File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    
    dataFile.println(heart());
    Serial.println(heart());    

    dataFile.println(test());
    Serial.println(test());
    
    dataFile.println(scale.get_units(), 1);
    Serial.println(scale.get_units(), 1);
    
    dataFile.close();
  }
  else {
    
    Serial.println("error opening datalog.txt");
  }
  delay(200);

}

void axel()
{
 adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1); 
  
}

int moving(){
  const int SIZE = 80;
  int arr [SIZE];
  int all = 0;
  int result;
  int a = 0;
  int middle;
  for (int i = 0; i < SIZE; i++){
    sensors_event_t event; 
    accel.getEvent(&event);
    arr[i] = event.acceleration.z;
    a += event.acceleration.z;
    delayMicroseconds(10);
   }
  middle = a / SIZE;
  for (int j = 0; j < SIZE; j++){
    all += (arr[j] - middle )*(arr[j] - middle );
  }
  sqrt(all);
  return all;
  }

  int test(){
    
  int x,y,z;  
  adxl.readXYZ(&x, &y, &z);
  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
  int pos{};
  int k =0;

          sensors_event_t event;
          accel.getEvent(&event);  
  
              if (moving() > MOOVING_TRESHOLD){
              pos = UNAVAILABLE;
              }
              else if (ax >= -1.2 && ax < -0.5){
              pos = SITTING;      //("4ЕЛОВЕК $ИДИТ    ");   ascii - 31
              }
              else if (az > 0.5 && az <= 1.2){
              pos = BACK;          //("СПИНА      ");       ascii - 32
              }
              else if (az >= -1.2 && az < -0.5){
              pos = STOMACK;         //("НАПУЗЕ   ");        ascii - 33
              }
              else if (ay >= -1.2 && ay < -0.5){
              pos = LEFT;        //("Left side");         ascii - 34
              }
              else if (ay <= 1.2 && ay > 0.5){
              pos = RIGHT;        //("ПРАВЫЙ БОК");         ascii - 35
              } 
              else {
              pos = UPSIDE;     //("VVERH NOGAMI");            ascii - 36
              }
              return pos;
              }


  int breath()
  {
    for (int j = 0; j < 100; j++){
    int stosec [100];
    int persec [5];
    for(int i = 0; i < 5; i++)
    {
      persec[i] = scale.get_units();
      delay(200); 
    }
    int matoj = (persec[0] + persec[1] + persec[2] + persec[3] + persec[4]) / 5;
    stosec[j] = matoj;
    } 
  }


  int hb()
{
  for (int j = 0; j < 200; j++){
    int matoj = 0;
    int stosec [100];
    int persec [5];
    for(int i = 0; i <20; i++)
    {
      persec[i] = analogRead(A0);
      matoj = matoj + persec[i];
      delay(50); 
    }
    matoj = matoj / 20;
    stosec[j] = matoj;
    }
}

int heart()
{
  
 /* if((digitalRead(9) == 1)||(digitalRead(10) == 1)){
    Serial.println('!');
  }
  else{*/

      int value=analogRead(A0);
  if(value>UpperThreshold)
  {
    if(BeatComplete)
    {
      BPM=millis()-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  if((value<LowerThreshold)&(BPMTiming)){
    BeatComplete=true;
  }
    // send the value of analog input 0:
      Serial.println(BPM);
 // }
  //Wait for a bit to keep serial data from saturating
  delay(1);
  return BPM;
}
