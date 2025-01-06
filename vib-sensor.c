#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


// Use GPIO Pin 17, which is Pin 0 for wiringPi library

#define vib_out 26  //BCM 12, wiringPi 26

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
    
	pinMode(vib_out, INPUT);


	// display counter value every second.
	while ( 1 ) 
	{
		//printf( "%d\n", eventCounter );
		//eventCounter = 0;
		        
		if(digitalRead(vib_out) == 0)
			printf("detect ! \n");
		if(digitalRead(vib_out) == 1)
			printf("Not detect \n");		
	
		delay( 200 ); // wait 1 second
	}

	return 0;
}
