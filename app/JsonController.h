#pragma once

#include "Controller.h"
using namespace yazi::web;

#include "Request.h"
#include "Response.h"
using namespace yazi::server;

namespace yazi {
namespace app {

class JsonController : public Controller
{
public:
    JsonController();
    ~JsonController();

    static void index(const Request & req, Response & resp);

protected:
    static JsonController ctrl;
};

}}
