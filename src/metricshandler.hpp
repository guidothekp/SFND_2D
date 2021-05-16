/**
 * Generate all the required metrics using the observed values.
 */

#include <vector>
#include "metrics.hpp"
#include "keypoints_handler.hpp"
#include "descriptormatcher_handler.hpp"
#include "timer_results_handler.hpp"

class metricsHandler {
    private:
        IHandler* kph = new keypointsHandler;
        IHandler* mph = new descriptorMatchHandler;
        IHandler* trh = new timerResultsHandler;

        const std::string keypointsResultsFile;
        const std::string matchesResultsFile;
        const std::string timerResultsFile;
        const std::vector<Metrics> metricsList;
    public:
        void handle();
        metricsHandler(const std::vector<Metrics> & metricsList, 
                const std::string & keypointsResultsFile,
                const std::string & matchesResultsFile,
                const std::string & timerResultsFile) 
            : metricsList(metricsList), 
            keypointsResultsFile(keypointsResultsFile),
            matchesResultsFile(matchesResultsFile),
            timerResultsFile(timerResultsFile) {};
        ~metricsHandler() {
            delete kph;
        }
};


void metricsHandler::handle() {
    kph->handle(metricsList, keypointsResultsFile);
    mph->handle(metricsList, matchesResultsFile);
    trh->handle(metricsList, timerResultsFile);
}

