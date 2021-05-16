#ifndef __STATISTICS__
#define __STATISTICS__

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
struct SummaryStatistics {
    T min;
    T max;
    double avg;
    double sd;
    const std::string to_string() const {
        std::string s;
        //s += std::to_string(min);
        //s += ", " + std::to_string(max);
        s += /*", " + */std::to_string(avg);
        s += ", " + std::to_string(sd);
        return s;
    }
};

//Given random variables that are have been observed, return the statistics
//of their sum
template<typename T>
struct Sum {
    typename std::vector<SummaryStatistics<T>> variables;
    double avg;
    double sd;
    void statistics(const std::vector<SummaryStatistics<T>> & vars) {
        double sum = 0.0, variance = 0.0;
        for (auto item : vars) {
            sum += item.avg;
            variance += pow(item.sd, 2);
        }
        avg = sum;
        sd = sqrt(variance);
    };
    std::string to_string() const {
        std::string s;
        s += std::to_string(avg);
        s += ", " + std::to_string(sd);
        return s;
    };
};

/**
 * Given data, find all the relevant statistics.
 */
template<typename T>
SummaryStatistics<T> statistics(const std::vector<T> & data) {
    const auto min = std::min_element(data.begin(), data.end());
    const auto max = std::max_element(data.begin(), data.end());
    double avg = 1.0 * std::accumulate(data.begin(), data.end(), 0)/data.size();
    std::vector<double> diff;
    for (const auto d : data) {
        diff.push_back(pow(d - avg, 2));
    }
    double sd = sqrt(1.0 * std::accumulate(diff.begin(), diff.end(), 0) / data.size() ) ;
    SummaryStatistics<T> ss;
    ss.min = *min;
    ss.max = *max;
    ss.avg = avg;
    ss.sd = sd;
    return ss;
}

#endif
