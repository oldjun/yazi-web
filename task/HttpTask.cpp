#include "HttpTask.h"
using namespace yazi::task;

#include "Logger.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "SocketHandler.h"
using namespace yazi::socket;

#include "Request.h"
#include "Server.h"
using namespace yazi::http;



HttpTask::HttpTask(Socket * socket) : Task(socket)
{
}

HttpTask::~HttpTask()
{
}

void HttpTask::run()
{
    SocketHandler * handler = Singleton<SocketHandler>::instance();

    Socket * socket = static_cast<Socket *>(m_data);
    debug("http task run: socket=%x", socket);

    char buf[1024 * 10] = {0};
    int len = socket->recv(buf, 1024 * 10);
    if (len > 0)
    {
        debug("recv msg len: %d msg data: %s", len, buf);

        Request req;
        req.parse(buf, len);
        req.show();

        Server * server = Singleton<Server>::instance();
        string output = server->handle(req);
        socket->send(output.c_str(), output.size());
        handler->attach(socket);
    }
    else
    {
        debug("http task socket closed by peer");
        handler->remove(socket);
    }
}

void HttpTask::destroy()
{
    debug("http task destory");
    delete this;
}
