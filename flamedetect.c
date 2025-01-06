#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


// Use GPIO Pin 17, which is Pin 0 for wiringPi library

#define flame 28  //BCM 20, wiringPi 28

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
	
	pinMode(flame, INPUT);

	// display counter value every second.
	while ( 1 ) 
	{
		//printf( "%d\n", eventCounter );
		//eventCounter = 0;
		
		if(digitalRead(flame) == 0)
			printf("flame sensor - Fire ! \n");
		if(digitalRead(flame) == 1)
			printf("not detect \n");		
	
		delay( 200 ); // wait 1 second
	}

	return 0;
}
