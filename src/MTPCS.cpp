//refactored code of MidTermProject_Camera_Student.cpp
/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

#include "metrics.hpp"
#include "metricshandler.hpp"

#define LOG 0

using namespace std;

Metrics detect(const std::string & detectorType, 
        const std::string & descriptorType, 
        const std::string & mDescriptorType,
        bool crossCheck = false,
        const std::string & matcherType = "MAT_BF", 
        const std::string & selectorType = "SEL_KNN")
{
    Metrics metrics;
    metrics.detectorType = detectorType;
    metrics.descriptorType = descriptorType;
    metrics.matcherSubType = mDescriptorType;
    metrics.matcherType = matcherType;
    metrics.selectorType = selectorType;
    metrics.crossCheck = crossCheck;

    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    string dataPath = "../";

    // camera
    string imgBasePath = dataPath + "images/";
    string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = false;            // visualize results

    /* MAIN LOOP OVER ALL IMAGES */

    for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
    {
        /* LOAD IMAGE INTO BUFFER */

        // assemble filenames for current index
        ostringstream imgNumber;
        imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
        string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

        // load image from file and convert to grayscale
        cv::Mat img, imgGray;
        img = cv::imread(imgFullFilename);
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        //// STUDENT ASSIGNMENT
        //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

        // push image into data frame buffer
        DataFrame frame;
        frame.cameraImg = imgGray;
        //Since we cannot extend an STL container and we don't want to change
        //the API for a circular buffer, let us just handle the code
        //externally.
        /*
           if (counter < dataBufferSize) {
           dataBuffer.push_back(frame);
           } else {
           dataBuffer[counter % dataBufferSize] = frame;
           }
           counter ++;
           */
        if (dataBuffer.size() == dataBufferSize) {
            if (LOG) std::cout << "buffer full. " << std::endl;
            dataBuffer.erase(dataBuffer.begin());
        }
        dataBuffer.push_back(frame);
        //    dataBuffer.push_back(frame);

        //// EOF STUDENT ASSIGNMENT
        if (LOG) cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

        /* DETECT IMAGE KEYPOINTS */

        // extract 2D keypoints from current image
        vector<cv::KeyPoint> keypoints; // create empty feature list for current image
        //"SIFT", "ORB"; //"AKAZE"; //"FAST"; //"BRISK"; //"HARRIS"; //"SHITOMASI";
        //string detectorType = "BRISK"; //"ORB"; //"AKAZE"; //"FAST"; //"BRISK"; //"HARRIS"; //"SHITOMASI";

        //// STUDENT ASSIGNMENT
        //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
        //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
        bool show = false;
        double detectTime = 0;
        if (detectorType.compare("SHITOMASI") == 0)
        {
            detectTime = detKeypointsShiTomasi(keypoints, imgGray, show);
        }
        else if (detectorType.compare("HARRIS") == 0)
        {
            detectTime = detKeypointsHarris(keypoints, imgGray, show);
        } else {
            detectTime = detKeypointsModern(keypoints, imgGray, detectorType, show);
        }
        metrics.detectionTimes.push_back(detectTime);
        //// EOF STUDENT ASSIGNMENT

        //// STUDENT ASSIGNMENT
        //// TASK MP.3 -> only keep keypoints on the preceding vehicle

        // only keep keypoints on the preceding vehicle
        bool bFocusOnVehicle = true;
        cv::Rect vehicleRect(535, 180, 180, 150);
        metrics.totalKeyPoints.push_back(keypoints.size());
        if (LOG) std::cout << "keypoint count before vehicle filtering: " << keypoints.size() << std::endl;
        if (bFocusOnVehicle)
        {
            std::vector<cv::KeyPoint> filtered;
            for (const auto & keyPoint : keypoints) {
                if (vehicleRect.contains(keyPoint.pt)) filtered.push_back(keyPoint);
            }
            keypoints = filtered;
            metrics.carKeyPoints.push_back(keypoints.size());
            if (LOG) std::cout << "keypoint count after vehicle filtering: " << keypoints.size() << std::endl;
        }
        //showKeyPoints(imgGray, keypoints, "Filtered", true);

        //// EOF STUDENT ASSIGNMENT

        // optional : limit number of keypoints (helpful for debugging and learning)
        bool bLimitKpts = false;
        if (bLimitKpts)
        {
            int maxKeypoints = 50;

            if (detectorType.compare("SHITOMASI") == 0)
            { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
            }
            cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
            //cout << " NOTE: Keypoints have been limited!" << endl;
        }

        // push keypoints and descriptor for current frame to end of data buffer
        (dataBuffer.end() - 1)->keypoints = keypoints;
        //cout << "#2 : DETECT KEYPOINTS done" << endl;

        /* EXTRACT KEYPOINT DESCRIPTORS */

        //// STUDENT ASSIGNMENT
        //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
        //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

        cv::Mat descriptors;
        //"BRISK", "BRIEF", "ORB", "FREAK", "AKAZE", "SIFT"
        //string descriptorType = "BRISK";
        double descriptorTime = descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);
        metrics.descriptorTimes.push_back(descriptorTime);
        //// EOF STUDENT ASSIGNMENT

        // push descriptors for current frame to end of data buffer
        (dataBuffer.end() - 1)->descriptors = descriptors;

        //cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

        if (dataBuffer.size() > 1) // wait until at least two images have been processed
        {

            /* MATCH KEYPOINT DESCRIPTORS */

            vector<cv::DMatch> matches;
            //string matcherType = "MAT_FLANN";        // MAT_BF, MAT_FLANN
            //string mDescriptorType = "DES_BINARY"; // DES_BINARY, DES_HOG
            //string selectorType = "SEL_KNN";       // SEL_NN, SEL_KNN

            //// STUDENT ASSIGNMENT
            //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
            //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

            matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                    (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                    matches, mDescriptorType, matcherType, selectorType);
            metrics.matchCount.push_back(matches.size());
            //// EOF STUDENT ASSIGNMENT

            // store matches in current data frame
            (dataBuffer.end() - 1)->kptMatches = matches;

            //cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;

            // visualize matches between current and previous image
            bVis = false; //true;
            if (bVis)
            {
                cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                        (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                        matches, matchImg,
                        cv::Scalar::all(-1), cv::Scalar::all(-1),
                        vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                string windowName = "Matching keypoints between two camera images";
                cv::namedWindow(windowName, 7);
                cv::imshow(windowName, matchImg);
                cout << "Press key to continue to next image" << endl;
                cv::waitKey(0); // wait for key to be pressed
            }
            bVis = false;
        }
    } // eof loop over all images
    return metrics;
}

//template<typename T>
//std::string to_str(SummaryStatistics<T> data, std::string key) {
//    std::string str = "";
//    str += std::to_string(data.min);
//    str += ", " + std::to_string(data.max);
//    str += ", " + std::to_string(data.avg);
//    str += ", " + std::to_string(data.sd);
//    return str;
//}
//
//std::string keyPointMetricsHeaders() {
//    std::string out = "KEYPOINT_DETECTOR";
//    std::vector<std::string> types {"TOTAL_POINTS", "CAR_POINTS", 
//        "NON_CAR_POINTS", "CAR_TO_NON_CAR_RATIO_PERCENT"};
//    std::vector<std::string> subTypes {"MIN", "MAX", "MEAN", "SD"};
//    for (int i = 0; i < types.size(); i ++) {
//        const std::string base = ", " + types[i];
//        std::string running;
//        for (int j = 0; j < subTypes.size(); j ++) {
//            running += base + "_" + subTypes[j];
//        }
//        out += running;
//    }
//    return out;
//}

//template<typename InputIt>
//void printKeyPointMetrics(InputIt first, InputIt last) {
//    std::vector<std::string> output;
//    output.push_back(keyPointMetricsHeaders());
//    for (auto & it = first; it != last; it ++) {
//        KeyPointMetrics kpm = *it;
//        std::string str = kpm.detectorType;
//        /*SummaryStatistics<int>*/ const auto & totalPoints = kpm.totalPoints;
//        /*SummaryStatistics<int>*/ const auto & carPoints = kpm.carPoints;
//        /*SummaryStatistics<int>*/ const auto & nbrPoints = kpm.nbrPoints;
//        /*SummaryStatistics<float>*/ const auto & ratio = kpm.carToNbrRatio;
//        str += ", " + totalPoints.to_string();
//        str += ", " + carPoints.to_string();
//        str += ", " + nbrPoints.to_string();
//        str += ", " + ratio.to_string();
//        output.push_back(str);
//    }
//    std::ofstream out;
//    out.open("../results/mp7.csv");
//    for (int i = 0; i < output.size(); i ++) {
//        out << output[i] << std::endl;
//    }
//    out.close();
//}
/*
   template<typename Iter>
   void handleKeyPointMetrics(Iter first, Iter last) {
   std::map<std::string, Metrics> map;
   for (Iter & iter = first; iter != last; iter ++) {
   std::string detector = iter->detectorType;
//std::cout << "-- " << detector << " --\n";
if (map.find(detector) == map.end()) {
//std::cout << "inserting: " << detector << std::endl;
map[detector] = *iter;
}
}
std::vector<Metrics> m;
for (const std::pair<std::string, Metrics> & element : map) {
m.push_back(element.second);
//std::cout << "== " << element.second.detectorType << std::endl;
}
std::vector<KeyPointMetrics> keyPointMetrics;
calculateKeyPointDistribution(m, keyPointMetrics);
printKeyPointMetrics(keyPointMetrics.begin(), keyPointMetrics.end());
}
*/
std::string getType(const std::string & detector) {
    /*if (!detector.compare("SIFT")) {
      return "DES_HOG";
      }*/
    return "DES_BINARY";
}

int main() {
    //std::vector<std::string> detectorTypes {"AKAZE"};
    //std::vector<std::string> descriptorTypes {"AKAZE"};
    std::vector<std::string> detectorTypes {"SIFT", "ORB", "AKAZE", "FAST",
        "BRISK", "HARRIS", "SHITOMASI"};
    std::vector<std::string> descriptorTypes {"SIFT", "ORB", "AKAZE", 
        "BRISK", "BRIEF", "FREAK"};
    
    std::vector<std::string> types {"DES_HOG", "DES_BINARY"};
    //std::vector<std::string> descriptorTypes {"BRISK", "BRIEF", "ORB", "FREAK", 
    //    "AKAZE", "SIFT"};
    std::vector<Metrics> metrics;
    std::vector<std::pair<std::string, std::string>> pairs;
    std::vector<bool> crossChecks {false, true};
    for (const auto & detector : detectorTypes) {
        for (const auto & descriptor : descriptorTypes) {
            for (const auto & type : types) {
                for (const auto cc : crossChecks) {
                    try {
                        Metrics m = detect(detector, descriptor, type, cc);//, "MAT_FLANN");
                        metrics.push_back(m);
                        std::cout << detector<< ", " 
                            << descriptor << ", " << type 
                            << ", " << "crossCheck? " << cc << std::endl;
                    } catch(const std::exception & error) {
                        pairs.push_back({detector, descriptor});
                    }
                }
            }
        }
    }
    for (int i = 0; i < pairs.size(); i ++) {
        std::pair<std::string, std::string> pair = pairs[i];
        std::cout << "( " << pair.first << ", " << pair.second << " )" << std::endl;
    }
    const std::string keypointsResultsFile {"../results/mp7.csv"};
    const std::string matchesResultsFile {"../results/mp8.csv"};
    const std::string timerResultsFile {"../results/mp9.csv"};
    metricsHandler mh(metrics, keypointsResultsFile, matchesResultsFile, 
            timerResultsFile);
    mh.handle();
    //mh.printData("../results/mp7_new.csv");
    //handleKeyPointMetrics(metrics.begin(), metrics.end());
    return 0;
}
