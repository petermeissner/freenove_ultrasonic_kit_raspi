/**********************************************************************
* Filename    : Sweep.c
* Description : Servo sweep
* Author      : freenove
* modification: 2016/07/05
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>


// Define the unit of servo pulse offset: 0.1ms
#define OFFSET_MS 3

// Define the pulse duration for minimum angle of servo
#define SERVO_MIN_MS 5+OFFSET_MS

// Define the pulse duration for maximum angle of servo
#define SERVO_MAX_MS 25+OFFSET_MS

// define the GPIO number connected to servo
#define servoPin    1


// ????
long map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}

// initialization function for servo PMW pin
void servoInit(int pin){
    softPwmCreate(pin,  0, 200);
}

// Specif a certain rotation angle (0-180) for the servo
void servoWrite(int pin, int angle){
    if(angle > 180)
        angle = 180;
    if(angle < 0)
        angle = 0;
    softPwmWrite(pin,map(angle,0,180,SERVO_MIN_MS,SERVO_MAX_MS));
}

// specific the unit for pulse(5-25ms) with specific duration output by servo pin: 0.1ms
void servoWriteMS(int pin, int ms){
    if(ms > SERVO_MAX_MS)
        ms = SERVO_MAX_MS;
    if(ms < SERVO_MIN_MS)
        ms = SERVO_MIN_MS;
    softPwmWrite(pin,ms);
}


// main program
int main(void)
{
    // when initialize wiring faiservo,print messageto screen
    int i;
    if(wiringPiSetup() == -1){
        printf("setup wiringPi faiservo !");
        return 1;
    }
    printf("Program is starting ...\n");

    // initialize PMW pin of servo
    servoInit(servoPin);
    // make servo rotate from minimum angle to maximum angle
    //for ( i = SERVO_MIN_MS; i < SERVO_MAX_MS; i++){
    //    servoWriteMS(servoPin,i);
    //    delay(10);
    //}

    //make servo rotate from maximum angle to minimum angle
    for ( i = SERVO_MAX_MS; i > SERVO_MIN_MS; i--){
        servoWriteMS(servoPin,i);
        delay(10);
    }
    
    return 0;
}

