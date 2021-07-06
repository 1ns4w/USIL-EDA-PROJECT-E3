#ifndef __NODE_NUMBER_H__
#define __NODE_NUMBER_H__

#include "NodeBase.h"

class NodeNumber : public NodeBase
{
  public:
    NodeNumber(TX val) : NodeBase(val) {}
    virtual TX eval() { return getValue(); }
    virtual void setValue(TX value) {  assert(0);   }
};
#endif
