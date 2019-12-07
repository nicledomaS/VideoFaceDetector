#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

#include "Detector.h"

namespace detect_faces
{

Detector::Detector(
        const std::string& fileName,
        double scaleFactor,
        int minNeighbors,
        int flags,
        cv::Size minSize,
        cv::Size maxSize)
    : m_faceCascade(std::make_shared<cv::CascadeClassifier>(fileName)),
      m_scaleFactor(std::move(scaleFactor)),
      m_minNeighbors(std::move(minNeighbors)),
      m_flags(std::move(flags)),
      m_minSize(std::move(minSize)),
      m_maxSize(std::move(maxSize))
{
}

void Detector::detectFaces(std::vector<cv::Rect>& faces, const cv::Mat& frame)
{
    cv::Mat frame_gray;
    cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    m_faceCascade->detectMultiScale(
                frame_gray,
                faces,
                m_scaleFactor,
                m_minNeighbors,
                m_flags,
                m_minSize,
                m_maxSize);
}

} // detect_faces


