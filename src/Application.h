#pragma once

#include <boost/noncopyable.hpp>

namespace core
{

class Application : private boost::noncopyable
{
public:
    virtual ~Application() = default;
    virtual void run() = 0;
};

} // core
