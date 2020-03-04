#include "Server.h"
using namespace yazi::http;

#include <sstream>
using std::ostringstream;

#include "Logger.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "TaskDispatcher.h"
using namespace yazi::thread;

#include "SocketHandler.h"
using namespace yazi::socket;

#include "HttpTask.h"
using namespace yazi::task;

Task * http_task_creator(Socket * socket)
{
    return new HttpTask(socket);
}

Server::Server()
{
}

Server::~Server()
{
}

void Server::on(const string & path, server_handler handler)
{
    m_handlers[path] = handler;
}

string Server::handle(const Request & req)
{
    const string & path = req.path();
    std::map<string, server_handler>::iterator it = m_handlers.find(path);
    if (it != m_handlers.end())
    {
        Response resp;
        it->second(req, resp);
        return resp.data();
    }

    string body =  "<!DOCTYPE html> \
                    <html> \
                        <head> \
                            <meta charset=\"utf-8\"> \
                            <title>yazi-web</title> \
                        </head> \
                        <body> \
                            <h1>404 Page Not Found</h1> \
                            <p>yazi-web is a lightweight c++ mvc framework</p> \
                        </body> \
                    </html>";
    ostringstream os;
    os << "HTTP/1.1 404 Not Found\r\n";
    os << "Content-Type: text/html; charset: UTF-8\r\n";
    os << "Content-Length: " << body.size() << "\r\n\r\n";
    os << body << "\r\n";
    return os.str();
}

void Server::listen(const string & ip, int port)
{
    // initialize the socket handler
    SocketHandler * socket_handler = Singleton<SocketHandler>::instance();
    socket_handler->listen(ip, port);
}

void Server::start(int threads, int connects)
{
    // initialize the thread pool and task queue
    Singleton<TaskDispatcher>::instance()->init(threads);

    SocketHandler * socket_handler = Singleton<SocketHandler>::instance();

    // register the echo task creator
    socket_handler->creator(http_task_creator);
    socket_handler->handle(connects);
}
