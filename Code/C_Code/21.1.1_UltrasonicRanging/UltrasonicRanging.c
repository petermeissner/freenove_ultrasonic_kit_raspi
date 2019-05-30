/**********************************************************************
* Filename    : UltrasonicRanging.c
* Description : Get distance from UltrasonicRanging
* Author      : freenove / modified by petermeissner
* modification: 2016/07/14 / 2019-05-10
* build:        gcc UltrasonicRanging.c  -o UltrasonicRanging -lwiringPi -lm
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define trigPin 4       
#define echoPin 5
#define MAX_DISTANCE 220        // define the maximum measured distance
#define timeOut MAX_DISTANCE*60 // calculate timeout according to the maximum measured distance


// function pulseIn: obtain pulse time of a pin
int pulseIn(int pin, int level, int timeout);

// function to print timestamp and data
int print_data(float* distance);

// get the measurement results of ultrasonic module,with unit: meter
float getSonar(){   
    
    // var declaration
    long pingTime;
    float distance;
    
    // trigPin send 10us high level 
    digitalWrite(trigPin,HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    
    // read plus time of echoPin
    pingTime = pulseIn(echoPin,HIGH,timeOut);   
    
    // the sound speed is 340m/s,and calculate distance
    distance = (float)pingTime * 340.0 / 2.0 / 1000000.0;
    
    // return 
    return distance;
}

int main(){
    // startup 
    printf("Program is starting ... \n");
    
    // when initialize wiring failed,print messageto screen
    if(wiringPiSetup() == -1){
        printf("setup wiringPi failed !");
        return 1; 
    }
    
    // var init
    float distance = 0;
    struct timeval now;
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    
    // endless loop
    while(1){
        distance = getSonar();
        print_data(&distance);
        delay(30);
    }   
    
    // return
    return 1;
}

int pulseIn(int pin, int level, int timeout)
{
   struct timeval tn, t0, t1;
   long micros;
   gettimeofday(&t0, NULL);
   micros = 0;
   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   gettimeofday(&t1, NULL);
   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);
   return micros;
}

// rpint time stamp and data
int print_data(float* distance) {
  char buffer[26];
  int millisec;
  struct tm* tm_info;
  struct timeval tv;

  gettimeofday(&tv, NULL);

  // Round to nearest millisec
  millisec = lrint(tv.tv_usec/1000.0); 
  
  // Allow for rounding up to nearest second
  if (millisec>=1000) { 
    millisec -=1000;
    tv.tv_sec++;
  }

  tm_info = localtime(&tv.tv_sec);

  strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
  printf("%s.%03d: %f\n", buffer, millisec, *distance);

  return 0;
}


