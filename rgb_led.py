import RPi.GPIO as GPIO   # GPIO 제어 모듈
import time               # time 모듈

R = 4                    # wPi. 0(GPIO. 0), BCM. 17, Physical-Pin. 11(LED 4)
G = 22                    # wPi. 1(GPIO. 1), BCM. 18, Physical-Pin. 12(LED 2)
B = 23                    # wPi. 2(GPIO. 2), BCM. 27, Physical-Pin. 13(LED 1)
                          # 가장 긴 핀(LED 3)은 Phical-Pin. 1(3.3v)로 연결

GPIO.setmode(GPIO.BCM)    # BCM모드 설정
GPIO.setup(R, GPIO.OUT)   # OUTPUT(출력) 설정
GPIO.setup(G, GPIO.OUT)   # OUTPUT(출력) 설정
GPIO.setup(B, GPIO.OUT)   # OUTPUT(출력) 설정

# 초당 60Hz면 깜빡거림이 보이지 않음(기호(?)에 따라 더 늘려도 괜찮음)
pwm_R = GPIO.PWM(R, 60)
pwm_G = GPIO.PWM(G, 60)
pwm_B = GPIO.PWM(B, 60)

# 공통캐소드이므로 반대로 넣어줘야함, 즉 0과 같음.
pwm_R.start(100)
pwm_G.start(100)
pwm_B.start(100)

# 0xff(255)에서 2.55를 나누면 100이 됨(Duty Cycle의 최대값이 100)
# 그리고 0xff(255)를 빼는 이유는 공통캐소드이므로 반대값이 들어가야 함.
def LedColorSet(r, g, b) :
    pwm_R.ChangeDutyCycle((0xff - r) / 2.55)
    pwm_G.ChangeDutyCycle((0xff - g) / 2.55)
    pwm_B.ChangeDutyCycle((0xff - b) / 2.55)

try :                                   # 정상 작동일 때
    while True :                        # 무한루프
        LedColorSet(0xff, 0x00, 0x00)   # Red (ff0000)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0x00, 0xff, 0x00)   # Green (00ff00)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0x00, 0x00, 0xff)   # Blue (0000ff)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0xff, 0xff, 0xff)   # White (ffffff)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0x00, 0xff, 0xff)   # Cyan (00ffff)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0xff, 0x00, 0xff)   # Magenta (ff00ff)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0xff, 0xff, 0x00)   # Yellow (ffff00)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0x00, 0x00, 0x00)   # Black(꺼짐) (000000)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0xff, 0xa2, 0x00)   # Orange (ffa200)
        time.sleep(1)                   # 1초 대기
        LedColorSet(0xff, 0x7d, 0xe5)   # Pink (ff7de5)
        time.sleep(1)                   # 1초 대기

except :            # 종료 시
    pwm_R.stop()    # pwm 종료
    pwm_G.stop()    # pwm 종료
    pwm_B.stop()    # pwm 종료
    GPIO.cleanup()  # GPIO 초기화
    print("end")    # "end" 메시지 출력
