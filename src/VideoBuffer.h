#pragma once

#include <boost/noncopyable.hpp>

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace cv
{

class Mat;

} // cv

class VideoBuffer : private boost::noncopyable
{
public:
    VideoBuffer();

    void push(const std::shared_ptr<cv::Mat>& item);
    std::shared_ptr<cv::Mat> pop();

private:
    std::mutex m_mtx;
    std::condition_variable m_notEmpty;
    std::queue<std::shared_ptr<cv::Mat>> m_buffer;
};
