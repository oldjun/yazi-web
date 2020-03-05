#pragma once

#include "Server.h"
#include "Request.h"
#include "Response.h"
using namespace yazi::server;

namespace yazi {
namespace web {

class Controller
{
public:
    Controller();
    ~Controller();
    
    static void register_handler(const string & path, server_handler handler);
};

}}
