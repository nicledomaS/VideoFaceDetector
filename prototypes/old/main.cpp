#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "PullObjects.h"
#include "Object.h"
#include "OpenCVReader.h"
#include "VideoBuffer.h"

using namespace std;
using namespace cv;

//std::mutex mtx;
//std::condition_variable condVar;
//std::queue<Mat> frames;

/** @function main */
int main( int argc, const char** argv )
{
    CommandLineParser parser(argc, argv,
                             "{help h||}"
                             "{face_cascade|../../data/lbpcascades/lbpcascade_frontalface.xml|Path to face cascade.}"
                             "{eyes_cascade|../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|Path to eyes cascade.}"
                             "{camera|0|Camera device number.}");

    parser.about( "\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
                  "You can use Haar or LBP features.\n\n" );
    parser.printMessage();

    String face_cascade_name = parser.get<String>("face_cascade");
//    String eyes_cascade_name = parser.get<String>("eyes_cascade");

    PullObjects pull(face_cascade_name);
    pull.createNewObject();
    pull.createNewObject();


    auto buffer = make_shared<VideoBuffer>();

    std::thread thrd([&buffer, &pull]()
    {
        size_t count = 0;
        while(true)
        {
            if(auto object = pull.getFree())
            {
                auto item = buffer->pop();
                object->start(item);
                ++count;

                std::cout << "Item count: " << count << std::endl;
            }
        }
    });

    int camera_device = parser.get<int>("camera");
    auto videoReader = std::make_shared<OpenCVReader>(camera_device, buffer);
    videoReader->handle();

    if(thrd.joinable())
    {
        thrd.join();
    }
    return 0;
}
