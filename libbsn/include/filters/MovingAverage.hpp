#ifndef MOVINGAVERAGE_HPP
#define MOVINGAVERAGE_HPP

#include <list>
#include <string>
#include <array>
#include <stdint.h>
#include <sstream>

namespace bsn {
    namespace filters {

        class MovingAverage { 
            public:
                MovingAverage(int32_t);

                MovingAverage(const MovingAverage & /*obj*/);
                MovingAverage &operator=(const MovingAverage & /*obj*/);

                double getValue(std::string);
                void insert(double, std::string);

                const std::string toString() const;

                uint32_t getRange() const;
                void setRange(const uint32_t);
            
            private:
                uint32_t range;
                double computedAverage;
                double lastInserted;
                std::array<std::list<double>, 5> buffer;
                
        };        

    }
}
#endif 