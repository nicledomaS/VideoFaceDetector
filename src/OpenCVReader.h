#pragma once

#include <memory>
#include <string>

#include "opencv2/videoio.hpp"

#include "VideoReader.h"

class VideoBuffer;

namespace video_stream
{

class OpenCVReader : public VideoReader
{
public:
    OpenCVReader(
            std::shared_ptr<VideoBuffer> videoBuffer,
            int cameraIdx,
            cv::VideoCaptureAPIs apiPreference = cv::CAP_ANY);
    OpenCVReader(std::shared_ptr<VideoBuffer> videoBuffer,
            const std::string& parameters,
            cv::VideoCaptureAPIs apiPreference = cv::CAP_ANY);

    // VideoReader interface
    void handle() override;

private:
    std::shared_ptr<VideoBuffer> m_videoBuffer;
    std::unique_ptr<cv::VideoCapture> m_videoCapture;
};

} // video_stream
