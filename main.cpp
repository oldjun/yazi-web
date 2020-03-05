#include <iostream>
using namespace std;

#include "System.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "Server.h"
using namespace yazi::server;

int main()
{
    Singleton<System>::instance()->init();

    Server * server = Singleton<Server>::instance();
    server->listen("", 8080);
    server->start();

    return 0;
}
