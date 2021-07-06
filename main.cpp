#include <iostream>
using namespace std;
#include "PostOrder.h"
#include "Pila.h"
#include "Cola.h"
#include "Arbol.h"
#include "Operation.h"

//Inicialización
PostOrder Po;
Operation Op;
Nodo *Post = NULL;
Nodo *Pre = NULL;
NodoC *Inicio;
NodoC *Fin;
NodoC *Aux;
NodoA *arbol = NULL;

int main(){
  
//SOLICITUD DE OPERACIÓN
  string operacion;
  cout<<"Ingrese su operación: "; 
  getline(cin,operacion);
  
//AGREGA LA INFORMACIÓN DE LA OPERACIÓN A NODOS EN UNA COLA 
  agregarTotal(Inicio, Fin, operacion);
  
//ORDENA EN POST ORDER LOS NODOS DE LA COLA Y LOS AGREGA A UNA PILA
  Aux = Inicio;
  Po.convertirToPost(Post, Aux, Fin);

    cout<<"\n";

    cout<<"El arbol generado es:\n";
//CREACIÓN DEL ARBOL USANDO ABB
  crearArbol(Post, arbol);
  
    cout<<"\n";

//MOSTRAR EL ARBOL USANDO RECORRIDO POST ORDER
  mostrarArbol(arbol,0);
  
//RESUELVE LA OPERACIÓN
  
  try {

    cout<<"El resultado es: "<<Op.OperationResult(arbol);
  }
  catch (std::invalid_argument) {
    
    cout<<"SYNTAXIS ERROR, VARIABLE ENCONTRADA";
  }


  return 0;
}
