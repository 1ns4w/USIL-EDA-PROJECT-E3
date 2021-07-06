#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include "NodeBase.h"
#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <cstdlib>
#include <list>
#include <map>
#include <string>

#include <cctype>

#include <iostream>

using namespace std;


class LexicalAnalyzer 
{
  struct Couple
  {
    NodeBase *pExp;
    string operation;
    Couple(NodeBase *_pExp, string _operation)
        : pExp(_pExp), operation(_operation) {}
  };
  
  class NodeNumber : public NodeBase
  {
    public:
      NodeNumber(TX val) : NodeBase(val) {}

      virtual TX eval() { return getValue(); }
      virtual void setValue(TX value) {  assert(0);   }
  };

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

  class NodeVariable : public NodeBase
  {
    string m_name;
    public:
      NodeVariable(string name, TX val) 
                  : NodeBase(val), m_name(name) {}

      virtual TX eval() { return getValue(); }
      virtual void setValue(TX value) {  m_value = value;   }
  };

  map<string, T2> operator_priority = 
  {
        {"^",5000},
        {"/",4000},
        {"*",3000},
        {"-",2000},
        {"+",1000},
  };
  //mapa de variables, Maizo
  map<string, NodeBase*> m_vars =
  {
   // {"X",pNodeVariable};
  };

  public:
    LexicalAnalyzer() {};
    NodeBase *MakeSyntacticExpressionTree(string str); 
  private:
    NodeBase *MakeSyntacticExpressionTree2(list<string> &tokens);list<string> getListofTokens(string str);
    vector<Couple> MakeCouples(list<string> &tokens);
    NodeBase *getNode(string operando);
    TX getNumber(string str1);
    T3 Isnumber(const string& str);
  public:
    NodeBase *Analize(string exp);
};
/*
  Input: string i.e "X5^3/(YW-5)*2^X"
  Output: Expression tree
*/

T3 LexicalAnalyzer::Isnumber(const string& str)
{
  for (T3 const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

NodeBase *LexicalAnalyzer::Analize(string exp)
{
  return MakeSyntacticExpressionTree(exp);
}

//crea la lista de tokens
NodeBase *LexicalAnalyzer::MakeSyntacticExpressionTree(string str)
{ 
  list<string> tokens = getListofTokens(str);
  return MakeSyntacticExpressionTree2(tokens);
}

/*
  Input: List of tokens: "X","^","3","/","(","Y","-","5",
                         ")","*","2","^","X"
  Output: Expression tree
*/

//crea el arbol
NodeBase *LexicalAnalyzer::MakeSyntacticExpressionTree2(list<string> &tokens)
{
  vector<Couple> m_trees = MakeCouples(tokens);
  for (auto x : operator_priority)
  {

  }
  return nullptr;
}

list<string> LexicalAnalyzer::getListofTokens(string str)
{
  list<string> output;
  auto pos = 0;
  string exp;
  auto size = str.size();
  for(auto i = 0; i<size;)
  {
      exp = "";
      if( str[i] == '(' )
      { i++;   // saltar el (
        auto cPar = 1; 
        while(cPar > 0 && i<size)// XW+15-(a+(b/c))+K. => XW, +, 15,-,a+(b/c), +, K
        {   if(str[i] == '(') cPar++;
            if(str[i] == ')') cPar--;
            if( cPar > 0)
              exp += str[i];
            i++;
        }
        if( i == size )
        {
          throw new MyException("paréntesis no cerrado: "+exp, i-exp.size());
        }
      }
      else      // No es paréntesis
      {
        if( isalnum(str[i]) ) // letra o numero
        { while( isalnum(str[i]))
            exp += str[i++];
        }
        else    // Operaciones + - * / ^ -> != <>
        {
            while( !isalnum(str[i]) && i<size )
            {
                exp += str[i++];
                if (str[i]=='(' || str[i]==')')
                  break;
            }  
        }
      } 
      output.push_back(exp);
  }
  return output;
}

TX LexicalAnalyzer::getNumber(string str1)
{ //re-hecho por maizo
  TX num_double = stod(str1);
  string str2 = to_string(num_double);
  if (str1 == str2)
    return num_double;
  throw new MyException("Error detectado: el string no fue transformado");
}

NodeBase *LexicalAnalyzer::getNode(string operando)
{
  auto iter = m_vars.find(operando); // m_vars["AX"] = pNodeVariable;
  if( iter != m_vars.end() )
    return iter->second;
  if (Isnumber(operando)) //else if y else agregados por maizo
  { 
    try
      { 
        TX numnodo = getNumber(operando);
        return new NodeNumber(numnodo);
      }
    catch(MyException *pExc)
      { cout << pExc->what() << endl; }
  }
   return MakeSyntacticExpressionTree(operando); 
}

vector<LexicalAnalyzer::Couple> LexicalAnalyzer::MakeCouples(list<string> &tokens)
{
  vector<Couple> trees;
  for(auto iter= tokens.begin(); iter != tokens.end(); iter++)
  {
    string operando = *iter++;
    NodeBase *pNode = getNode(operando);

    string operador = "";
    if(iter != tokens.end() )
      operador = *iter++;
    
    Couple couple(pNode, operador);  
    trees.push_back(couple);
  }
  return trees;
}
#endif
