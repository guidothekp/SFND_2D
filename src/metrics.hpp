/**
 * Container for metrics.
 */

#ifndef __METRICS__
#define __METRICS__

#include <string>
#include <vector>
#include <map>

/** 
 * Unlike the dataframe, we should not use a ring buffer since we want to 
 * study the system. More data the better. Even if we had a million frames, 
 * the size of this object will be ~28 million entries per detector per 
 * descriptor. Assuming each string is 10 characters, the actual size will
 * be 10 + 10 + 4 * million + 4 * million + 4 * million + 8 * million + 
 * 8 * million ~ 28 million bytes ~ 28 MB. 
 * Given that we have 5 types of detector and descriptors each,
 * we are looking at ~ 5 * 28 MB = 150 MB. 
 */
struct Metrics {
    std::string detectorType;
    std::string descriptorType;
    std::string matcherSubType;
    std::string matcherType;
    std::string selectorType;
    bool crossCheck;
    std::vector<int> totalKeyPoints;
    std::vector<int> carKeyPoints;
    std::vector<int> matchCount;
    std::vector<double> detectionTimes; //keypoint detection times.
    std::vector<double> descriptorTimes; //descriptor times.
};

//struct KeyPointMetrics {
//    std::string detectorType;
//    SummaryStatistics<int> totalPoints;
//    SummaryStatistics<int> carPoints;
//    SummaryStatistics<int> nbrPoints;
//    SummaryStatistics<double> carToNbrRatio;
//};
/**
 * Your seventh task is to count the number of keypoints on the preceding vehicle for all 10 images and take note of the distribution of their neighborhood size. Do this for all the detectors you have implemented.
 */
//void calculateKeyPointDistribution(const std::vector<Metrics> & metrics, 
//        std::vector<KeyPointMetrics> & kpMetricsList) {
//    for (const auto & metric : metrics) {
//        KeyPointMetrics kpm;
//        kpm.detectorType = metric.detectorType;
//        kpm.totalPoints = statistics(metric.totalKeyPoints);
//        kpm.carPoints = statistics(metric.carKeyPoints);
//        std::vector<int> nbrPoints;
//        std::transform(metric.totalKeyPoints.begin(),
//                metric.totalKeyPoints.end(),
//                metric.carKeyPoints.begin(),
//                std::back_inserter(nbrPoints), std::minus<int>());
//        kpm.nbrPoints = statistics(nbrPoints);
//        std::vector<double> ratios;
//        std::transform(metric.carKeyPoints.begin(),
//                metric.carKeyPoints.end(),
//                nbrPoints.begin(),
//                std::back_inserter(ratios), std::divides<double>());
//        std::transform(ratios.begin(), ratios.end(), ratios.begin(), 
//                [](double d) -> double {return d * 100.00;});
//        kpm.carToNbrRatio = statistics(ratios);
//        kpMetricsList.push_back(kpm);
//    }
//}

#endif
