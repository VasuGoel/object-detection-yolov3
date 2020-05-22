#include <string>
#include <fstream>
#include <exception>

#include "MediaLoader.h"

void MediaLoader::LoadMedia(CommandLineParser parser, VideoCapture &capture, VideoWriter &video, std::string &outputFile)
{
    std::string str;
    try {
        if (parser.has("image"))
        {
            // Open the image file
            str = parser.get<std::string>("image");
            std::ifstream filestream(str);
            if(!filestream)  throw("error");
            capture.open(str);
            str.replace(str.end()-4, str.end(), "_yolo_output.jpg");
            outputFile = str;
        }
        else if (parser.has("video"))
        {
            // Open the video file
            str = parser.get<std::string>("video");
            std::ifstream filestream(str);
            if(!filestream)  throw("error");
            capture.open(str);
            str.replace(str.end()-4, str.end(), "_yolo_output.avi");
            outputFile = str;
        }
        // Open the webcam
        else capture.open(0);
    }
    catch(...) {
        throw std::runtime_error("Could not open the input image/video stream.");
    }   

    // Get the video writer initialized to save the output video
    if (!parser.has("image")) {
        video.open(outputFile, VideoWriter::fourcc('M','J','P','G'), 28, Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT)));
    }
}