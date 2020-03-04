#include "Request.h"
using namespace yazi::http;

#include <string.h>
#include <vector>

#include "Logger.h"
#include "String.h"
using namespace yazi::utility;

const string Request::null = "";

Request::Request()
{
}

Request::~Request()
{
}

bool Request::parse(const char * buf, int len)
{
    /* Parse request line: method, URI, proto */
    const char * s = buf;
    const char * e = buf + len - 1;
    const char * i = s;

    /* Request is fully buffered. Skip leading whitespaces. */
    while ((i < e) && (isspace(*i))) i++;
    s = i;

    // parse http request's method
    while ((i < e) && (strchr(" ", *i) == NULL)) i++;
    m_method = string(s, 0, i - s);

    while ((i < e) && (strchr(" ", *i) != NULL)) i++;
    s = i;

    // parse http request's uri
    while ((i < e) && (strchr(" ", *i) == NULL)) i++;
    m_uri = string(s, 0, i - s);

    while ((i < e) && (strchr(" ", *i) != NULL)) i++;
    s = i;

    // parse http request's protocol
    while ((i < e) && (strchr("\r\n", *i) == NULL)) i++;
    m_proto = string(s, 0, i - s);

    while ((i < e) && (strchr("\r\n", *i) != NULL)) i++;
    s = i;

    /* If URI contains '?' character, initialize query_string */
    size_t pos = m_uri.find_first_of('?');
    if (pos != string::npos)
    {
        m_path = m_uri.substr(0, pos);
        m_query_string = m_uri.substr(pos + 1);

        std::vector<string> output;
        String::Split(output, m_query_string, '&');
        for (std::vector<string>::iterator it = output.begin(); it != output.end(); it++)
        {
            std::vector<string> out;
            String::Split(out, (*it), '=');
            if (out.size() == 2)
            {
                m_get[out[0]] = out[1];
            }
            else
            {
                m_get[out[0]] = "";
            }
        }
    }
    else
    {
        m_path = m_uri;
    }
    

    /* Parse request headers */
    while (i < e)
    {
        // parse http request header's name
        while ((i < e) && (strchr(": ", *i) == NULL)) i++;
        string name = string(s, 0, i - s);

        while ((i < e) && (strchr(": ", *i) != NULL)) i++;
        s = i;

        // parse http request header's value
        while ((i < e) && (strchr("\r\n", *i) == NULL)) i++;
        string value = string(s, 0, i - s);

        m_headers[name] = value;

        if (strncmp(i, "\r\n\r\n", 4) == 0)
        {
            break;
        }

        while ((i < e) && (strchr("\r\n", *i) != NULL)) i++;
        s = i;
    }

    while ((i < e) && (strchr("\r\n", *i) != NULL)) i++;
    s = i;

    m_body = string(s);

    return true;
}

bool Request::is_get() const
{
    return (m_method == "GET");
}

bool Request::is_post() const
{
    return (m_method == "POST");
}

bool Request::is_ajax() const
{
    return false;
}

const string & Request::get(const string & name) const
{
    std::map<string, string>::const_iterator it = m_get.find(name);
    if (it != m_get.end())
    {
        return it->second;
    }
    return null;
}

const string & Request::post(const string & name) const
{
    std::map<string, string>::const_iterator it = m_post.find(name);
    if (it != m_get.end())
    {
        return it->second;
    }
    return null;
}

const string & Request::header(const string & name) const
{
    std::map<string, string>::const_iterator it = m_headers.find(name);
    if (it != m_get.end())
    {
        return it->second;
    }
    return null;
}

const string & Request::cookie(const string & name) const
{
    std::map<string, string>::const_iterator it = m_cookies.find(name);
    if (it != m_get.end())
    {
        return it->second;
    }
    return null;
}

const string & Request::path() const
{
    return m_path;
}

const string & Request::user_host() const
{
    return header("Host");
}

const string & Request::user_agent() const
{
    return header("User-Agent");
}

void Request::show()
{
    debug("http method: %s", m_method.c_str());
    debug("http uri: %s", m_uri.c_str());
    debug("http proto: %s", m_proto.c_str());
    debug("http path: %s", m_path.c_str());
    debug("http query string: %s", m_query_string.c_str());
    debug("http headers -- start");
    for (std::map<string, string>::const_iterator it = m_headers.begin(); it != m_headers.end(); it++)
    {
        debug("http header: %s=%s", it->first.c_str(), it->second.c_str());
    }
    debug("http headers -- end");
    debug("http get params -- start");
    for (std::map<string, string>::const_iterator it = m_get.begin(); it != m_get.end(); it++)
    {
        debug("http get: %s=%s", it->first.c_str(), it->second.c_str());
    }
    debug("http get params -- end");
    debug("http post params -- start");
    for (std::map<string, string>::const_iterator it = m_post.begin(); it != m_post.end(); it++)
    {
        debug("http post: %s=%s", it->first.c_str(), it->second.c_str());
    }
    debug("http post params -- end");
    debug("http body: %s", m_body.c_str());
}