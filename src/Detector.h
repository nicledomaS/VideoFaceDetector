#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

#include "opencv2/core/types.hpp"

namespace cv
{

class CascadeClassifier;
class Mat;

} // cv

namespace detect_faces
{

class Detector : private boost::noncopyable
{
public:
    explicit Detector(
            const std::string &fileName,
            double scaleFactor = 1.1,
            int minNeighbors = 3,
            int flags = 0,
            cv::Size minSize = cv::Size(),
            cv::Size maxSize = cv::Size());

    void detectFaces(
            std::vector<cv::Rect>& faces,
            const cv::Mat& frame);

private:
    std::shared_ptr<cv::CascadeClassifier> m_faceCascade;
    double m_scaleFactor;
    int m_minNeighbors;
    int m_flags;
    cv::Size m_minSize;
    cv::Size m_maxSize;
};

} // detect_faces
