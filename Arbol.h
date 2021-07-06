#ifndef __ARBOL_H__
#define __ARBOL_H__
#include <iostream>
#include "Pila.h"

struct NodoA{
  string dat;
  int val;
  NodoA *izq;
  NodoA *der;
  
};
//Prototipos
NodoA *crearNodo(string, int);
void insertarNodoArbol(NodoA *&,string,int);
void postOrden(NodoA *);
void crearArbol(Nodo *&, NodoA *&);
void mostrarArbol(NodoA *&, int cont);

//Crear Nodo
NodoA *crearNodo(string d, int v){
  NodoA *nuevo_nodo = new NodoA();
  nuevo_nodo->dat = d;
  nuevo_nodo->val = v;
  nuevo_nodo->izq = NULL;
  nuevo_nodo->der = NULL;

  return nuevo_nodo;
}

//Insertar nuevo nodo en el arbol
void insertarNodoArbol(NodoA *&arbol,string d,int v){
  if(arbol==NULL){
    NodoA *nuevo_nodo = crearNodo(d, v);
    arbol = nuevo_nodo;
  }else{
    int valorRaiz = arbol->val;
    if(v < valorRaiz){
      insertarNodoArbol(arbol->izq, d, v);
    }else{
      insertarNodoArbol(arbol->der, d, v);
    }
  }
}

//Crear el arbol 
void crearArbol(Nodo *&op, NodoA *&arbol){
  Nodo *operacion = new Nodo();
  operacion = op;
  string datoP;
  int tipoP;
  
  while(operacion!=NULL){
    datoP = operacion->dato;
    tipoP = operacion->tipo;
    insertarNodoArbol(arbol, datoP, tipoP);
    pop(operacion);
  }
}

//Mostrar el arbol
void mostrarArbol(NodoA *&arbol, int cont){
  if (arbol == NULL){
    return;
  }else{
    mostrarArbol(arbol->der, cont+1);
    for(int i = 0; i<cont; i++){
      cout<<"     ";
    }
    cout<<arbol->dat<<"\n";
    mostrarArbol(arbol->izq, cont+1);
  }
}

#endif
