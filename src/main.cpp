#ifndef ___EXPRESSION_H__
#define ___EXPRESSION_H__
#include "operator.h"
#include <thread>
#include <future>
using std::string;
using std::thread;
using std::future;
using std::launch;
using std::promise;

class Expression
{
public:
    Expression* left;
    Expression* right;
    Expression(Expression* left_=nullptr, Expression* right_=nullptr):left(left_), right(right_) {}
    virtual ~Expression() {};
    virtual string toString() const = 0;
    virtual int evaluate() const = 0;
    //Version asincrona, utilizando future y async
    virtual int asyncEvaluate() const = 0;
    //Version asincrona, utilizando thread, future y promise.
    virtual void asyncEvaluate2(promise<int>* p) const = 0;
};


class NumberExpression : public Expression
{
public:
    int value;
    NumberExpression(const int value_):Expression(), value(value_) {}
    string toString()
    const
    {
        return std::to_string(value);
    }
    int evaluate() const
    {
        std::cout<<"Number: "<<value<<std::endl;
        return value;
    }
    int asyncEvaluate() const
    {
        std::cout<<"Number : "<<value<<std::endl;
        return value;
    }

  //Se asigna la respuesta en el puntero promise.
    void asyncEvaluate2(promise<int>* p) const
    {
        std::cout<<"Number : "<<value<<std::endl;
        p->set_value(value);
    }

};

class BinaryExpression : public Expression
{
public:
    char operator_;
    BinaryExpression(const char oper, Expression* const left_ = 0, Expression* const right_ = 0):Expression(left_, right_), operator_(oper) {}
    string toString()
    const
    {
        return string{operator_};
    }

    int evaluate() const
    {
        if(operatorMap.count(operator_) > 0)
        {
            std::cout<<"Start Binary expression: "<<operator_<<std::endl;
            int result  = operatorMap[operator_](left->evaluate(), right->evaluate());
            std::cout<<"End Binary expression: "<<operator_<<" Resultado: "<<result<<std::endl;
            return result;
        }
        return 0;
    }

    //Se calcula los resultado de las ramas izquierda y derecha de forma asincrona (paralela)
    //Se usa la funcion async para crear el thread y el objeto future devuelto por esta funcion
    //El objeto future tendra el valor calculado, una vez que finalice el thread de ejecutarse.
    int asyncEvaluate() const
    {
        if(left && right)
        {
            if(operatorMap.count(operator_) > 0)
            {
                std::cout<<"Start Binary expression: "<<operator_<<std::endl;
                auto future_leftValue = std::async(launch::async, &Expression::asyncEvaluate, left);
                auto future_rigthValue = std::async(launch::async, &Expression::asyncEvaluate, right);
                const int leftValue = future_leftValue.get();
                const int rightValue = future_rigthValue.get();
                int result =operatorMap[operator_](leftValue, rightValue);
                std::cout<<"End Binary expression: "<<operator_<<" Resultado: "<<result<<std::endl;
                return result;
            }
            else
            {
                throw std::runtime_error("Error: Operator not supported.");
            }
        }
        else
        {
            throw std::runtime_error("Error: Invalid Expression");
        }
    }

    //esta version utiliza threads
    //de esta forma como no es posible devolver directamente el valor del resultado desde el thread
    //se crean punteros de promises y se pasan por parametro a la funcion que se ejecutara en el thread
    //Se obtienen previamente los objetos futures de los punteros promises, para obtener el resultado una vez calculado
    //Una vez se calcula el nuevo resultado se setea el valor en el puntero promise pasado por parametro.
    void asyncEvaluate2(promise<int>* p) const
    {
        if(left && right)
        {
            if(operatorMap.count(operator_) > 0)
            {
                std::cout<<"Start Binary expression: "<<operator_<<std::endl;
                promise<int> promise_left, promise_right;
                auto future_left = promise_left.get_future();
                thread thread_left(&Expression::asyncEvaluate2, left, &promise_left);
                auto future_right= promise_right.get_future();
                thread thread_right(&Expression::asyncEvaluate2, right, &promise_right);

                const int leftValue = future_left.get();
                const int rightValue = future_right.get();
                int result =operatorMap[operator_](leftValue, rightValue);
                p->set_value(result);

                //se esperan que terminen los threads izquierda y derecha para termnar la funcion
                if(thread_left.joinable())
                {
                    thread_left.join();
                }
                if(thread_right.joinable())
                {
                    thread_right.join();
                }

                std::cout<<"End Binary expression: "<<operator_<<" Resultado: "<<result<<std::endl;
            }
            else
            {
                throw std::runtime_error("Error: Operator not supported.");
            }
        }
        else
        {
            throw std::runtime_error("Error: Invalid Expression");
        }
    }
};

class ExpressionTree
{
public:
    const int evaluate();
    const int asyncEvaluate();
    const int asyncEvaluate2();
    ExpressionTree(const char*);
    void recorridoInorden();
    void recorridoPostOrden();
    void recorridoPreOrden();
private:
    const Expression* root;
    const Expression* buildTree(const char*&);
    Expression* parseNumero(const char*&);
    Expression* parseParentesis(const char*&);
    Expression* parseSumandos(const char*&);
    Expression* parseFactores(const char*&);
    void inorden(const Expression*);
    void postorden(const Expression*);
    void preorden(const Expression*);
};

const Expression* ExpressionTree::buildTree(const char*&s)
{
    return parseSumandos(s);
}

ExpressionTree::ExpressionTree(const char* input)
{
    root = buildTree(input);
}
const int ExpressionTree::evaluate()
{
    return root->evaluate();
}

const int ExpressionTree::asyncEvaluate()
{
    return root->asyncEvaluate();
}

const int ExpressionTree::asyncEvaluate2()
{
    promise<int> result;
    future<int> future_result = result.get_future();
    root->asyncEvaluate2(&result);
    return future_result.get();
}

Expression* ExpressionTree::parseNumero(const char*& s)
{
    NumberExpression* numExpr = new NumberExpression(0);
    while(*s && std::isdigit(*s))
    {
        numExpr->value = numExpr->value* 10 + *s++ - '0';
    }
    return numExpr;
}


Expression* ExpressionTree::parseParentesis(const char*& s)
{
    if(*s == 0)
    {
        throw std::runtime_error("Error: Invalid Expression.");
    }
    else if(*s == '(')
    {
        s++;
        Expression* expr = parseSumandos(s);
        if(*s == ')')
        {
            s++;
            return expr;
        }
        throw std::runtime_error("Error: Parentesis no balanceados");
    }
    else if(std::isdigit(*s))
    {
        Expression* expr = parseNumero(s);
        return expr;
    }
    throw std::runtime_error("Error: Character invalid.");
}

Expression* ExpressionTree::parseFactores(const char*&s)
{
    Expression* left = parseParentesis(s);
    while(*s)
    {
        if(*s == '*')
        {
            s++;
            Expression* right = parseParentesis(s);
            left = new BinaryExpression('*', left, right);
            continue;

        }
        else if(*s == '/')
        {
            s++;
            Expression* right = parseParentesis(s);
            left = new BinaryExpression('/', left, right);
            continue;
        }
        return left;
    }
    return left;
}


Expression* ExpressionTree::parseSumandos(const char*& s)
{
    Expression* left = parseFactores(s);
    while(*s)
    {
        if(*s=='+')
        {
            s++;
            Expression* right = parseFactores(s);
            left = new BinaryExpression('+', left, right);
            continue;
        }
        else if(*s == '-')
        {
            s++;
            Expression* right = parseFactores(s);
            left = new BinaryExpression('-', left, right);
            continue;
        }
        return left;
    }
    return left;
}

void ExpressionTree::inorden(const Expression* expr)
{
    if(expr)
    {
        inorden(expr->left);
        std::cout<<expr->toString()<<" ";
        inorden(expr->right);
    }
}

void ExpressionTree::recorridoInorden()
{
    inorden(root);
    std::cout<<std::endl;
}

void ExpressionTree::preorden(const Expression* expr)
{
    if(expr)
    {
        std::cout<<expr->toString()<<" ";
        preorden(expr->left);
        preorden(expr->right);
    }
}

void ExpressionTree::recorridoPreOrden()
{
    preorden(root);
    std::cout<<std::endl;
}

void ExpressionTree::postorden(const Expression* expr)
{
    if(expr)
    {
        postorden(expr->left);
        postorden(expr->right);
        std::cout<<expr->toString()<<" ";

    }
}

void ExpressionTree::recorridoPostOrden()
{
    postorden(root);
    std::cout<<std::endl;
}

#endif // ___EXPRESSION_H__
