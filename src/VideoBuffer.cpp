#include "VideoBuffer.h"
#include "VideoFrame.h"

VideoBuffer::VideoBuffer()
{
}

void VideoBuffer::push(const std::shared_ptr<VideoFrame> &item)
{
    std::lock_guard<std::mutex> lock(m_mtx);
    m_buffer.push(item);
//    m_notEmpty.notify_one();
}

std::shared_ptr<VideoFrame> VideoBuffer::pop()
{
    std::unique_lock<std::mutex> lock(m_mtx);
//    m_notEmpty.wait(lock, [this]()
//    {
//        return !m_buffer.empty();
//    });
    if(m_buffer.empty())
    {
        return nullptr;
    }

    auto item = m_buffer.front();
    m_buffer.pop();
    return item;
}
