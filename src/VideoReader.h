#pragma once

#include <boost/noncopyable.hpp>

namespace video_stream
{

class VideoReader : private boost::noncopyable
{
public:
    virtual ~VideoReader() = default;

    virtual void handle() = 0;
};

} // video_stream
