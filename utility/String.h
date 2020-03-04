#pragma once

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <cctype>
#include <algorithm>
#include <iterator>
using namespace std;

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace yazi {
namespace utility {

class String
{
public:
    static string ToLower(const string& input);
    static string ToUpper(const string& input);

    static char ToChar(const string& input);
    static short ToShort(const string& input);
    static int ToInt(const string& input);
    static long ToLong(const string& input);
    static float ToFloat(const string& input);
    static double ToDouble(const string& input);

    static string ToString(char c);
    static string ToString(short s);
    static string ToString(int i);
    static string ToString(long l);
    static string ToString(float f);
    static string ToString(double d);

    static string TrimStart(const string& input);
    static string TrimStart(const string& input, char trim);
    static string TrimStart(const string& input, const char* trims);

    static string TrimEnd(const string& input);
    static string TrimEnd(const string& input, char trim);
    static string TrimEnd(const string& input, const char* trims);

    static string Trim(const string& input);
    static string Trim(const string& input, char trim);
    static string Trim(const string& input, const char* trims);

    static void Split(vector<string>& output, const string& input);
    static void Split(vector<string>& output, const string& input, char separator);
    static void Split(vector<string>& output, const string& input, const string& separators);

    static string Join(vector<string>& input);
    static string Join(vector<string>& input, char separator);
    static string Join(vector<string>& input, const char* separators);

    static int Compare(const string& strA, const string& strB, bool ignoreCase = false);
    static string Format(const char* format, ...);

    static bool IsNumeric(const string& input);
};

}}
