#pragma once

#include <memory>

#include <boost/noncopyable.hpp>

namespace cv
{

class Mat;

} //cv

namespace core
{

class VideoHandler : private boost::noncopyable
{
public:
    virtual ~VideoHandler() = default;

    virtual void handle(const cv::Mat& frame) = 0;
};

} // core
