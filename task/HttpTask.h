#pragma once

#include "Task.h"
using namespace yazi::thread;

#include "Socket.h"
using namespace yazi::socket;

namespace yazi {
namespace task {

class HttpTask : public Task
{
public:
    HttpTask(Socket * socket);
    virtual ~HttpTask();

    virtual void run();
    virtual void destroy();
};

}}
