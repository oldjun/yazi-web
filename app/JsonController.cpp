#include "JsonController.h"
using namespace yazi::app;

#include "Json.h"
using namespace yazi::json;

JsonController JsonController::ctrl;

JsonController::JsonController()
{
    register_handler("/json", &JsonController::index);
}

JsonController::~JsonController()
{
}

void JsonController::index(const Request & req, Response & resp)
{
    Json json;
    json["code"] = 0;
    json["data"]["id"] = req.get("id");
    json["data"]["name"] = req.get("name");
    
    resp.json(json.toString());
}
