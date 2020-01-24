#pragma once

#include <boost/noncopyable.hpp>

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

struct VideoFrame;

class VideoBuffer : private boost::noncopyable
{
public:
    VideoBuffer();

    void push(const std::shared_ptr<VideoFrame>& item);
    std::shared_ptr<VideoFrame> pop();

private:
    std::mutex m_mtx;
    std::condition_variable m_notEmpty;
    std::queue<std::shared_ptr<VideoFrame>> m_buffer;
};
