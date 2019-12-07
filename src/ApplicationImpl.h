#pragma once

#include <memory>

#include "Application.h"

class VideoBuffer;

namespace cv
{

class CommandLineParser;

}

namespace detect_faces
{

class Detector;

} // detect_faces

namespace video_stream
{

class VideoReader;

} // video_stream

namespace core
{

class ApplicationImpl : public Application
{
public:
    ApplicationImpl(const cv::CommandLineParser& parser);

    // Application interface
    void run() override;

public:
    std::shared_ptr<VideoBuffer> m_videoBuffer;
    std::unique_ptr<video_stream::VideoReader> m_videoReader;
    std::unique_ptr<detect_faces::Detector> m_detector;
};

} // core
