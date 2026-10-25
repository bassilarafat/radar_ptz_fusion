#include "simulated_radar_source.hpp"
#include <chrono>
#include <cmath>

// Function to get current time 
std::uint64_t nowMilliseconds()
{
    auto now = std::chrono::system_clock::now();

    auto duration = now.time_since_epoch();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    return static_cast<std::uint64_t>(ms.count());
}


// Simulated Radar
std::vector<RadarDetection>SimulatedRadarSource::readDetections()
{
    // 1. Simulation step
    const double t = step_;
    step_++;
    // 2. Current time
    std::uint64_t time_ms = nowMilliseconds();

    // 3. First target
    RadarDetection target1;

    target1.target_id = 101;
    target1.range_m = 1500.0 + 10.0 * t;

    double azimuth = 45 + 2 * t;
    if (azimuth >= 360) {
        azimuth = azimuth - 360;
    }
    target1.azimuth_deg = azimuth;

    target1.height_msl_m = 300;
    target1.timestamp_ms = time_ms;

    // 4. Second target
    RadarDetection target2;

    target2.target_id = 202;
    target2.range_m = 1000.0 + 10.0 * t;

    double azimuth2 = 90 + 2 * t;
    if (azimuth2 >= 360) {
        azimuth2 = azimuth2 - 360;
    }
    target2.azimuth_deg = azimuth2;

    target2.height_msl_m = 200;

    target2.timestamp_ms = time_ms;

    // 5. Return targets
    return {target1, target2};
}
