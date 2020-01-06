#include <memory>

#include "opencv2/highgui.hpp"

#include "Application.h"

int main(int argc, char** argv)
{
    cv::CommandLineParser parser(
                argc,
                argv,
                "{help h||}"
                "{face_cascade|C:/Users/yuriy/data/lbpcascades/lbpcascade_frontalface.xml|Path to face cascade.}"
                "{camera|0|Camera device number.}"
                "{apiPreference|0|Select preferred API for a capture object.}");

    parser.about( "\nThis program demonstrates using the cv::CascadeClassifier class to detect objects Face in a video stream.\n"
                  "You can use Haar or LBP features.\n\n" );
    parser.printMessage();

    std::make_unique<core::Application>(parser)->run();

    return 0;
}
