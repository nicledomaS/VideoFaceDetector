#include "ThreadPool.h"
#include "JoinThreads.h"

namespace core
{

ThreadPool::ThreadPool(size_t threadCount)
    : m_stop(false),
      m_joinThread(std::make_unique<JoinThreads>(m_threads))
{
    for(size_t i = 0; i < threadCount; ++i)
    {
        m_threads.push_back(std::thread(&ThreadPool::worker, this));
    }
}

ThreadPool::~ThreadPool()
{
    m_stop = true;
}

void ThreadPool::worker()
{
    while(!m_stop)
    {
        std::shared_ptr<Task> task;
        if(m_tasks.tryPop(task))
        {
            (*task)();
        }
        else
        {
            std::this_thread::yield();
        }
    }
}


void ThreadPool::submit(Task func)
{
    auto task = std::make_shared<Task>(std::move(func));
    m_tasks.push(task);
}

} // core
