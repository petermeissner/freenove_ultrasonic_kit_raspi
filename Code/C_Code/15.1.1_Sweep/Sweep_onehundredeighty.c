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
// function returning long
// 
long map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}

// initialization function for servo PMW pin
void servoInit(int pin){
    softPwmCreate(pin,  0, 200);
}

// Specif a certain rotation angle (0-180) for the servo
void servoWrite(int pin, int angle){
    softPwmWrite(
        pin,
        map(angle, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS)
    );
}


// main program
int main(void)
{
    // when initialize wiring faiservo,print messageto screen
    int i;
    if(wiringPiSetup() == -1){
        printf("setup wiringPi fail servo !\n");
        return 1;
    }
    printf("Moving ervo to 0 degree\n");

    // initialize PMW pin of servo
    servoInit(servoPin);
    servoWrite(servoPin, 0);

    return 0;
}

