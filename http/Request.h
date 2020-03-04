#pragma once
#include <string>
using namespace std;

#include <map>

namespace yazi {
namespace http {

class Request
{
public:
    Request();
    ~Request();

    bool parse(const char * buf, int len);

    bool is_get() const;
    bool is_post() const;
    bool is_ajax() const;

    const string & get(const string & name) const;
    const string & post(const string & name) const;
    const string & header(const string & name) const;
    const string & cookie(const string & name) const;
    const string & path() const;
    const string & user_agent() const;
    const string & user_host() const;

    void show();

private:
    string m_method;
    string m_uri;
    string m_proto;
    string m_path;
    string m_body;
    string m_query_string;
    std::map<string, string> m_get;
    std::map<string, string> m_post;
    std::map<string, string> m_headers;
    std::map<string, string> m_cookies;
    static const string null;
};

}}
