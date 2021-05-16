#include "interfaces.hpp"

#include <vector>
#include <string>
#include "statistics.hpp"

class keypointsHandler : public IHandler {
    public:
        void handle(const std::vector<Metrics> & metricsList,
                const std::string & filename);
        ~keypointsHandler() {}
};

namespace kpUtils {
    struct KeyPointMetrics {
        std::string detectorType;
        SummaryStatistics<int> totalPoints;
        SummaryStatistics<int> carPoints;
        SummaryStatistics<int> nbrPoints;
        SummaryStatistics<double> carToNbrRatio;
    };

    template<typename T>
        void mergeVectors(std::vector<T> & to, const std::vector<T> & from) {
            std::copy(from.cbegin(), from.cend(), std::back_inserter(to));
        };

    std::vector<Metrics> merge(const std::vector<Metrics> & metricsList) {
        std::vector<Metrics> rv;
        std::map<std::string, std::vector<Metrics>> map;
        for (auto iter = metricsList.cbegin(); iter != metricsList.cend(); iter++) {
            std::string key = iter->detectorType;
            if (map.find(key) == map.end()) {
                map[key] = std::vector<Metrics>{};
            }
            map[key].push_back(*iter);
        }
        for (auto iter = map.cbegin(); iter != map.cend(); iter ++) {
            std::vector<Metrics> v = iter->second;
            Metrics m = v[0];
            for (int i = 1; i < v.size(); i ++) {
                Metrics mm = v[i];
                mergeVectors(m.totalKeyPoints, mm.totalKeyPoints);
                mergeVectors(m.carKeyPoints, mm.carKeyPoints);
            }
            rv.push_back(m);
        }
        return rv;
    }

    std::vector<Metrics> findUnique(const std::vector<Metrics> & metricsList) {
        std::map<std::string, Metrics> map;
        for (auto iter = metricsList.begin();
                iter != metricsList.end(); iter ++) {
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
        return m;
    }

    std::string keyPointMetricsHeaders() {
        std::string out = "KEYPOINT_DETECTOR";
        const std::vector<std::string> types {"TOTAL_POINTS", "CAR_POINTS",
            "NON_CAR_POINTS", "CAR_TO_NON_CAR_RATIO_PERCENT"};
        const std::vector<std::string> subTypes {/*"MIN", "MAX", */ "MEAN", "SD"};
        for (int i = 0; i < types.size(); i ++) {
            const std::string base = ", " + types[i];
            std::string running;
            for (int j = 0; j < subTypes.size(); j ++) {
                running += base + "_" + subTypes[j];
            }
            out += running;
        }
        return out;
    }

    void printKeyPointMetrics(
            const std::vector<KeyPointMetrics> & keyPointMetricsList,
            const std::string & file) {
        std::vector<std::string> output;
        output.push_back(keyPointMetricsHeaders());
        for (auto iter = keyPointMetricsList.begin();
                iter != keyPointMetricsList.end();
                iter ++) {
            const KeyPointMetrics kpm = *iter;
            std::string str = kpm.detectorType;
            /*SummaryStatistics<int>*/ const auto & totalPoints = kpm.totalPoints;
            /*SummaryStatistics<int>*/ const auto & carPoints = kpm.carPoints;
            /*SummaryStatistics<int>*/ const auto & nbrPoints = kpm.nbrPoints;
            /*SummaryStatistics<float>*/ const auto & ratio = kpm.carToNbrRatio;
            str += ", " + totalPoints.to_string();
            str += ", " + carPoints.to_string();
            str += ", " + nbrPoints.to_string();
            str += ", " + ratio.to_string();
            output.push_back(str);
        }
        std::ofstream out;
        out.open(file);
        for (const auto & str : output) {
            out << str << std::endl;
        }
        out.close();
    }

    /**
     * Your seventh task is to count the number of keypoints on the preceding vehicle for all 10 images and take note of the distribution of their neighborhood size. Do this for all the detectors you have implemented.
     */
    void calculateKeyPointDistribution(const std::vector<Metrics> & metrics,
            std::vector<KeyPointMetrics> & kpMetricsList) {
        for (const auto & metric : metrics) {
            KeyPointMetrics kpm;
            kpm.detectorType = metric.detectorType;
            kpm.totalPoints = statistics(metric.totalKeyPoints);
            kpm.carPoints = statistics(metric.carKeyPoints);
            std::vector<int> nbrPoints;
            std::transform(metric.totalKeyPoints.begin(),
                    metric.totalKeyPoints.end(),
                    metric.carKeyPoints.begin(),
                    std::back_inserter(nbrPoints), std::minus<int>());
            kpm.nbrPoints = statistics(nbrPoints);
            std::vector<double> ratios;
            std::transform(metric.carKeyPoints.begin(),
                    metric.carKeyPoints.end(),
                    nbrPoints.begin(),
                    std::back_inserter(ratios), std::divides<double>());
            std::transform(ratios.begin(), ratios.end(), ratios.begin(),
                    [](double d) -> double {return d * 100.00;});
            kpm.carToNbrRatio = statistics(ratios);
            kpMetricsList.push_back(kpm);
        }
    }

    std::vector<KeyPointMetrics> prepareData(
            const std::vector<Metrics> & metricsList) {
        std::vector<Metrics> m = kpUtils::findUnique(metricsList);
        std::vector<KeyPointMetrics> keyPointMetrics;
        calculateKeyPointDistribution(m, keyPointMetrics);
        return keyPointMetrics;
    }
}

void keypointsHandler::handle(const std::vector<Metrics> & metricsList,
        const std::string & filename) {
    std::vector<kpUtils::KeyPointMetrics> keyPointMetrics = 
        kpUtils::prepareData(metricsList);
    printKeyPointMetrics(keyPointMetrics, filename);
}
