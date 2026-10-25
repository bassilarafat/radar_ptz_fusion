//radar detection data 

#pragma once

#include <cmath>
#include<cstdint>
#include<optional>

struct RadarDetection{
    std::uint32_t target_id;
    double azimuth_deg;
    double range_m;
    std::optional<double> height_msl_m;
    std::uint64_t timestamp_ms;
};


//declare function to validate the data 
inline bool isValidDetection(const RadarDetection& d)
{

    if(!std::isfinite(d.range_m)||
        !std::isfinite(d.azimuth_deg))
    
        return false;

    if(d.range_m <=0)
        return false;

    if (d.azimuth_deg < 0 || d.azimuth_deg >= 360)
        return false;    

    return true;
}


