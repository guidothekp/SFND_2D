//implementation for the mp.7
/**
 * TASK MP.7
 * Your seventh task is to count the number of keypoints on the preceding 
 * vehicle for all 10 images and take note of the distribution of their 
 * neighborhood size. Do this for all the detectors you have implemented.
*/

#include "dataStructures.h"
#include "matching2D.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

class MP7 {
    private:
        std::string basePath, prefix, fileType(".png");
        size_t start(0), end(9), fillWidth(4), dataBufferSize(2);
        std::vector<DataFrame> dataBuffer;
};
