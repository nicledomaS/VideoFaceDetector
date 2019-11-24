#include <iostream>

#include "opencv2/highgui.hpp"

#include "OpenCVReader.h"
#include "VideoBuffer.h"

OpenCVReader::OpenCVReader(int cameraIdx, std::shared_ptr<VideoBuffer> videoBuffer)
    : m_videoCapture(std::make_unique<cv::VideoCapture>()),
      m_videoBuffer(std::move(videoBuffer))
{
    m_videoCapture->open(cameraIdx + cv::CAP_DSHOW);
}

void OpenCVReader::handle()
{
    if (!m_videoCapture->isOpened())
    {
        std::cout << "--(!)Error opening video capture" << std::endl;
        return;
    }

    cv::Mat frame;
    while (m_videoCapture->read(frame))
    {
        m_videoBuffer->push(std::make_shared<cv::Mat>(frame.clone()));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
