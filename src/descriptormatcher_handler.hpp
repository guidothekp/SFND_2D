#include "interfaces.hpp"
#include "metrics.hpp"

struct DescriptorMatchMetrics {
    std::string detectorType;
    std::string descriptorType;
    std::string matcherSubType;
    bool crossCheck;
    SummaryStatistics<int> matchStatistics;
};

class descriptorMatchHandler : public IHandler {
    public:
        ~descriptorMatchHandler() {};
        void handle(const std::vector<Metrics> & metricsList,
                const std::string & filename);
};

namespace dsmUtils {
    std::vector<DescriptorMatchMetrics> prepareData(
            const std::vector<Metrics> & metricsList) {
        std::vector<DescriptorMatchMetrics> list;
        for (Metrics m : metricsList) {
            DescriptorMatchMetrics dmm;
            dmm.matchStatistics = statistics(m.matchCount);
            dmm.detectorType = m.detectorType;
            dmm.descriptorType = m.descriptorType;
            dmm.matcherSubType = m.matcherSubType;
            list.push_back(dmm);
        }
        std::sort(list.begin(), list.end(),
                [](const DescriptorMatchMetrics & a, 
                    const DescriptorMatchMetrics & b) {
                return a.matchStatistics.avg > b.matchStatistics.avg;
                });
        return list;
    }

    std::string makeHeaders() {
        std::string str;
        str += "KEYPOINT_DETECTOR";
        str += ", DESCRIPTOR";
        str += ", MATCHER_SUBTYPE";
        str += ", CROSSCHECK";
        const std::vector<std::string> types { /*"MIN", "MAX", */ "MEAN", "SD"};
        const std::vector<std::string> traits {"MATCHES"};
        for (auto trait : traits) 
            for (auto type : types) 
                str = str + ", " + trait + "_" + type;
        return str;
    }

    std::string to_string(const DescriptorMatchMetrics & dmm) {
        std::string str;
        str += dmm.detectorType;
        str += ", " + dmm.descriptorType;
        str += ", " + dmm.matcherSubType;
        str += ", " + std::to_string(dmm.crossCheck);
        str += ", " + dmm.matchStatistics.to_string();
        return str;
    }

    std::vector<std::string> convertToStrings(
            const std::vector<DescriptorMatchMetrics> & dmms) {
        std::vector<std::string> strings {makeHeaders()};
        for (DescriptorMatchMetrics dmm : dmms) {
            strings.push_back(to_string(dmm));
        }
        return strings;
    }

    void printDescriptorMatchMetrics(
            const std::vector<DescriptorMatchMetrics> & dmms,
            const std::string & filename) {
        std::vector<std::string> strings = convertToStrings(dmms);
        std::ofstream out;
        out.open(filename);
        for (auto string : strings) {
            out << string << std::endl;
        }
        out.close();
    }
};

void descriptorMatchHandler::handle(const std::vector<Metrics> & metricsList,
        const std::string & filename) {
    std::vector<DescriptorMatchMetrics> dmms = dsmUtils::prepareData(metricsList);
    dsmUtils::printDescriptorMatchMetrics(dmms, filename);
}
