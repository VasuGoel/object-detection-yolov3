#include <string>
#include <fstream>
#include <sstream>
#include <opencv2/dnn.hpp>

#include "YoloNet.h"

// Load the network
void YoloNet::loadNetwork()
{
    network_ = readNetFromDarknet(modelConfiguration_, modelWeights_);
    network_.setPreferableBackend(DNN_BACKEND_OPENCV);
    network_.setPreferableTarget(DNN_TARGET_CPU);
}

// Load class names used in COCO dataset
void YoloNet::loadClasses(std::string classesFilePath)
{
    std::string line;
    std::ifstream filestream(classesFilePath);
    while(getline(filestream, line))    classes_.push_back(line);
}

// Return the names of classes
std::vector<std::string> YoloNet::getClasses()
{
    return std::move(YoloNet::classes_);
}

// Set input for network
void YoloNet::setInput(Mat blob)
{
    network_.setInput(blob);
}

// Get the names of the output layers
std::vector<std::string> YoloNet::getOutputsNames()
{
    static std::vector<std::string> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> outLayers = network_.getUnconnectedOutLayers();
        
        //get the names of all the layers in the network
        std::vector<std::string> layersNames = network_.getLayerNames();
        
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

// Run forward pass to get output of output layers
void YoloNet::runForwardPass(std::vector<Mat> &outs, std::vector<std::string> outnames) 
{
    network_.forward(outs, outnames);
}

// Return overall time for inference and timing for each layer (in layersTimes)
double YoloNet::getInferenceTime(std::vector<double> &layersTimes)
{
    double time = network_.getPerfProfile(layersTimes);
    return time;
}