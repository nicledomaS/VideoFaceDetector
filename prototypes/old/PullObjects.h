#ifndef PULLOBJECTS_H
#define PULLOBJECTS_H

#include <memory>
#include <vector>
#include <queue>
#include <mutex>

#include "opencv2/objdetect.hpp"

class Object;

class PullObjects
{
public:
    PullObjects(const std::string& fileName);
    ~PullObjects();

    std::shared_ptr<Object> createNewObject();
    std::shared_ptr<Object> getFree() const;

    void detect(const std::shared_ptr<cv::Mat>& frame, cv::CascadeClassifier &faceCascade);
private:
    std::string m_fileName;
    std::vector<std::shared_ptr<Object>> m_objects;
    std::mutex mtx;
    std::condition_variable condVar;
    std::queue<cv::Mat> frames;
    std::thread thrd;
};

#endif // PULLOBJECTS_H
