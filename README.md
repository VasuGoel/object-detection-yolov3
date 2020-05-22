# Object Detection using YOLOv3
Deep Learning Object Detection in image, video and stream data using YOLOv3 object detection algorithm with OpenCV real-time 
computer vision library. YOLOv3 is the latest variant of the popular object detection algorithm YOLO - You Only Look Once. The
published model recognizes 80 different objects of the COCO dataset in images and videos.

## Cloning
You can clone the repository with HTTPS:
```
https://github.com/VasuGoel/object-detection-yolov3.git
```
or with SSH:
```
git@github.com:VasuGoel/object-detection-yolov3.git
```

## Dependencies
* cmake >= 3.11
  * All OSes: installation instructions can be found [here](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools](https://developer.apple.com/xcode/features/) to get make
  * Windows: installation instructions can be found [here](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* OpenCV >= 4.3
  * Linux: installation instructions can be found [here](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)
  * Mac: `brew install opencv`
  * Windows: Pre-built binaries can found [here](https://opencv.org/opencv-4-3-0/)
  * Download OpenCV 4.3.0 source code from [here](https://codeload.github.com/opencv/opencv/zip/4.3.0)
  
## Download model files
You can download the YOLOv3 model configurations, trained weights and class names in the COCO dataset by running the shell script as follow:
```
sudo chmod a+x getModelConfig.sh
./getModelConfig.sh
```
or if you wish to train a YOLOv3 model on your own dataset then skip this part but remember to update the model file paths with the new configurations, weights and class names.

## Compiling and Running
### Compiling
To compile the project, create a `build` directory and `cd` into that directory:
```
mkdir build && cd build
```
From within the `build` directory, run `cmake` and `make` as follows:
```
cmake ..
make
```

  
