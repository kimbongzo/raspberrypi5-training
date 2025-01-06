# Import necessary libraries
from board import SCL, SDA
import busio
from PIL import Image, ImageDraw, ImageFont
import adafruit_ssd1306
import subprocess
import psutil
 
# Create the I2C interface
i2c = busio.I2C(SCL, SDA)
 
# Create the SSD1306 OLED class
display = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c)
 
# Clear display
display.fill(0)
display.show()
 
# Create blank image for drawing with mode '1' for 1-bit color
width = display.width
height = display.height
image = Image.new('1', (width, height))
 
# Get drawing object to draw on image
draw = ImageDraw.Draw(image)
 
# Draw a black filled box to clear the image
draw.rectangle((0, 0, width, height), outline=0, fill=0)
 
# Define some constants to allow easy resizing of shapes
padding = -2
top = padding
bottom = height - padding
 
# Move left to right keeping track of the current x position for drawing shapes
x = 0
 
# Load a default font
font = ImageFont.load_default()
 
# Collect system information
def get_system_info():
    # CPU usage
    cpu_usage = f"CPU: {psutil.cpu_percent()}%"
    # RAM usage
    ram = psutil.virtual_memory()
    ram_usage = f"RAM: {ram.percent}%"
    # IP address
    cmd = "hostname -I | cut -d' ' -f1"
    ip_address = subprocess.check_output(cmd, shell=True).decode("utf-8").strip()
    ip_info = f"IP: {ip_address}"
 
    return cpu_usage, ram_usage, ip_info
 
# Display system information on OLED
while True:
    # Draw a black filled box to clear the image
    draw.rectangle((0, 0, width, height), outline=0, fill=0)
 
    # Get system info
    cpu_usage, ram_usage, ip_info = get_system_info()
 
    # Write lines of text
    draw.text((x, top + 0), cpu_usage, font=font, fill=255)
    draw.text((x, top + 8), ram_usage, font=font, fill=255)
    draw.text((x, top + 16), ip_info, font=font, fill=255)
 
    # Display image
    display.image(image)
    display.show()
