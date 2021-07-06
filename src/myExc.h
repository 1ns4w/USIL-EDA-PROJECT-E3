#ifndef __MY_EXC_H__
#define __MY_EXC_H__

#include <exception>
#include <cstring>
#include <string> //c++11
#include <sstream>
using namespace std;

class MyException : public exception
{
  private:
    string m_errMsg;
    size_t m_pos;
    string m_ErrorMsg;
  public:
    MyException(string str, size_t pos)
              : m_errMsg(str), m_pos(pos)
    {
      stringstream m_fullErrMsg;
        m_fullErrMsg << m_errMsg << " pos: " << m_pos <<endl;
        m_ErrorMsg = m_fullErrMsg.str();
    }
    MyException(string str) : m_errMsg(str) {}
  public:
    const char * what () const throw ()
    {      return m_ErrorMsg.c_str();
    }
};
#endif
