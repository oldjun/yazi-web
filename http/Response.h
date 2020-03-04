#pragma once

#include <string>
using namespace std;

namespace yazi {
namespace http {

class Response
{
public:
    enum Type
    {
        HTML = 0,
        JSON
    };

    Response();
    ~Response();

    void html(const string & data);
    void json(const string & data);
    string data() const;

private:
    Type m_type;
    string m_data;
};

}}
