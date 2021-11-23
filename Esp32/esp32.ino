#define USE_ARDUINO_INTERRUPTS false
#define FORCE_SENSOR_PIN 32
#include <PulseSensorPlayground.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "battery.h"
#include "heart.h"
#include "lungs.h"
#include "bluetooth.h"
#include "axles.h"
#include <SD.h>
#include <ADXL345.h>
#include <Adafruit_ADXL345_U.h>

#define FF21 &FreeSansBold18pt7b
#define TFT_WHITE 0xFFFF
#define UpperThreshold 550
#define LowerThreshold 500
const int MOOVING_TRESHOLD = 150;

const int PULSE_INPUT = 33;
const int PULSE_BLINK = 2;    // Pin 13 is the on-board LED
const int PULSE_FADE = 5;
const int THRESHOLD = 500;   // Adjust this number to avoid noise when idle
const int UNAVAILABLE = 0;
const int SITTING = 5;
const int BACK = 1;
const int STOM = 2;
const int LEFT = 4;
const int RIGHT = 3;
const int UPSIDE = 6;

int BPM = 0;
int mass[100] = {};
int count = 0;
int BF = 0;

const int chipSelect = 4;

byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

const int OUTPUT_TYPE = SERIAL_PLOTTER;
TFT_eSPI tft = TFT_eSPI(); 
PulseSensorPlayground pulseSensor;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
ADXL345 adxl;

void setup(void) {
  /////////////DISPLAY/////////////////
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  
  tft.drawLine(0, 20, 229, 20, TFT_WHITE);
  tft.drawLine(0, 75, 229, 75, TFT_WHITE);
  tft.drawLine(0, 130, 229, 130, TFT_WHITE);
  tft.drawLine(0, 185, 229, 185, TFT_WHITE);

  tft.pushImage(0, 0,  20, 20, bluetooth);
  tft.pushImage(110, 0, 20, 20, battery);
  tft.pushImage(0, 25,  48, 48, heart);
  tft.pushImage(0, 80,  48, 48, lungs);
  tft.pushImage(0, 135,  48, 48, axles);

  tft.setFreeFont(FF21);
  tft.setTextColor(TFT_RED);
  tft.drawString("N/A", 60, 35);
  tft.setTextColor(TFT_BLUE);
  tft.drawString("N/A", 60, 90);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("0", 60, 145);

 /////////////PULSE_SENSOR/////////////////
 Serial.begin(115200);
 
 pulseSensor.analogInput(PULSE_INPUT);
 pulseSensor.blinkOnPulse(PULSE_BLINK);
 pulseSensor.fadeOnPulse(PULSE_FADE);

 pulseSensor.setSerial(Serial);
 pulseSensor.setOutputType(OUTPUT_TYPE);
 pulseSensor.setThreshold(THRESHOLD);

 samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

/////////////AXELEROMETER/////////////////

//axel();
 
/////////////MICRO_SD CARD/////////////////
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

void getBPM1()
{
 if (pulseSensor.sawNewSample()) {
    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
       BPM = pulseSensor.getBeatsPerMinute();  
       // Serial.print("BPM: ");                       
        Serial.println(BPM); 
        tft.setFreeFont(FF21);
        tft.setTextColor(TFT_RED);
        tft.fillRect(60, 35, 60, 35, TFT_BLACK);
        tft.drawString(String(BPM), 60, 35); 
      }
    } 
 }

void getBF1()
{
  int SensorReading = analogRead(FORCE_SENSOR_PIN); 
  int mfsr_r18 = map(SensorReading, 0, 1024, 0, 255);
  //Serial.println(mfsr_r18);
  mass[count] = mfsr_r18; 
  count++;
  if (count == 100)
  {
    count = 0;
    for(int i = 0; i <= 100; i++)
    {
      int value = mass[i];
      if(value >= 100)
      {
        count++;
      }
    }
    BF = count * 0.6;
    for(int j = 0; j <= 100; j++)
    {
      mass[j] = 0;
    }
    count = 0;
    //Serial.println("BF= ");
    //Serial.println(BF);
    tft.setFreeFont(FF21);
    tft.setTextColor(TFT_BLUE);
    tft.fillRect(60, 90, 60, 35, TFT_BLACK);
    tft.drawString(String(BF*2), 60, 90);
    }
    delay(100);
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

 int pos(){
    
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
              pos = SITTING;      //("Сидя");   
              }
              else if (az > 0.5 && az <= 1.2){
              pos = BACK;          //("Спина");      
              }
              else if (az >= -1.2 && az < -0.5){
              pos = STOM;         //("Живот");        
              }
              else if (ay >= -1.2 && ay < -0.5){
              pos = LEFT;        //("Лево");         
              }
              else if (ay <= 1.2 && ay > 0.5){
              pos = RIGHT;        //("Право");         
              } 
              else {
              pos = UPSIDE;     //(" ");            
              }
              return pos;
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

  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment

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
void loop() 
{ 
/* getBPM1();
 delay(100);
 getBF1();
 delay(100); */

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    
    dataFile.println(getBPM1());
    Serial.println(getBPM1());    

    dataFile.println(pos());
    Serial.println(pos());
    
    dataFile.println(getBF1());
    Serial.println(getBF1());
    
    dataFile.close();
  }
  else {
    
    Serial.println("error opening datalog.txt");
  }
  delay(200);
}






  
