#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <iostream>
#include <math.h> 
#include <map>
#include "Arbol.h"

class Operation{
  
  using OpeMet = string (Operation::*)(string , string );
  string m_opeStr; // "+", "*", "/", etc
  OpeMet m_pOperationMethod;
  
  
  map<string, OpeMet > m_opeMap = {
        {"+", &Operation::suma},
        {"-", &Operation::resta},
        {"/", &Operation::division},
        {"*", &Operation::multip},
        {"^", &Operation::power},
        {"sen", &Operation::sin},
        {"cos", &Operation::cos},
        {"tan", &Operation::tan},
        {"ctg", &Operation::ctg},
        {"sec", &Operation::sec},
        {"csc", &Operation::csc},
      };
  
  public:
    Operation();
    string OperationResult(NodoA *&);
        string suma (string v1, string v2);
    string resta (string v1, string v2);
    string division (string v1, string v2);
    string multip (string v1, string v2);
    string power (string v1, string v2);
    string sin (string v1, string v2);
    string cos (string v1, string v2);
    string tan (string v1, string v2);
    string ctg (string v1, string v2);
    string sec (string v1, string v2);
    string csc (string v1, string v2);
};

Operation::Operation(){}

//OBTENER EL RESULTADO TOTAL DE LA OPERACIÓN
string Operation::OperationResult(NodoA *&arbol){ 
  OpeMet opElegida;
  if (arbol == NULL){
    return "";
    
  }else{
    m_opeStr = arbol->dat;
    
    map<string, OpeMet>::iterator it = m_opeMap.find(m_opeStr); 

    if(it != m_opeMap.end()){
      opElegida = m_opeMap[m_opeStr]; 
                       
      string v1 = OperationResult(arbol->der); 

      string v2 = OperationResult(arbol->izq);   
      
      return (this->*opElegida)(v1, v2);
                 
    }
    
  }
  return m_opeStr;

}


//DETERMINAR SI EL VALOR A OPERAR ES NÚMERO
bool isNumber(const string& str)
{
  string parteEntera;
  string parteDecimal;

  int valAbs;
  string Absol;
  valAbs = str.find_first_of("-");
  if(valAbs == 0){
    
    Absol = str.substr(valAbs+1);
  }

  int posPunto;
  //ENCUENTRA LA POSICIÓN DEL PUNTO "."
  posPunto = Absol.find_first_of(".");
  if(posPunto>0){
    parteEntera = Absol.substr(0,posPunto);//ENTERO VA DESDE EL INICIO HASTA EL PUNTO
    parteDecimal = Absol.substr(posPunto+1);//DECIMAL VA DESDE UNO DESPUÉS DEL PUNTO

  }else{
    parteEntera = Absol;
    parteDecimal = "0";
  }

  bool primer = true;
  bool segundo = true;

  //VERIFICAR SI EXISTE UN CARACTER NO NUMERICO
  
  for (char const &c : parteEntera) { //RECORRIDO DE LA PARTE ENTERA
    if (isdigit(c) == 0){
      primer = false;
    }
  }

  for (char const &c : parteDecimal) {//RECORRIDO DE LA PARTE DECIMAL
      if (isdigit(c) == 0){
        segundo = false;
      }
  }


  if(primer && segundo){//SI AMBOS SON NUMEROS
    return true;
  }else{ //SI UNO DE ELLOS NO ES NUMERO
    return false;
  }
  
}


//REALIZAR UNA SUMA DE LA OPERACIÓN COMBINADA
string Operation::suma (string v1, string v2){ 
  string resultado = "Variable detectada";
  
  if(isNumber(v1) && isNumber(v2)){
    float num1 = stof(v1);
    float num2 = stof(v2);
    float result = num1+num2;

    resultado = to_string(result);
  }
  return resultado; 
  
}


//REALIZAR UNA RESTA DE LA OPERACIÓN COMBINADA
string Operation::resta (string v1, string v2){
  string resultado = "Variable detectada";
  
  if(isNumber(v1) && isNumber(v2)){
    float num1 = stof(v1);
    float num2 = stof(v2);
    float result = num2-num1;

    resultado = to_string(result);
  }
  return resultado; 

}

//REALIZAR UNA DIVISIÓN DE LA OPERACIÓN COMBINADA
string Operation::division (string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1) && isNumber(v2)){
    float num1 = stof(v1);
    float num2 = stof(v2);
    float result = num2/num1;

    resultado = to_string(result);
  }
  return resultado; 


}

//REALIZAR UNA MULTIPLICACIÓN DE LA OPERACIÓN COMBINADA
string Operation::multip (string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1) && isNumber(v2)){
    float num1 = stof(v1);
    float num2 = stof(v2);
    float result = num1*num2;

    resultado = to_string(result);
  }
  return resultado; 

}

//REALIZAR UNA POTENCIA DE LA OPERACIÓN COMBINADA
string Operation::power (string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1) && isNumber(v2)){
    float num1 = stof(v1);
    float num2 = stof(v2);
    float result = pow(num2,num1);

    resultado = to_string(result);
  }
  return resultado; 

}

//ENCONTRAR EL SENO DE LA OPERACIÓN
string Operation::sin (string v1, string v2){
string resultado = "Variable detectada";
 
  if(isNumber(v1)){
    float num1 = stof(v1);
    
    float result = ::sin(num1);
    
    resultado = to_string(result);
    
  }
  return resultado; 

}

//ENCONTRAR EL COSENO DE LA OPERACIÓN
string Operation::cos (string v1, string v2){
  string resultado = "Variable detectada";
  
  if(isNumber(v1)){
    float num1 = stof(v1);
    
    float result = ::cos(num1);
    
    resultado = to_string(result);
    
  }
  return resultado; 

}

//ENCONTRAR EL TANGENTE DE LA OPERACIÓN
string Operation::tan (string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1)){
    float num1 = stof(v1);
    
    float result = ::tan(num1);
    
    resultado = to_string(result);
    
  }
  return resultado; 

}

//ENCONTRAR EL COTANGENTE DE LA OPERACIÓN
string Operation::ctg (string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1)){
    float num1 = stof(v1);
    float res = ::tan(num1);
    float result = 1/res;
    
    resultado = to_string(result);
    
  }
  return resultado; 

}

//ENCONTRAR EL SECANTE DE LA OPERACIÓN
string Operation::sec(string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1)){
    float num1 = stof(v1);
    float res = ::cos(num1);
    float result = 1/res;
    
    resultado = to_string(result);
    
  }
  return resultado; 

}

//ENCONTRAR EL COSECANTE DE LA OPERACIÓN
string Operation::csc (string v1, string v2){
 string resultado = "Variable detectada";
  
  if(isNumber(v1)){
    float num1 = stof(v1);
    float res = ::sin(num1);
    float result = 1/res;
    
    resultado = to_string(result);
    
  }
  return resultado; 

}
#endif

