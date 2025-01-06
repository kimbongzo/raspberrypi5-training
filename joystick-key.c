#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


// Use GPIO Pin 17, which is Pin 0 for wiringPi library

#define switch 21  //BCM 5, wiringPi 21


// -------------------------------------------------------------------------
// main
int main(void) 
{
	// sets up the wiringPi library
	if (wiringPiSetup () < 0) 
	{
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
		return 1;
	}
	
	pinMode(switch, INPUT);

	// set Pin 17/0 generate an interrupt on high-to-low transitions
	// and attach myInterrupt() to the interrupt
	/*if ( wiringPiISR (LIGHTSEN_OUT, INT_EDGE_RISING, &myInterrupt) < 0 ) 
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
		return 1;
	}*/

	// display counter value every second.
	while ( 1 ) 
	{
		//printf( "%d\n", eventCounter );
		//eventCounter = 0;
		
		if(digitalRead(switch) == 0)
			printf("light full ! \n");
		if(digitalRead(switch) == 1)
			printf("dark \n");		
	
		delay( 200 ); // wait 1 second
	}

	return 0;
}
