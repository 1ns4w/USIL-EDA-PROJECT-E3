#ifndef __POST_ORDER_H__
#define __POST_ORDER_H__
#include "Pila.h"
#include "Cola.h"

class PostOrder{
  private:
  string operacion;
  Nodo *Post;
  NodoC *ListI;
  NodoC *ListF;
  public:
  PostOrder();
  void convertirToPost(Nodo *&, NodoC *&, NodoC *&);  
  int jerarquia(string);
};
//Constructor de la clase
PostOrder:: PostOrder(){}

//Ordena los datos recibidos en Post orden
void PostOrder :: convertirToPost(Nodo *&Salida, NodoC *&Inicio, NodoC *&Fin)
{
  Post = Salida; 
  Nodo *Aux = NULL;
  ListI = Inicio;
  ListF = Fin;
  
  for(int i=0; i<cantidadNodos(Inicio, Fin); i++){

    string val = ListI->valor;
    int num = ListI->dato;
    
    if(val == "(") {
      push(Aux, val,0); 

    }else if(val == "^" ||val == "*" ||val == "/" ||val == "+" ||val == "-"){
      while(jerarquia(val)<= jerarquia(nextP(Aux))){
          string n = nextP(Aux);
          push(Salida, n, Aux->tipo);
          pop(Aux);
          
      }
      push(Aux, val, num);

    }else if(val == "sen" ||val == "cos" ||val == "tan" ||val == "ctg" ||val == "sec"||val == "csc"){
      while(jerarquia(val)<= jerarquia(nextP(Aux))){
          string n = nextP(Aux);
          push(Salida, n, Aux->tipo);
          pop(Aux);
          
      }
      push(Aux, val, num);

    }else if(val == ")"){
      while(jerarquia(nextP(Aux))!= 1){
        push(Salida, nextP(Aux), Aux->tipo);
        pop(Aux);
      }
      pop(Aux);

    }else{
      push(Salida, val, num);
    }

    ListI= ListI->siguiente;
              
  }
  while(Aux!=NULL){
      push(Salida, nextP(Aux),Aux->tipo);
      pop(Aux);
  }
  
}

int PostOrder :: jerarquia(string c){
  int j = 0;
  string ob = c;

  if(ob == "^"){
    j = 4;
  }else if(ob == "*" || ob == "/"){
    j = 3;
  }else if(ob == "sen" || ob == "cos"|| ob == "tan"|| ob == "ctg"|| ob == "sec"|| ob == "csc"){
    j = 5;
  }else if(ob =="+" || ob =="-"){
    j = 2;
  }else if(ob == "("){
    j = 1;
  }else if(ob =="%"){
    j = 0;
  }
  return j;


}
#endif
