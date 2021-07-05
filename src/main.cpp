#ifndef __OPERATOR_H__
#define __OPERATOR_H__
#include <map>
using std::map;
typedef int (*operator_func)(int, int);
int suma(int a, int b)
{
    return a + b;
}

int resta(int a, int b)
{
    return a - b;
}

int multiplicacion(int a, int b)
{
    return a * b;
}

int division(int a, int b)
{
    return a/b;
}

map<char, operator_func> operatorMap = {{ '+', &suma}, {'-', &resta}, {'*', &multiplicacion}, {'/', &division}};
map<char,int> operatorPrecedence = {{'+',1},{'-',1},{'*',2},{'/',2}};



#endif // __OPERATOR_H__

