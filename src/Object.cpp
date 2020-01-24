#include <iostream>
#include <stdexcept>
#include <future>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "Object.h"
#include "Detector.h"
#include "VideoBuffer.h"
#include "VideoFrame.h"

Object::Object(
        const std::string& fileName,
        const std::shared_ptr<VideoBuffer>& videobuffer)
    : m_used(false),
      m_detector(std::make_unique<detect_faces::Detector>(fileName)),
      m_videobuffer(videobuffer)
{
}

Object::~Object()
{
}

void Object::start(const std::shared_ptr<VideoFrame>& videoFrame)
{
    if(videoFrame)
    {
        std::vector<cv::Rect> faces;
        m_detector->detectFaces(faces, videoFrame->frame);

        for (const auto& face : faces)
        {
            cv::Point p1(face.x, face.y);
            cv::Point p2(face.x + face.width, face.y + face.height);

            rectangle(videoFrame->frame, p1, p2, cv::Scalar( 255, 0, 255 ));
        }

        m_videobuffer->push(videoFrame);
    }
    m_used = false;
}

void Object::setUsed(bool used)
{
    m_used = used;
}

bool Object::used() const
{
    return m_used;
}
