mkdir yolov3-coco
curl https://pjreddie.com/media/files/yolov3.weights -o ./yolov3-coco/yolov3.weights
curl https://github.com/pjreddie/darknet/blob/master/cfg/yolov3.cfg?raw=true -o ./yolov3-coco/yolov3.cfg
curl https://github.com/pjreddie/darknet/blob/master/data/coco.names?raw=true -o ./yolov3-coco/coco.names
echo "YOLOv3 model configurations downloaded successfully."