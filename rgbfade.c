#include <signal.h> //Signal 사용 헤더파일
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> //exit() 사용 헤더파일

#include <wiringPi.h>
#include <softPwm.h>

#include <wiringPi.h>

#define RGBLEDPOWER  24 //BCM_GPIO 19
#define RED		7	// BCM_GPIO 16 - OUT
#define GREEN	9	// BCM_GPIO 20 - OUT
#define BLUE	8 // BCM_GPIO 21 - OUT

void Bpluspinmodeset(void);

void setRGB(int r, int g, int b);
void sig_handler(int signo); // SIGINT 핸들러 함수
void  Fade( int fromColor, int toColor, int offColor );

int main (void)
{
	if(wiringPicheck()) printf("Fail");
		
	Bpluspinmodeset();
	
	signal(SIGINT, (void *)sig_handler);
	
	digitalWrite(RGBLEDPOWER, 1);
    
    int i = 0, j = 0, k=0;
	printf("RGB LED Various Color");
 
	softPwmCreate(RED, 0, 255);
	softPwmCreate(GREEN, 0, 255);
	softPwmCreate(BLUE, 0, 255);
	
	while(1)
	{
        // R -> G 불빛 변화
        Fade( RED, GREEN, BLUE );  // R에서 G로 FADE 전환
        
        // G -> B 불빛 변화
        Fade( GREEN, BLUE, RED );  // G에서 B로 FADE 전환
        
        // B -> R 불빛 변화
        Fade( BLUE, RED, GREEN );  // B에서 R로 FADE 전환
	}
  
  return 0 ;
}

int wiringPicheck(void)
{
	if (wiringPiSetup () == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1 ;
	}
}

void Bpluspinmodeset(void)
{
	pinMode(RGBLEDPOWER, OUTPUT);
	pinMode (RED, OUTPUT);
	pinMode (GREEN, OUTPUT);
	pinMode (BLUE, OUTPUT);	
	
}

////////////////////////////////////////
// fromColor 번호의 핀과 연결된 색상에서
// toColor 번호의 핀과 연결된 색상으로
// 점차 색상을 변화시키는 함수

void  Fade( int fromColor, int toColor, int offColor )
{
  int  color;  // fromColor 빛의 세기
  
  // fromColor -> toColor 빛깔 변화
  
  softPwmWrite( offColor, 0 );  // 먼저 offColor는 처음부터 끔 (OFF)
  
  for( color = 255; color >= 0; color-- )  // 255 에서 0 까지 1씩 감소 
  {
    softPwmWrite( fromColor, color );      // 시작할 때의 색상 ON
    softPwmWrite( toColor, 255 - color );  // 끝날 때의 색상 ON
    delay(30);  // 0.03초 동안 불빛 지속(지연)
  }
}

void sig_handler(int signo) // ctrl-c 로 종료시 실행되는 함수
{
    printf("process stop\n");
	digitalWrite(RED, 0);
	digitalWrite(GREEN, 0);
	digitalWrite(BLUE, 0);
	digitalWrite(RGBLEDPOWER, 0); //Off
	exit(0);
}

/**
void setRGB(int r, int g, int b){
  softPwmWrite(RED, 255-r);
  softPwmWrite(GREEN, 255-g);
  softPwmWrite(BLUE, 255-b);
}
*/
