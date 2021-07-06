#include <iostream>
#include "general.h"

int main()
{
  LexicalAnalyzer la;
  string exp = "(a+b/x)-y+18/(3-6)";
  try
  {
    NodeBase *pExp = la.Analyze(exp);

    list<string> tokens = la.getListofTokens(exp);
    
    cout << "imput: " << exp << endl;
    for(auto tok: tokens)
      cout << tok << endl;
  }
  catch(MyException *pExc)
  {
    cerr << pExc->what() << endl;
  }
}
