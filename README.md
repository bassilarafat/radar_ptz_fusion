# Radar + PTZ Fusion Starter (C++17 / Linux)

This is **Phase 1 only**: a simulated radar measurement source and ENU coordinate conversion. It does not connect to a real radar or camera and does not implement sensor fusion yet.

## Assumptions
- Slant range in meters.
- Azimuth degrees clockwise from north.
- Height in meters **relative to the radar**, not altitude above sea level.
- ENU axes: East, North, Up; radar at origin.
- Flat local tangent plane; no Earth-curvature or refraction compensation.

## Build and run
```bash
sudo apt update
sudo apt install -y build-essential cmake
cmake -S . -B build
cmake --build build -j
./build/radar_demo
```

## Next stages
1. Replace the sample vector with timestamped decoded radar messages from your actual transport and protocol.
2. Establish clock synchronization, radar/camera surveyed poses, and calibrated camera intrinsics.
3. Acquire RTSP video and read PTZ status. Validate camera optical-axis conventions.
4. Compute camera bearing/elevation observations from detections.
5. Associate measurements by timestamp, uncertainty and geometry; implement EKF and evaluate with logged ground truth.

Never send physical PTZ commands until device-specific limits and safety constraints are validated.
