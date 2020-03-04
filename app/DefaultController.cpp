#include "DefaultController.h"
using namespace yazi::app;

DefaultController DefaultController::ctrl;

DefaultController::DefaultController()
{
    register_handler("/", &DefaultController::index);
}

DefaultController::~DefaultController()
{
}

void DefaultController::index(const Request & req, Response & resp)
{
    string html =  "<!DOCTYPE html> \
                    <html> \
                        <head> \
                            <meta charset=\"utf-8\"> \
                            <title>yazi-web</title> \
                        </head> \
                        <body> \
                            <h1>this is html page</h1> \
                            <p>yazi-web is a lightweight c++ mvc framework</p> \
                        </body> \
                    </html>";
    resp.html(html);
}

