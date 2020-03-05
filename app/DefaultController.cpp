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
                            <h1>default controller</h1> \
                            <p>index action run</p> \
                        </body> \
                    </html>";
    resp.html(html);
}

