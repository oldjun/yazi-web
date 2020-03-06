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
```

## Controllers
Create a demo RESTful API with the TestController class, as shown below

app\TestController.h
```c++
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
```

app\TestController.cpp
```c++
#include "TestController.h"
using namespace yazi::app;

TestController TestController::ctrl;

TestController::TestController()
{
    register_handler("/test", &TestController::index);
    register_handler("/test/detail", &TestController::detail);
}

TestController::~TestController()
{
}

void TestController::index(const Request & req, Response & resp)
{
    string html =   "<!DOCTYPE html> \
                        <html> \
                            <head> \
                            <meta charset=\"utf-8\"> \
                            <title>yazi-web</title> \
                        </head> \
                        <body> \
                            <h1>test controller</h1> \
                            <p>index action run</p> \
                        </body> \
                    </html>";
    resp.html(html);
}

void TestController::detail(const Request & req, Response & resp)
{
    string html =   "<!DOCTYPE html> \
                        <html> \
                            <head> \
                            <meta charset=\"utf-8\"> \
                            <title>yazi-web</title> \
                        </head> \
                        <body> \
                            <h1>test controller</h1> \
                            <p>detail action run</p> \
                        </body> \
                    </html>";
    resp.html(html);
}
```
As you can see, users can use the TestController to map paths and parameters at the same time. This is a very convenient way to create a RESTful API application. After compiling all of the above source files, we get a very simple web application. This is a good start. Type http://localhost/test in browser will run test controller's index method, type http://localhost/test/detail in browser will run test controller's detail method.

## Compile & Run the project
download the source code, cd into the yazi-server project working directory, run command make && ./main 
```bash
cd ./yazi-server
make
./main
```
