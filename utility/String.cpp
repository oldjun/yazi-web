#include "String.h"

using namespace yazi::utility;

string String::ToLower(const string& input)
{
    string str = input;
    std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);
    return str;
}

string String::ToUpper(const string& input)
{
    string str = input;
    std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::toupper);
    return str;
}

char String::ToChar(const string& input)
{
    char c = 0;
    stringstream ss;
    ss << input;
    ss >> c;
    return c;
}

short String::ToShort(const string& input)
{
    short s = 0;
    stringstream ss;
    ss << input;
    ss >> s;
    return s;
}

int String::ToInt(const string& input)
{
    //return atoi(input.c_str());
    int i = 0;
    stringstream ss;
    ss << input;
    ss >> i;
    return i;
}

long String::ToLong(const string& input)
{
    //return atol(input.c_str());
    long l = 0;
    stringstream ss;
    ss << input;
    ss >> l;
    return l;
}

float String::ToFloat(const string& input)
{
    float f = 0.0;
    stringstream ss;
    ss << input;
    ss >> f;
    return f;
}

double String::ToDouble(const string& input)
{
    // return atof(input.c_str());
    double d = 0.0;
    stringstream ss;
    ss << input;
    ss >> d;
    return d;
}

string String::ToString(char c)
{
    ostringstream os;
    os << c;
    return os.str();
}

string String::ToString(short s)
{
    ostringstream os;
    os << s;
    return os.str();
}

string String::ToString(int i)
{
    ostringstream os;
    os << i;
    return os.str();
}

string String::ToString(long l)
{
    ostringstream os;
    os << l;
    return os.str();
}

string String::ToString(float f)
{
    ostringstream os;
    os << f;
    return os.str();
}

string String::ToString(double d)
{
    ostringstream os;
    os << d;
    return os.str();
}

string String::TrimStart(const string& input)
{
    return TrimStart(input, " \r\n");
}

string String::TrimStart(const string& input, char trim)
{
    string str;
    str = trim;
    return TrimStart(input, str.c_str());
}

string String::TrimStart(const string& input, const char* trims)
{
    string delimiter = trims;
    string str = input;
    size_t found;
    found = str.find_first_not_of(delimiter);
    if (found != string::npos)
        str.erase(0, found);
    else
        str.clear();
    return str;
}

string String::TrimEnd(const string& input)
{
    return TrimEnd(input, " \r\n");
}

string String::TrimEnd(const string& input, char delim)
{
    string str;
    str = delim;
    return TrimEnd(input, str.c_str());
}

string String::TrimEnd(const string& input, const char* delims)
{
    string delimiter = delims;
    string str = input;
    size_t found;
    found = str.find_last_not_of(delimiter);
    if (found != string::npos)
        str.erase(found + 1);
    else
        str.clear();
    return str;
}

string String::Trim(const string& input)
{
    return Trim(input, " \r\n");
}

string String::Trim(const string& input, char trim)
{
    string str;
    str = trim;
    return Trim(input, str.c_str());
}

string String::Trim(const string& input, const char* trims)
{
    string str = TrimStart(input, trims);
    str = TrimEnd(str, trims);
    return str;
}

void String::Split(vector<string>& output, const string& input)
{
    output.clear();
    istringstream iss(input);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(output));
}

void String::Split(vector<string>& output, const string& input, char separator)
{
    output.clear();
    stringstream ss(input);
    string item;
    while(getline(ss, item, separator))
    {
        output.push_back(item);
    }
}

void String::Split(vector<string>& output, const string& input, const string& separators)
{
    output.clear();
    size_t last = 0;
    size_t index = input.find_first_of(separators, last);
    while (index != string::npos)
    {
        string str = input.substr(last, index - last);
        output.push_back(str);
        last = index + 1;
        index = input.find_first_of(separators, last);
    }
    if (index - last > 0)
    {
        output.push_back(input.substr(last , index - last));
    }
}

string String::Join(vector<string>& input)
{
    return Join(input, ' ');
}

string String::Join(vector<string>& input, char separator)
{
    ostringstream os;
    vector<string>::iterator it;
    for (it = input.begin(); it != input.end(); it++)
    {
        os << *it;
        os << separator;
    }
    return os.str();
}

string String::Join(vector<string>& input, const char* separators)
{
    ostringstream os;
    vector<string>::iterator it;
    for (it = input.begin(); it != input.end(); it++)
    {
        os << *it;
        os << separators;
    }
    return os.str();
}

int String::Compare(const string& strA, const string& strB, bool ignoreCase)
{
    if (ignoreCase)
    {
        return strcasecmp(strA.c_str(), strB.c_str());
    }
    else
    {
        return strA.compare(strB);
    }
}

string String::Format(const char* format, ...)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsnprintf(buf, sizeof(buf), format, arg_ptr);
    va_end(arg_ptr);
    return string(buf);
}

bool String::IsNumeric(const string& input)
{
    if (input.find_first_not_of("0123456789.") != string::npos)
        return false;
    if (count(input.begin(), input.end(), '.') > 1)
        return false;
    return true;
}

