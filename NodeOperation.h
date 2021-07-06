#ifndef __NODE_OPERATION_H__
#define __NODE_OPERATION_H__

#include <map>
#include "NodeBase.h"

class NodeOperation : public NodeBase
{
  using OpeMet = TX (NodeOperation::*)(TX , TX );

  T1      m_opeStr; // "+", "*", "/", etc
  OpeMet  m_pOperationMethod;
  NodeBase * m_pRight;
  NodeBase * m_pLeft;

  map<string, OpeMet > m_opeMap = {
        {"+", &NodeOperation::suma},
        {"-", &NodeOperation::resta},
        {"/", &NodeOperation::division},
        {"*", &NodeOperation::multip},
        /*{"^", &NodeOperation::power},
        {"sin", &NodeOperation::sin},*/
      };
  
  public:
    NodeOperation(T1 ope, NodeBase *pLeft, NodeBase *pRight);
        
    virtual TX eval();
    virtual void setValue(TX value) {  assert(0);   }
    
    TX suma (TX v1, TX v2);
    TX resta (TX v1, TX v2);
    TX division (TX v1, TX v2);
    TX multip (TX v1, TX v2);
};

NodeOperation::NodeOperation(T1 ope, NodeBase *pLeft, NodeBase *pRight)
            : m_opeStr(ope), m_pLeft(pLeft), m_pRight(pRight)
{ m_pOperationMethod = m_opeMap[m_opeStr]; }

TX NodeOperation::eval()
{
  TX v1 = m_pLeft->eval();
  TX v2 = 0;
  if( m_pRight ) v2 = m_pRight->eval();
  return (this->*m_pOperationMethod)(v1, v2);
}

TX NodeOperation::suma (TX v1, TX v2)
{ return v1+v2; }

TX NodeOperation::resta (TX v1, TX v2)
{ return v1-v2; }

TX NodeOperation::division (TX v1, TX v2)
{ return v1/v2; }

TX NodeOperation::multip (TX v1, TX v2)
{ return v1*v2; }

#endif
