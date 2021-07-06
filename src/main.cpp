#include <iostream>
#include "general.h"

int main()
{
  LexicalAnalyzer la;
  //string exp = "a+b/(35^X-(y+3))-6";
  //string exp = "a+b/x-y+(3-6)-(x+y)-3";
  string exp = "2+1/6-4";
  try
  {
    NodeBase *pExp = la.Analize(exp);

  }
  catch(MyException *pExc)
  {
    cerr << pExc->what() << endl;
  }
}
