# fbg_opencv_example
In this repo is shown the fbg library working with OpenCV in C++.  
I am using a RPi3B+ and gc9a01 SPI screen. Others systems can be used.
![GIF](gif.gif)
This example shows:
- Read cv::Mat from cv::VideoCapture
- Convert to fbg_img struct
- Display on the TFT (Any TFT)

# Hardware for running the example
I am using a **gc9a01** display, but other SPI (and I2C) screens can be used with this method.  
The wiring is (using the Pin Number, the one in the circles):
| TFT Pin | Raspberry Pi Physical Pin |
|----------------|---------------------------|
| VCC            | 1 (3.3v)                     |
| GND            | 6 (GND)                          |
| CS             | 24                        |
| RESET          | 13                        |
| DC / RS        | 22                        |
| MOSI           | 19                        |
| SCK/SCL           | 23                        |


Raspberry Pi 3B pin reference:
![PINOUT](pinout.jpg)


# Configuration on Raspberry (or probably other linux systems)
You have to change one thing in the SD card.  
Open it with an external PC and navigate to /boot partition. You will find a folder

Change this line:

Reboot.

Ensure that now there are 2 devices (one is your HDMI and the other is the TFT display).
If not, check the wiring and SD /boot configuration.

# Downloading, compiling and running
I am using a workaround.  
Download where ever you want the repo of fbg: 

Inside of the folder examples you can find several examples

Run it first to check screen behaviour

If is working, insert in that folder my example code: cam_to_fbg.cpp

Install opencv and other dependencies if they are needed:

Compile it with:
