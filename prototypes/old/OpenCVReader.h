#ifndef OPENCVREADER_H
#define OPENCVREADER_H

#include <memory>
#include <string>

#include "VideoReader.h"

namespace cv
{

class VideoCapture;

} // cv

class VideoBuffer;

class OpenCVReader : public VideoReader
{
public:
    OpenCVReader(int cameraIdx, std::shared_ptr<VideoBuffer> videoBuffer);

    // VideoReader interface
    void handle() override;

private:
    std::unique_ptr<cv::VideoCapture> m_videoCapture;
    std::shared_ptr<VideoBuffer> m_videoBuffer;
};

#endif // OPENCVREADER_H
