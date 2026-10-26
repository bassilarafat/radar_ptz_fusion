
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "cnpy.h"

// One radar point in 3D space
struct RadarPoint {
    double x;
    double y;
    double z;
};


struct RadarMeasurement {
    double range;
    double azimuth;
    double elevation;
};

RadarMeasurement convertToRadar(
    const RadarPoint& point
) {
    // Reverse MMAUD exported coordinate mapping
    double x = point.z;
    double y = -point.x;
    double z = -point.y;

    constexpr double RAD_TO_DEG =
        180.0 / 3.14159265358979323846;

    double horizontal = std::hypot(x, y);

    double range = std::hypot(horizontal, z);

    double azimuth =
        std::atan2(y, x) * RAD_TO_DEG;

    double elevation =
        std::atan2(z, horizontal) * RAD_TO_DEG;

    return {range, azimuth, elevation};
}

// Convert array values into radar points
template <typename T>
std::vector<RadarPoint> extractPoints(
    const cnpy::NpyArray& array
) {
    const T* data = array.data<T>();

    size_t rows = array.shape[0];
    size_t cols = array.shape[1];

    std::vector<RadarPoint> points;
    points.reserve(rows);

    for (size_t i = 0; i < rows; ++i) {
        size_t index = i * cols;

        RadarPoint point{
            static_cast<double>(data[index]),
            static_cast<double>(data[index + 1]),
            static_cast<double>(data[index + 2])
        };

        points.push_back(point);
    }

    return points;
}

// Load a NumPy radar file
std::vector<RadarPoint> loadRadarFile(
    const std::string& filename
) {
    cnpy::NpyArray array = cnpy::npy_load(filename);

    if (array.shape.size() != 2 || array.shape[1] < 3) {
        throw std::runtime_error(
            "Expected a 2D array with at least 3 columns"
        );
    }

    if (array.fortran_order) {
        throw std::runtime_error(
            "Fortran-order arrays are not supported"
        );
    }

    std::cout << "Rows: " << array.shape[0] << '\n';
    std::cout << "Columns: " << array.shape[1] << '\n';
    std::cout << "Bytes per value: " << array.word_size << '\n';

    // Assumes the file contains floating-point values
    if (array.word_size == 4) {
        return extractPoints<float>(array);
    }

    if (array.word_size == 8) {
        return extractPoints<double>(array);
    }

    throw std::runtime_error(
        "Unsupported numeric value size"
    );
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0]
                  << " file.npy\n";
        return 1;
    }

    try {
        std::vector<RadarPoint> points =
            loadRadarFile(argv[1]);

        // need to to return the duplicated data

        int duplicates = 0;

        for(size_t i=1 ; i < points.size() ; i++){
            for(size_t j = 0 ; j < i; j++){
                if(
                    std::abs(points[i].x - points[j].x) < 0.000001 &&
                    std::abs(points[i].y - points[j].y) < 0.000001 &&
                    std::abs(points[i].z - points[j].z) < 0.000001
                ){
                    duplicates++;
                    break;
                }
            }
        }

        std::cout<<"duplicates : " << duplicates << '\n';


        std::cout << "Total points: "
                  << points.size() << '\n';

        size_t count = std::min(
            points.size(), size_t{5}
        );
        std::cout << std::fixed << std::setprecision(2);

        for (size_t i = 0; i < count; ++i) {


            RadarMeasurement m =
                convertToRadar(points[i]);

            std::cout << "Point " << i
                      << " Range=" << m.range
                      << " Azimuth=" << m.azimuth
                      << " deg Elevation=" << m.elevation
                      << "deg\n";
        }

    } catch (const std::exception& error) {
        std::cerr << "Error: "
                  << error.what() << '\n';
        return 1;
    }

    return 0;
}
