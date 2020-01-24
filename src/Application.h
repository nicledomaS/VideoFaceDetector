#pragma once

#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

namespace cv
{

class CommandLineParser;
class VideoCapture;

} // cv

class VideoBuffer;

namespace core
{

class VideoHandler;

class Application : private boost::noncopyable
{
public:
    Application(int cameraId,
            int apiRef,
            const std::string& faceCascasdConfig,
            int cascadeCount);

    Application::Application(
            const std::string& fileName,
            int apiRef,
            const std::string &faceCascasdConfig,
            int cascadeCount);
    ~Application();

    void run();

private:
    std::unique_ptr<cv::VideoCapture> m_videoCapture;
    std::shared_ptr<VideoBuffer> m_videobuffer;
    std::unique_ptr<VideoHandler> m_videoHandler;
};

} // core
