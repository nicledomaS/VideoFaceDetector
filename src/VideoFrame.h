#pragma once

#include <memory>
#include <chrono>

#include "opencv2/core/mat.hpp"

struct VideoFrame
{
    cv::Mat frame;
    std::chrono::system_clock::time_point time;
};

