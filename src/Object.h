#pragma once

#include <atomic>
#include <thread>

#include <boost/noncopyable.hpp>

namespace cv
{

class Mat;

} // cv

namespace detect_faces
{

class Detector;

} // detect_faces

class VideoBuffer;
struct VideoFrame;

class Object : private boost::noncopyable
{
public:
    Object(
            const std::string& fileName,
            const std::shared_ptr<VideoBuffer>& videobuffer);
    ~Object();

    void start(const std::shared_ptr<VideoFrame>& videoFrame);

    void setUsed(bool used);
    bool used() const;

private:
    std::atomic_bool m_used;
    std::unique_ptr<detect_faces::Detector> m_detector;
    std::shared_ptr<VideoBuffer> m_videobuffer;
};

