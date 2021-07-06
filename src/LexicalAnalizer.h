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

class LexicalAnalyzer 
{
  map<string, int> operator_priority = {
        {"^",10},
        {"/",20},
        {"*",30},
        {"-",40},
        {"+",50},
};

  public:
    LexicalAnalyzer() {};
    NodeBase *MakeSyntacticExpressionTree(string str); 
  private:
    NodeBase *MakeSyntacticExpressionTree(list<string> &tokens);
    list<string> getListofTokens(string str);
  public:
    NodeBase *AnaliZe(string exp);
};

/*
  Input: string i.e "X5^3/(YW-5)*2^X"
  Output: Expression tree
*/
NodeBase *LexicalAnalyzer::MakeSyntacticExpressionTree(string str)
{ 
  list<string> tokens = getListofTokens(str);
  return MakeSyntacticExpressionTree(tokens);
}

/*
  Input: List of tokens: "X","^","3","/","(","Y","-","5",
                         ")","*","2","^","X"
  Output: Expression tree
*/
NodeBase *LexicalAnalyzer::MakeSyntacticExpressionTree(list<string> &tokens)
{
  vector<Couple> trees =MakeCouples(tokens);
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
        while(cPar > 0)  // XW+15-(a+(b/c))+K.      => XW, +, 15,-,a+(b/c), +, K
        {   if(str[i] == '(') cPar++;
            if(str[i] == ')') cPar--;
            if( cPar > 0)
              exp += str[i];
            i++;
        }
        if(i==size)
        {
          throw new myException("parentesis no cerrado: "+exp, i-exp.size());
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
            while( !isalnum(str[i]) && i<size)
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

NodeBase *LexicalAnalyzer::getNode(string operando)
{
  auto iter = m_vars.find(operando)
  if (iter != m_vars.end())
    return iter->second;
  try
  {
    TX ipsta =getNumber(operando)
    return new NodeNumber(operando)
  }
  catch (myException *pExc)
  {
    cout << pExc->what() << endl;
  }
  return
}

vector<LexicalAnalizer::Couple> LexicalAnalyzer::MakeCouples(list<string> &tokens)
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
