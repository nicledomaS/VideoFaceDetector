#pragma once

#include <queue>
#include <mutex>

#include <boost/noncopyable.hpp>

namespace core
{

template<typename T>
class ThreadsafeQueue : private boost::noncopyable
{
public:
    void push(const std::shared_ptr<T>& newValue);
    bool tryPop(std::shared_ptr<T> &newValue);

private:
    mutable std::mutex m_mutex;
    std::queue<std::shared_ptr<T>> m_queue;
};

template<typename T>
void ThreadsafeQueue<T>::push(const std::shared_ptr<T>& newValue)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(newValue);
}

template<typename T>
bool ThreadsafeQueue<T>::tryPop(std::shared_ptr<T> &newValue)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_queue.empty())
    {
        return false;
    }

    newValue = std::move(m_queue.front());
    m_queue.pop();
    return true;
}

} // core

