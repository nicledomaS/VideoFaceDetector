#include "JoinThreads.h"

namespace core
{

JoinThreads::JoinThreads(std::vector<std::thread>& threads)
    : m_threads(threads)
{
}

JoinThreads::~JoinThreads()
{
    for(auto& thread : m_threads)
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
}

} // core
