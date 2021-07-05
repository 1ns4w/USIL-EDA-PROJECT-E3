#include <iostream>
#include "expression_tree.h"
#include <string.h>
#include <chrono>
using namespace std;

typedef std::chrono::high_resolution_clock myClock;
typedef std::chrono::duration<double,nano> nanoDuration;
typedef std::chrono::duration<double, milli> milliDuration;

int main()
{

    cout<<"Ingrese una expresion matematica:"<<endl;
    string s;
    getline(cin, s);
    cout<<s<<endl;
    ExpressionTree *tree = new ExpressionTree(s.c_str());

    //Se mide el tiempo de ejecucion de la evaluacion secuencial
    cout<<"\nMetodo secuencial"<<endl;
    auto start = myClock::now();
    const int resultado = tree->evaluate();
    auto end = myClock::now();
    cout<<"\nResultado: "<<resultado<<endl;
    milliDuration elapsed = end - start;
    cout<<"Tiempo de ejecucion (metodo secuencial): "<<elapsed.count()<<" ms."<<endl;

    //Se mide el tiempo de ejecucion utilizando threads
    cout<<"\nMetodo paralelo con threads: "<<endl;
    start = myClock::now();
    const int resultado2 = tree->asyncEvaluate2();
    end = myClock::now();
    cout<<"\nResultado: "<<resultado2<<endl;
    elapsed = end - start;
    cout<<"Tiempo de ejecucion (metodo paralelo con threads): "<<elapsed.count()<<" ms."<<endl;


    //Se mide el tiempo de ejecucion utilizando metodos async y future.
    cout<<"\nMetodo asincrono con async y future: "<<endl;
    start = myClock::now();
    const int resultado3 = tree->asyncEvaluate();
    end = myClock::now();
    cout<<"\nResultado: "<<resultado3<<endl;
    elapsed = end - start;
    cout<<"Tiempo de ejecucion (metodo paralelo con async y future): "<<elapsed.count()<<" ms."<<endl;


    cout<<"\nNotacion Infija:"<<endl;
    tree->recorridoInorden();
    cout<<"Notacion Prefija:"<<endl;
    tree->recorridoPreOrden();
    cout<<"Notacion Postfija:"<<endl;
    tree->recorridoPostOrden();
    return 0;
}
