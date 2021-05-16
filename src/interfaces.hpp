#include "metrics.hpp"

#ifndef __INTERFACES__
#define __INTERFACES__

#include <vector>
#include <string>

class IHandler {
    public:
        virtual void handle(const std::vector<Metrics> & metricsList, 
                const std::string & filename) = 0;
        virtual ~IHandler() {};
};

#endif
