#ifndef __COLA_H__
#define __COLA_H__

#include<iostream>


using namespace std;

  struct NodoC{
    int dato;
    string valor;
    NodoC *siguiente;
  };

  //Prototipos de funciones 
  NodoC crearNodo();
  void insertarCola(NodoC *&,NodoC *&, int, string);
  bool colaVacia(NodoC *);
  void agregarTotal(NodoC *&,Nodo *&,string);
  int cantidadNodos(NodoC *&,Nodo *&);
  
  //Función para insertar elementos a una cola
  
  void insertarCola(NodoC *&frente, NodoC *&fin, int n,string s){
    NodoC *nuevo_nodo = new NodoC();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->valor = s;

    if(colaVacia(frente)){
      frente = nuevo_nodo;
    }else{
      fin->siguiente = nuevo_nodo;
    }
    fin = nuevo_nodo;
  }

  //Función para contar la cantidad de nodos de la cola
  int cantidadNodos(NodoC *&I, NodoC *&F){
    NodoC *nuevo = new NodoC();
    nuevo = I;
    int contador =1;
    while(nuevo != F){
      nuevo = nuevo->siguiente;
      contador++;
    }
    return contador;
  }

  //Función para determinar si la cola está vacía
  bool colaVacia(NodoC *frente){
    return (frente == NULL)?true : false;
  }

  //Agregar elementos de la operación
  void agregarTotal(NodoC *&frente, NodoC *&fin, string operacion){
    string concat ="";
    int contador = 1;
        
    for(int i=0;i<operacion.size();i++){
      char op = operacion[i];
      switch(op)
      {
      case '(':
      case ')':
        if(concat!=""){
            insertarCola(frente,fin,contador,concat);
            concat="";
            contador++;
        }        
        concat+=op;
        insertarCola(frente,fin,0,concat);
        concat="";
        break;
      case '^':
      case '*':
      case '/':
      case '+':
      case '-':
        if(concat!=""){
            insertarCola(frente,fin,contador,concat);
            concat="";
            contador++;
        }
        concat+=op;
        insertarCola(frente,fin,contador,concat);
        contador++;
        concat="";
        break;
      default:
      concat+=op;
      if(concat == "sen"||concat== "cos"||concat =="tan"||concat =="ctg"||concat=="sec"||concat =="csc"){
        insertarCola(frente,fin,contador,concat);
        concat="";
        contador++;
      };
    }
       
  }
  
  if(concat!=""){
      insertarCola(frente,fin,contador,concat);
  }
}
#endif
