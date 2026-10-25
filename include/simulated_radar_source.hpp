#pragma once 

#include "radar_source.hpp"
#include <cstdint>

class SimulatedRadarSource final: public IRadarSource {

    public:
        std::vector<RadarDetection>readDetections() override;

    private:    
        std::uint64_t step_ = 0 ; 

};
