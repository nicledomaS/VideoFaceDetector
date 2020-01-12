#pragma once

#include <vector>
#include <thread>

#include <boost/noncopyable.hpp>

namespace core
{

class JoinThreads : boost::noncopyable
{
public:
    JoinThreads(std::vector<std::thread>& threads);
    ~JoinThreads();

private:
    std::vector<std::thread>& m_threads;
};

} // core


