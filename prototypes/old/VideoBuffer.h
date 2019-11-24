#ifndef VIDEOBUFFER_H
#define VIDEOBUFFER_H

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace cv
{

class Mat;

} // cv

class VideoBuffer
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

#endif // VIDEOBUFFER_H
