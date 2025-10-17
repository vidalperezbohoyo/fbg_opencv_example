# fbg_opencv_example
![GIF](gif.gif)  
Read from **USB-Camera** and draw the **cv::Mat**

# Hardware for running the example
## My hardware
I am using a **gc9a01** display in **Raspberry Pi 3B+**, *but other SPI (and I2C) screens can be used with this method*. 

## Wiring
| TFT Pin | Raspberry Pi Physical Pin (number inside circles on the pinout image) |
|----------------|---------------------------|
| VCC            | 1 (3.3v)                     |
| GND            | 6 (GND)                          |
| CS             | 24                        |
| RESET          | 13                        |
| DC / RS        | 22                        |
| MOSI           | 19                        |
| SCK/SCL           | 23                        |

> Also, you will need a USB Camera.  
*In my Raspberry is mounted on /dev/video0*.  

Raspberry Pi 3B+ pin reference:  
![PINOUT](pinout.jpg)

# Configuration
> Based on: https://github.com/juliannojungle/gc9a01-overlay?tab=readme-ov-file

*You have to change one thing in the SD card.*  

Open it with an external PC and navigate to **/boot** partition. 
> Note: On my PC is called **D:bootfs**.

You will find a folder called **/overlays** find here: **gc9a01.dtbo** 
> Note: Use your screen name *nameofscreen.dtbo*.
 
**If exist, nice. If not, you have to find it in internet and add it.**  
  
Now, you have to change in **config.txt** (this file is outside of **/overlays** folder):  

```dtoverlay=gc9a01```  
> Note: Use your screen name *dtoverlay=nameofscreen*
 
Insert the SD card and turn on the system. 
> Note: Probably you have now losed the HDMI Desktop image and you have a terminal. (Search in internet to fix that).

Ensure that now there are 2 devices (one is your HDMI and the other is the TFT display).
Type in terminal:  
```bash
ls /dev/fb*
```   
Should output at least **/dev/fb0** and **/dev/fb1**

> Note: If not, check the wiring and SD /boot configuration. Screen is not being recognised.

# Downloading, compiling and running  
Download where ever you want the repo of fbg:
```bash
git clone https://github.com/grz0zrg/fbg
```
Inside of the folder **/examples** you can find several examples. Run them first to check screen behaviour.
```bash
make
./quickstart
```

**If is working**, insert in that folder my example code: **cam_to_fbg.cpp**

> Note: Install opencv if needed

## Compilation  
**First C files** (Do once) 
```bash
gcc -c ../src/lodepng/lodepng.c ../src/nanojpeg/nanojpeg.c ../src/fbgraphics.c ../custom_backend/fbdev/fbg_fbdev.c -I../src -I. -I../custom_backend/fbdev -O2 -Wall
```
**Create static lib** (Do once)
```bash
ar rcs libfbg.a lodepng.o nanojpeg.o fbgraphics.o fbg_fbdev.o
```

**Compile the example** (Do on every change)  
```bash
g++ cam_to_fbg.cpp -I../src -I. -I../custom_backend/fbdev -std=c++11 -Wall -g `pkg-config --cflags --libs opencv4` libfbg.a -lm -o cam_to_fbg
```

# Run
```bash
./cam_to_fbg
```
