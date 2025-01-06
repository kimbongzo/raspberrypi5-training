import RPi.GPIO as gpio
import time

PINS = [6, 13, 19, 7]
SEQA = [(6, 13), (13, 19), (19, 7), (7, 6)]

DELAY = 0.05
def full_drive_stepper(seq):
    for pin in PINS:
        if pin in SEQA[seq]:
            gpio.output(pin, gpio.HIGH)
        else:
            gpio.output(pin, gpio.LOW)
    time.sleep(DELAY)

gpio.setmode(gpio.BCM)

for pin in PINS:
    gpio.setup(pin, gpio.OUT)

index = 0
try:
    while True:
        full_drive_stepper(index % 4)
        index += 1
except KeyboardInterrupt:
    gpio.cleanup()
