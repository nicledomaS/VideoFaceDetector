#include <iostream>

#include "opencv2/highgui.hpp"

#include "OpenCVReader.h"
#include "VideoBuffer.h"

namespace video_stream
{

namespace
{

template<typename T>
bool open(
        cv::VideoCapture& videoCapture,
        T parameters,
        cv::VideoCaptureAPIs apiPreference)
{
    return videoCapture.open(parameters, apiPreference);
}

} // anonymous

OpenCVReader::OpenCVReader(
        std::shared_ptr<VideoBuffer> videoBuffer,
        int cameraIdx,
        cv::VideoCaptureAPIs apiPreference)
    : m_videoBuffer(std::move(videoBuffer)),
      m_videoCapture(std::make_unique<cv::VideoCapture>())
{
    open(*m_videoCapture, cameraIdx, apiPreference);
}

OpenCVReader::OpenCVReader(
        std::shared_ptr<VideoBuffer> videoBuffer,
        const std::string &parameters,
        cv::VideoCaptureAPIs apiPreference)
    : m_videoBuffer(std::move(videoBuffer)),
      m_videoCapture(std::make_unique<cv::VideoCapture>())
{
    open(*m_videoCapture, parameters, apiPreference);
}

void OpenCVReader::handle()
{
    if (!m_videoCapture->isOpened())
    {
        std::cout << "--(!)Error opening video capture" << std::endl;
        return;
    }

    cv::Mat currentFrame;
    while (m_videoCapture->read(currentFrame))
    {
        m_videoBuffer->push(std::make_shared<cv::Mat>(currentFrame.clone()));
//        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

} // video_stream
