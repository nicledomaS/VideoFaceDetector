#include <iostream>

#include "DetectFaceHandler.h"
#include "VideoBuffer.h"
#include "VideoFrame.h"
#include "Object.h"
#include "ThreadPool.h"

namespace core
{

DetectFaceHandler::DetectFaceHandler(
        const std::shared_ptr<VideoBuffer>& videobuffer,
        const std::string& fileName,
        size_t countObjects)
    : m_videobuffer(videobuffer),
      m_fileName(fileName),
      m_countObjects(countObjects),
      m_threadPool(std::make_unique<ThreadPool>(countObjects))
{
}

DetectFaceHandler::~DetectFaceHandler()
{
}

void DetectFaceHandler::handle(const cv::Mat& frame)
{
    try
    {
        auto detectObject = getFree();
        if(detectObject)
        {
            auto newVideoFrame = std::make_shared<VideoFrame>();
            newVideoFrame->frame = frame.clone();
            newVideoFrame->time = std::chrono::system_clock::now();

            detectObject->setUsed(true);
            auto task = [detectObject, newVideoFrame]()
            {
                detectObject->start(newVideoFrame);
            };

            m_threadPool->submit(task);
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

std::shared_ptr<Object> DetectFaceHandler::createNewObject()
{
    auto newObject = std::make_shared<Object>(m_fileName, m_videobuffer);
    m_objects.push_back(newObject);

    return newObject;
}

std::shared_ptr<Object> DetectFaceHandler::getFree()
{
    for(const auto& object : m_objects)
    {
        if(!object->used())
        {
            return object;
        }
    }

    return m_objects.size() < m_countObjects ? createNewObject() : nullptr;
}

} // core
