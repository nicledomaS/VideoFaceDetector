#include "Application.h"

#include <iostream>
#include <future>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "DetectFaceHandler.h"
#include "VideoBuffer.h"
#include "VideoFrame.h"

namespace core
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

Application::Application(const cv::CommandLineParser &parser)
    : m_videoCapture(std::make_unique<cv::VideoCapture>()),
      m_videobuffer(std::make_shared<VideoBuffer>()),
      m_videoHandler(
          std::make_unique<DetectFaceHandler>(
              m_videobuffer, parser.get<std::string>("face_cascade")))
{
    int cam = parser.get<int>("camera");
    auto apiRef = parser.get<int>("apiPreference");
    open(*m_videoCapture, cam, cv::VideoCaptureAPIs(apiRef));
}

Application::~Application()
{
}

void Application::run()
{
    if (!m_videoCapture->isOpened())
    {
        std::cout << "Error opening video capture" << std::endl;
        return;
    }

    auto last = std::chrono::system_clock::now();

    cv::Mat frame;
    while(m_videoCapture->read(frame))
    {
        m_videoHandler->handle(frame);

        auto videoFrame = m_videobuffer->pop();

        if(videoFrame && videoFrame->time > last)
        {
            cv::imshow("Output", videoFrame->frame);

            last = videoFrame->time;
            auto key = cv::waitKey(1);

            if (key == 27/*ESC*/)
            {
                break;
            }
        }
    }
}

} // core

