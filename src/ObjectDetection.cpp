#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "YoloNet.h"
#include "MediaLoader.h"
#include "Draw.h"

using namespace cv;

const char* keys =
"{help h usage ? | | Usage examples: \n\t\t./ObjectDetection --image=../image.jpg \n\t\t./ObjectDetection --video=../video.mp4}"
"{image i        |<none>| input image   }"
"{video v       |<none>| input video   }"
;

// Initialize the parameters
float confThreshold = 0.5;      // Confidence threshold
float nmsThreshold = 0.4;       // Non-maximum suppression threshold
int inpWidth = 416;             // Width of network's input image
int inpHeight = 416;            // Height of network's input image


int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, keys);
    parser.about("Use this script to run object detection with YOLOv3 in OpenCV.");
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    // Specify the configuration and weight files for the model
    std::string modelConfiguration = "../yolov3-coco/yolov3.cfg";
    std::string modelWeights = "../yolov3-coco/yolov3.weights";

    // Create YOLO network instance
    YoloNet yolonet(modelConfiguration, modelWeights);

    // Load the network
    yolonet.loadNetwork();

    // Load names of classes
    std::string classesFilePath = "../yolov3-coco/coco.names";
    yolonet.loadClasses(classesFilePath);

    // Create a drawable object with model instance
    Drawable draw(yolonet);
    
    // Open a video file or an image file or a camera stream.
    std::string outputFile;
    VideoCapture cap;
    VideoWriter video;
    Mat frame, blob;

    try
    {
        MediaLoader::LoadMedia(parser, cap, video, outputFile);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    // Create a window
    static const std::string kWinName = "Deep learning object detection with YOLOv3";
    namedWindow(kWinName, WINDOW_NORMAL);

    // Process frames
    while (waitKey(1) < 0)
    {
        // get frame from the video
        cap >> frame;

        // Stop the program if reached end of video
        if (frame.empty()) {
            std::cout << "Done processing." << std::endl;
            std::cout << "Output file stored at " << outputFile << std::endl;
            waitKey(3000);
            break;
        }

        // Create a 4D blob from a frame.
        dnn::blobFromImage(frame, blob, 1/255.0, Size(inpWidth, inpHeight), Scalar(0,0,0), true, false);
        
        //Sets the input to the network
        yolonet.setInput(blob);
        
        // Runs the forward pass to get output of the output layers
        std::vector<Mat> outs;
        yolonet.runForwardPass(outs, yolonet.getOutputsNames());
        
        // Remove the bounding boxes with low confidence
        draw.postprocess(frame, outs, confThreshold, nmsThreshold);
        
        // Put efficiency information
        std::vector<double> layersTimes;
        double freq = getTickFrequency() / 1000;
        double t = yolonet.getInferenceTime(layersTimes) / freq;
        std::string label = format("Inference time for a frame : %.2f ms", t);
        putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
        
        // Write the frame with the detection boxes
        Mat detectedFrame;
        frame.convertTo(detectedFrame, CV_8U);
        if (parser.has("image"))    imwrite(outputFile, detectedFrame);
        else video.write(detectedFrame);
        
        imshow(kWinName, frame);     
    }
    
    cap.release();
    if (!parser.has("image")) video.release();

    return 0;
}
