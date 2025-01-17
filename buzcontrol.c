#include <signal.h> //Signal 사용 헤더파일
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> //exit() 사용 헤더파일

#include <wiringPi.h>

#define BUZCONTROL  0	//BCM17, wiringPi 0

void sig_handler(int signo); // SIGINT 핸들러 함수

int main (void)
{
	if (wiringPiSetup () == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1 ;
	}
		
	signal(SIGINT, (void *)sig_handler);	
	
	int i;
	while(1)
	{	
		printf("here \n");
		
		pinMode (BUZCONTROL, OUTPUT);
		
		//delay(1000);
			
		digitalWrite(BUZCONTROL, 1);
		delay(1000);
		digitalWrite(BUZCONTROL, 0);
		delay(1000);

		
	}	
  
  return 0 ;
}

void sig_handler(int signo) // ctrl-c 로 종료시 실행되는 함수
{
    printf("process stop\n"); 	
	digitalWrite(BUZCONTROL, 0);
	exit(0);
}


