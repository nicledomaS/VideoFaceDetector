#pragma once

#include <vector>
#include <atomic>
#include <thread>
#include <memory>

#include <boost/noncopyable.hpp>

#include "ThreadsafeQueue.h"

namespace core
{

class JoinThreads;

using Task = std::function<void()>;

class ThreadPool : private boost::noncopyable
{
public:
    explicit ThreadPool(size_t threadCount);
    ~ThreadPool();

    void submit(Task func);

private:
    void worker();

private:
    std::atomic_bool m_stop;
    std::vector<std::thread> m_threads;
    std::unique_ptr<JoinThreads> m_joinThread;
    ThreadsafeQueue<Task> m_tasks;
};

} // core
