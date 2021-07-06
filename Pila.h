#ifndef __PILA_H__
#define __PILA_H__

#include <iostream> 
using namespace std;

struct Nodo{
  string dato;
  int tipo;
  Nodo *siguiente;
};
//Prototipo de función
void push(Nodo *&,string, int);
void pop(Nodo *&, string &);
string nextP(Nodo *&);
bool vacio(Nodo *&);

//Función de agregar un nodo a la pila
void push(Nodo *&pila, string n, int t){
  Nodo *nuevo_nodo = new Nodo();
  nuevo_nodo -> dato = n;
  nuevo_nodo -> siguiente = pila;
  nuevo_nodo -> tipo = t;
  pila = nuevo_nodo;
}

void pop(Nodo *&pila){
  Nodo *aux = pila;
  pila = aux->siguiente;
  delete aux;
}

bool vacio(Nodo *&pila){
  bool empty=true;
  if(pila != NULL){
    empty=false;
  }
    return empty;
}

string nextP(Nodo *&pila){
  string n;
  if (vacio(pila)==0){
    Nodo *aux = pila;
    n = aux->dato;
    
    //pila = aux->siguiente;
  }else{
    n = '%';
  }
  return n;
}


#endif
