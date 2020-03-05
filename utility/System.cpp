#include "System.h"
using namespace yazi::utility;

#include <sys/resource.h>

#include "Logger.h"
#include "Singleton.h"
using namespace yazi::utility;

System::System()
{
}

System::~System()
{
}

void System::init()
{
    core_dump();

    m_root_path = get_root_path();

    // initialize the global logger
    Logger::instance()->open(m_root_path + "/main.log");
}

void System::core_dump()
{
    // core dump
    struct rlimit x;
    int ret = getrlimit(RLIMIT_CORE, &x);
    x.rlim_cur = x.rlim_max;
    ret = setrlimit(RLIMIT_CORE, &x);

    ret = getrlimit(RLIMIT_DATA, &x);
    x.rlim_cur = 768000000;
    ret = setrlimit(RLIMIT_DATA, &x);
}

string System::get_root_path()
{
    if (m_root_path != "")
    {
        return m_root_path;
    }
    char path[1024];
    memset(path, 0, 1024);
    int cnt = readlink("/proc/self/exe", path, 1024);
    if (cnt < 0 || cnt >= 1024)
    {
        return "";
    }
    for (int i = cnt; i >= 0; --i)
    {
        if (path[i] == '/')
        {
            path[i] = '\0';
            break;
        }
    }
    return string(path);
}
