#include "Response.h"
using namespace yazi::http;

#include <fstream>
#include <sstream>
using std::ostringstream;

Response::Response()
{
}

Response::~Response()
{
}

void Response::html(const string & data)
{
    m_type = HTML;
    m_data = data;
}

void Response::json(const string & data)
{
    m_type = JSON;
    m_data = data;
}

string Response::data() const
{
    ostringstream os;
    os << "HTTP/1.1 200 OK\r\n";
    switch (m_type)
    {
        case HTML:
            os << "Content-Type: text/html; charset: utf-8\r\n";
            break;
        case JSON:
            os << "Content-Type: application/json; charset: utf-8\r\n";
            break;
        default:
            break;
    }
    os << "Content-Length: " << m_data.size() << "\r\n\r\n";
    os << m_data << "\r\n";
    return os.str();
}