#ifndef MEDIALOADER_H
#define MEDIALOADER_H

#include <opencv2/highgui.hpp>

using namespace cv;

namespace MediaLoader
{
    void LoadMedia(CommandLineParser parser, VideoCapture &capture, VideoWriter &video, std::string &outputFile);
};

#endif