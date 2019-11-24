#ifndef OBJECT_H
#define OBJECT_H

#include <atomic>
#include <thread>

#include "opencv2/objdetect.hpp"

using Work = std::function<void(const std::shared_ptr<cv::Mat>& frame, cv::CascadeClassifier& faceCascade)>;

class Object
{
public:
    Object(const std::string& fileName, const Work& work);

    void start(const std::shared_ptr<cv::Mat>& frame);

    bool used() const;

private:
    std::atomic_bool m_used;
    cv::CascadeClassifier m_faceCascade;
    Work m_work;
};

#endif // OBJECT_H
