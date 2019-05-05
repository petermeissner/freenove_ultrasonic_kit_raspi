/**********************************************************************
* Filename    : Blink.c
* Description : Make an led blinking.
* auther      : www.freenove.com
* modification: 2016/06/07
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define  ledPin    0

int main(void)
{
	if(wiringPiSetup() == -1){ // When initialize wiring failed, print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}
	
	// When initialize wiring successfully, print message to screen	
	printf("wiringPi initialize successfully, GPIO %d(wiringPi pin)\n", ledPin); 	
	
	// Set the pin mode
	pinMode(ledPin, OUTPUT); 

	while(1){
		
			//led on
			digitalWrite(ledPin, HIGH);  
			printf("led on...\n");
			delay(1000);
			
			//led off
			digitalWrite(ledPin, LOW);  
			printf("...led off\n");
			delay(1000);
	}

	return 0;
}

