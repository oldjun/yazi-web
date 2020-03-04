# yazi-web
a c++ mvc web framework

|Author|junping|
|---|---|
|E-mail|oldjun@sina.com|
|Wechat|chenjunping1024|

## Overview
**yazi-web** is a C++ based HTTP application framework. yazi-web can be used to easily build various types of web application server programs using C++. 

yazi-web only supports Linux. Its main features are as follows:

* Use a non-blocking I/O network lib based on epoll to provide high-concurrency;
* Provide a completely asynchronous programming mode;
* Based on template, a simple reflection mechanism is implemented to completely decouple the main program framework, controllers and views;
* Support cookies and built-in sessions;
* Support back-end rendering, the controller generates the data to the view to generate the Html page;
* Support view page dynamic loading (dynamic compilation and loading at runtime);
* Provide a convenient and flexible routing solution from the path to the controller handler;
* Support JSON format request and response, very friendly to the Restful API application development;
* Support non-blocking I/O based asynchronously reading and writing database (MySQL(MariaDB) database);

## Start the web server
Unlike most C++ frameworks, the main program of the yazi-web application can be kept clean and simple. yazi-web uses a few tricks to decouple controllers from the main program.
```c++
#include <iostream>
using namespace std;

#include "Singleton.h"
#include "System.h"
using namespace yazi::utility;

#include "Server.h"
using namespace yazi::http;

int main()
{
    Singleton<System>::instance()->init();

    Server * server = Singleton<Server>::instance();
    server->listen("", 8080);
    server->start();

    return 0;
}
```
