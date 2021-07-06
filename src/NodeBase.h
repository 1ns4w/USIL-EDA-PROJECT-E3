#ifndef __NODE_BASE_H__
#define __NODE_BASE_H__

#include "type.h"
using namespace std;

class NodeBase
{
  protected:
    TX m_value = 0;
    TX getValue() { return m_value; }
    virtual void setValue(TX value) = 0;
  public:
    NodeBase(TX val = 0) : m_value(val) {};
    virtual TX eval() = 0;
};
#endif
