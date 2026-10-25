#pragma once

// generalize radar types sources 
// simulated data , hdlc data 

#include "radar_detection.hpp"
#include<vector>

class IRadarSource {
public:
//virtual بتخلي البرنامج يختار الدالة حسب نوع الكائن الحقيقي، مش نوع المؤشر أو المرجع المستخدم للوصول إليه.
    virtual ~IRadarSource() =default;

    virtual std::vector<RadarDetection>readDetections()=0;

};

