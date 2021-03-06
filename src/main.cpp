#include <memory>

#include "opencv2/highgui.hpp"

#include "Application.h"

constexpr auto FileName = "FileName";
constexpr auto CameraId = "CameraId";
constexpr auto ApiReference = "ApiReference";
constexpr auto FaceCascade = "FaceCascade";
constexpr auto CascadeCount = "CascadeCount";

std::shared_ptr<core::Application> createApplication(
        const cv::CommandLineParser& parser)
{
    auto fileName = parser.get<std::string>(FileName);
    auto cameraId = parser.get<int>(CameraId);
    auto apiRef = parser.get<int>(ApiReference);
    auto faceCascade = parser.get<std::string>(FaceCascade);
    auto cascadeCount = parser.get<int>(CascadeCount);

    return fileName.empty() ?
                std::make_unique<core::Application>(cameraId, apiRef, faceCascade, cascadeCount) :
                std::make_unique<core::Application>(fileName, apiRef, faceCascade, cascadeCount);
}

int main(int argc, char** argv)
{
    cv::CommandLineParser parser(
                argc,
                argv,
                "{help h||}"
                "{FileName||Path to file.}"
                "{CameraId|0|Camera device number.}"
                "{ApiReference|0|Select preferred API for a capture object.}"
                "{FaceCascade|./lbpcascade_frontalface.xml|Path to face cascade.}"
                "{CascadeCount|1|Count face cascade.}");

    parser.about("Video Faces Detector\n");
    parser.printMessage();
    createApplication(parser)->run();

    return 0;
}
