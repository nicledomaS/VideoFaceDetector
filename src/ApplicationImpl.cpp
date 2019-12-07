#include <iostream>
#include <thread>
#include <chrono>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "ApplicationImpl.h"
#include "OpenCVReader.h"
#include "VideoBuffer.h"
#include "Detector.h"

namespace core
{

namespace
{

std::unique_ptr<video_stream::VideoReader> createVideoReader(
        std::shared_ptr<VideoBuffer> videoBuffer,
        const cv::CommandLineParser& parser)
{
    return std::make_unique<video_stream::OpenCVReader>(
                std::move(videoBuffer),
                parser.get<int>("camera"),
                cv::VideoCaptureAPIs(parser.get<int>("apiPreference")));
}

std::unique_ptr<detect_faces::Detector> createDetector(
        const cv::CommandLineParser& parser)
{
    return std::make_unique<detect_faces::Detector>(
                parser.get<std::string>("face_cascade"));
}

} // anonymous

ApplicationImpl::ApplicationImpl(const cv::CommandLineParser& parser)
    : m_videoBuffer(std::make_shared<VideoBuffer>()),
      m_videoReader(createVideoReader(m_videoBuffer, parser)),
      m_detector(createDetector(parser))
{
}

void ApplicationImpl::run()
{
    std::cout << "Run application" << std::endl;

    std::thread videoReaderThread([this]()
    {
        m_videoReader->handle();
    });

    while(true)
    {
        auto frame = m_videoBuffer->pop();

//        std::vector<cv::Rect> faces;
//        m_detector->detectFaces(faces, *frame);

//        for (const auto& faceRect : faces)
//        {
//            cv::Point p1(faceRect.x, faceRect.y);
//            cv::Point p2(faceRect.x + faceRect.width, faceRect.y + faceRect.height);
//            rectangle(*frame, p1, p2, cv::Scalar( 255, 0, 255 ));
//        }

        cv::imshow("Output", *frame);

        int key = cv::waitKey(1);
        if (key == 27/*ESC*/)
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    if(videoReaderThread.joinable())
    {
        videoReaderThread.join();
    }
}

} // core


