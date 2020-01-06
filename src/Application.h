#pragma once

#include <memory>

#include <boost/noncopyable.hpp>

namespace cv
{

class CommandLineParser;
class VideoCapture;

}

class VideoBuffer;

namespace core
{

class VideoHandler;

class Application : private boost::noncopyable
{
public:
    Application(const cv::CommandLineParser& parser);
    ~Application();

    void run();

private:
    std::unique_ptr<cv::VideoCapture> m_videoCapture;
    std::shared_ptr<VideoBuffer> m_videobuffer;
    std::unique_ptr<VideoHandler> m_videoHandler;
};

} // core
