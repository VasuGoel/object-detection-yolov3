#ifndef YOLONET_H
#define YOLONET_H

#include <string>
#include <vector>
#include <opencv2/dnn.hpp>

using namespace cv;
using namespace cv::dnn;

class YoloNet 
{
public:
    // Initialize YOLO network with specified model configurations and model weights
    YoloNet(std::string modelConfiguration, std::string modelWeights) : modelConfiguration_(modelConfiguration), modelWeights_(modelWeights) {};

    void loadNetwork();
    void loadClasses(std::string classesFilePath);
    std::vector<std::string> getClasses();

    void setInput(Mat blob);
    std::vector<std::string> getOutputsNames();
    void runForwardPass(std::vector<Mat> &outs, std::vector<std::string> outnames);
    double getInferenceTime(std::vector<double> &layersTimes);

private:
    std::vector<std::string> classes_;      // stores class names used in COCO dataset
    std::string modelConfiguration_;        // specify model configurations
    std::string modelWeights_;              // specify model weights

    Net network_;                           // used to create and manipulate artificial neural network
};

#endif