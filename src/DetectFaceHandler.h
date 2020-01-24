#pragma once

#include <vector>
#include <thread>

#include "VideoHandler.h"

class VideoBuffer;
class Object;

namespace core
{

class ThreadPool;

class DetectFaceHandler : public VideoHandler
{
public:
    DetectFaceHandler(
            const std::shared_ptr<VideoBuffer>& videobuffer,
            const std::string& fileName,
            size_t countObjects = 2);
    ~DetectFaceHandler();

    // VideoHandler interface
    void handle(const cv::Mat& frame) override;

private:
    std::shared_ptr<Object> createNewObject();
    std::shared_ptr<Object> getFree();

private:
    std::shared_ptr<VideoBuffer> m_videobuffer;
    std::string m_fileName;
    size_t m_countObjects;
    std::vector<std::shared_ptr<Object>> m_objects;
    std::unique_ptr<ThreadPool> m_threadPool;
};

} // core
