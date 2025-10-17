#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <opencv2/opencv.hpp>

extern "C" {
    #include "../src/fbgraphics.h"
    #include "../custom_backend/fbdev/fbg_fbdev.h"
}

using namespace cv;

int main(int argc, char **argv)
{
    const char *fbdev = "/dev/fb1"; // Use fb0 or fb1 depending on your setup. HDMI or TFT display.

    std::cout << "Program started" << std::endl;

    VideoCapture cap("/dev/video0"); // Open default camera

    if (!cap.isOpened())
    {
        std::cerr << "[ERROR] Camera not opened" << std::endl;
        return 1;
    }

    int cam_w = (int)cap.get(CAP_PROP_FRAME_WIDTH);
    int cam_h = (int)cap.get(CAP_PROP_FRAME_HEIGHT);

    std::cout << "Camera resolution: " << cam_w << "x" << cam_h << std::endl;

    struct _fbg *fbg = fbg_fbdevSetup((char*)fbdev, 0);
    if (!fbg) 
    {
        std::cerr << "[ERROR] Could not initialize framebuffer" << std::endl;
        return 1;
    }

    std::cout << "Framebuffer initialized. Size: " << fbg->width << "x" << fbg->height << std::endl;

    Mat frame;
    Mat resized;

    uint8_t *buffer;

    while (true) 
    {
        cap >> frame;
        if (frame.empty()) 
        {
            std::cerr << "[ERROR] Empty frame" << std::endl;
            continue;
        }
  
        resize(frame, resized, Size(fbg->width, fbg->height));
        cvtColor(resized, resized, COLOR_BGR2RGB);

        // Convert to PNG
        std::vector<uint8_t> png_vec;
        if (!cv::imencode(".png", resized, png_vec))
        {
            std::cerr << "[ERROR] encoding image to PNG" << std::endl;
            continue;
        }
        size_t buf_size = png_vec.size();
        buffer = (uint8_t*) malloc(buf_size);
        if (!buffer) 
        {
            std::cerr << "[ERROR] Malloc() error" << std::endl;
            continue;
        }

        std::memcpy(buffer, png_vec.data(), buf_size);

        struct _fbg_img* img = fbg_loadImageFromMemory(fbg, buffer, buf_size);
        if (!img) 
        {
            std::cerr << "[ERROR] Could not load image into FBG" << std::endl;
            continue;
        }
        
        fbg_imageClip(fbg, img, 0, 0, 0, 0, fbg->width, fbg->height);

        fbg_flip(fbg); // I don't know if this is necessary here

        fbg_draw(fbg);

        if (waitKey(1) == 'q')
            break;

        fbg_freeImage(img);
        free(buffer);
    }

    fbg_close(fbg);
    return 0;
}
