#ifndef __NODE_VARIABLE_H__
#define __NODE_VARIABLE_H__

#include "NodeBase.h"

class NodeVariable : public NodeBase
{
  string m_name;
  public:
    NodeVariable(string name, TX val) 
                : NodeBase(val), m_name(name) {}

    virtual TX eval() { return getValue(); }
    virtual void setValue(TX value) {  m_value = value;   }
};
#endif
