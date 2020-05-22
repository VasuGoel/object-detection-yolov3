#ifndef DRAW_H
#define DRAW_H

#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>

#include "YoloNet.h"

using namespace cv;

class Drawable
{     
public: 
    Drawable(YoloNet yolonet) : classes_(yolonet.getClasses()) {};

    void postprocess(Mat& frame, const std::vector<Mat>& outs, int confThreshold, int nmsThreshold);
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);

private:
    std::vector<std::string> classes_;
};

#endif