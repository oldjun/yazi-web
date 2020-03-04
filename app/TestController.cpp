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