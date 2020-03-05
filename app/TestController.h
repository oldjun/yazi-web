#pragma once

#include "Controller.h"
using namespace yazi::web;

#include "Request.h"
#include "Response.h"
using namespace yazi::server;

namespace yazi {
namespace app {

class TestController : public Controller
{
public:
    TestController();
    ~TestController();

    static void index(const Request & req, Response & resp);
    static void detail(const Request & req, Response & resp);

protected:
    static TestController ctrl;
};

}}
