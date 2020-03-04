#include "Controller.h"
using namespace yazi::web;

#include "Singleton.h"
using namespace yazi::utility;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::register_handler(const string & path, server_handler handler)
{
    Server * server = Singleton<Server>::instance();
    server->on(path, handler);
}