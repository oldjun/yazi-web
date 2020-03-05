#pragma once

#include <string>
using namespace std;

#include "Request.h"
#include "Response.h"

namespace yazi {
namespace server {

typedef void (*server_handler)(const Request & req, Response & resp);

class Server
{
public:
    Server();
    ~Server();

    void listen(const string & ip, int port);
    void start();

    void set_threads(int threads);
    void set_connects(int connects);

    void on(const string & path, server_handler handler);
    string handle(const Request & req);

private:
    string m_ip;
    int m_port;
    int m_threads;
    int m_connects;
    string m_root_path;
    std::map<string, server_handler> m_handlers;
};

}}
