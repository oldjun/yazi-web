#pragma once

#include <string>
using namespace std;

#include "Request.h"
#include "Response.h"

namespace yazi {
namespace http {

typedef void (*server_handler)(const Request & req, Response & resp);

class Server
{
public:
    Server();
    ~Server();

    void on(const string & path, server_handler handler);
    string handle(const Request & req);

    void listen(const string & ip, int port);
    void start(int threads = 1024, int connects = 1024);

private:
    std::map<string, server_handler> m_handlers;
};

}}
