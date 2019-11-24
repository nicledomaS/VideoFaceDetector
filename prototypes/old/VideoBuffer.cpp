#include "VideoBuffer.h"

VideoBuffer::VideoBuffer()
{

}

void VideoBuffer::push(const std::shared_ptr<cv::Mat> &item)
{
    std::lock_guard<std::mutex> lock(m_mtx);
    m_buffer.push(item);
    m_notEmpty.notify_one();
}

std::shared_ptr<cv::Mat> VideoBuffer::pop()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_notEmpty.wait(lock, [this]()
    {
        return !m_buffer.empty();
    });

    auto item = m_buffer.front();
    m_buffer.pop();
    return item;
}
