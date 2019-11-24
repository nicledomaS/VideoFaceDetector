#include <iostream>
#include <stdexcept>

#include "opencv2/imgproc.hpp"

#include "Object.h"

Object::Object(const std::string &fileName, const Work &work)
    : m_used(false),
      m_work(work)
{
    try {
        if( !m_faceCascade.load( fileName ) )
        {
            std::cout << "--(!)Error loading face cascade\n";
            throw std::runtime_error("--(!)Error loading face cascade");
        };
    } catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

}

void Object::start(const std::shared_ptr<cv::Mat> &frame)
{
    m_used = true;
    std::thread([this, frame]()
    {
        m_work(frame, m_faceCascade);
        m_used = false;
    }).detach();
}

bool Object::used() const
{
    return m_used;
}
