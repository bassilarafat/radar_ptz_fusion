#include "radar_source.hpp"
#include "simulated_radar_source.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>

int main() {

    std::unique_ptr<IRadarSource> radar =
        std::make_unique<SimulatedRadarSource>();

    for (int cycle = 1; cycle <= 5; ++cycle) {

        const auto detections =
            radar->readDetections();

        std::cout << "Cycle " << cycle << "\n";

        for (const auto& d : detections) {

            if (!isValidDetection(d)) {
                std::cerr << "Invalid radar detection\n";
                continue;
            }

            std::cout
                << std::fixed
                << std::setprecision(1)
                << "  ID=" << d.target_id
                << " Range=" << d.range_m << " m"
                << " Azimuth=" << d.azimuth_deg << " deg"
                << " Height(MSL)=";

            if (d.height_msl_m) {
                std::cout << *d.height_msl_m << " m";
            } else {
                std::cout << "N/A";
            }

            std::cout << " Timestamp=" << d.timestamp_ms
                << " ms\n";
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(200)
        );
    }

    return 0;
}
