#ifndef __UTIL_H__
#define __UTIL_H__
#include<string>
#include <regex>
using std::string;
using std::regex;
template <typename T>
bool isInArray(T ar[], size_t arrSize, T element)
{
    for(size_t i = 0; i<arrSize; i++)
    {
        if(ar[i] == element)
        {
            return true;
        }
    }
    return false;
}


bool isNumber(string str)
{
    regex num_expr("(\\+|-)?[[:digit:]]+(\\.[[:digit:]]+)*");
    return regex_match(str, num_expr);
}


#endif // __UTIL_H__
