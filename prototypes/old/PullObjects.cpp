#include <iostream>
#include <ctime>
#include <iomanip>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "PullObjects.h"
#include "Object.h"

PullObjects::PullObjects(const std::string &fileName)
    : m_fileName(fileName)
{
    thrd = std::thread([this]()
    {
        cv::VideoWriter video;
        cv::Size frame_size(640, 480);
        std::string pipeline = "appsrc ! videoconvert ! video/x-raw, format=(string)RGBA ! matroskamux ! filesink location=c:\\test.mkv";
        auto param = "appsrc ! videoconvert ! "
                "x264enc noise-reduction=10000 speed-preset=ultrafast tune=zerolatency ! "
                "rtph264pay config-interval=1 pt=96 !"
                "tcpserversink host=192.168.1.54 port=5000 sync=false";
        video.open(pipeline, cv::CAP_FFMPEG, 0, 20, frame_size, true);

        while(true)
        {
            cv::Mat frame;
            {
                std::unique_lock<std::mutex> lock(mtx);
                condVar.wait(lock, [this](){return !frames.empty();});
                frame = frames.front().clone();
                frames.pop();
            }
            video.write(frame);
        }
    });
}

PullObjects::~PullObjects()
{
    if(thrd.joinable())
    {
        thrd.join();
    }
}

std::shared_ptr<Object> PullObjects::createNewObject()
{
    auto newObject = std::make_shared<Object>(
                m_fileName,
                [this](const std::shared_ptr<cv::Mat>& frame, cv::CascadeClassifier& faceCascade)
    {
        detect(frame, faceCascade);
    });
    m_objects.push_back(newObject);

    return newObject;
}

std::shared_ptr<Object> PullObjects::getFree() const
{
    for(const auto& object : m_objects)
    {
        if(!object->used())
        {
            return object;
        }
    }
    return nullptr;
}

void PullObjects::detect(const std::shared_ptr<cv::Mat> &frame, cv::CascadeClassifier& faceCascade)
{
    cv::Mat frame_gray;
    cvtColor( *frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    std::vector<cv::Rect> faces;

    auto beginTime = std::chrono::system_clock::now();

    faceCascade.detectMultiScale( frame_gray, faces,  1.1, 2, 0, cv::Size(80, 80));

    auto endTime = std::chrono::system_clock::now();

    auto in_time_t = std::chrono::system_clock::to_time_t(beginTime);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%X")
       << ":"
       << std::to_string(in_time_t % 1000);

    std::cout << "Thread id: "
              << std::this_thread::get_id()
              << " "
              << "Begin time: "
              << ss.str()
              << std::endl
              << "detected time: "
              << std::to_string(
                     std::chrono::duration_cast<std::chrono::milliseconds>(
                         endTime - beginTime).count())
              << std::endl;



    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point p1(faces[i].x, faces[i].y);
        cv::Point p2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

        rectangle(*frame, p1, p2, cv::Scalar( 255, 0, 255 ));
    }


    std::lock_guard<std::mutex> lock(mtx);
    frames.push(frame->clone());
    condVar.notify_one();
}
