//
//  main.cpp
//  Iterative method
//
//  Created by Владимир Афанасьев on 03.12.2019.
//  Copyright © 2020 Владимир Афанасьев. All rights reserved.
//

#include<stdlib.h>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
ofstream out("out.txt");
class Expression {
public:
    virtual Expression *dif() = 0;
    virtual void print() = 0;
};
class Number :public Expression
{
public:
    double e;
    
    Number(double n) : e(n) {}
    Expression*dif()
    {
        
        
        return new Number(0);
        
    }
    void print()
    {
        out<< e;
    }
    
};
Expression *Nl = new Number(0);

class Variable :public Expression
{
    char X;
public:
    Variable(char c) :X(c){}
    Expression*dif()
    {
        return new Number(1);
        
    }
    void print()
    {
        out<< X;
    };
};

class Add :public Expression
{
    Expression*m1, *m2;
public:
    Add(Expression*L1, Expression*L2) : m1(L1), m2(L2) {}
    Expression*dif()
    {
        return new Add(m1->dif(), m2->dif());
        
    };
    void print(){
        m1->print();
        out << "+";
        m2->print();
    }
};

class Mul :public Expression
{
    Expression*e1;
    Expression *e2;
public:
    Mul(Expression*L1, Expression*L2) : e1(L1), e2(L2) {}
    Expression*dif()
    {
        return new Add(new Mul(e1->dif(), e2), new Mul(e1, e2->dif()));
        
    };
    void print(){
        e1->print();
        out << "*";
        e2->print();
    }
    
};
class Sub :public Expression
{
    Expression*m1, *m2;
public:
    Sub(Expression*L1, Expression*L2) : m1(L1), m2(L2) {}
    Expression*dif()
    {
        return new Sub(m1->dif(), m2->dif());
        
    };
    void print(){
        m1->print();
        out << "-";
        m2->print();
    }
};

class Res :public Expression
{
    Expression*e1;
    Expression *e2;
public:
    Res(Expression*L1, Expression*L2) : e1(L1), e2(L2) {}
    Expression*dif()
    {
        return new Res(new Sub(new Mul(e1->dif(), e2), new Mul(e1, e2->dif())), new Mul(e2, e2));
        
    };
    void print(){
        out << "(";
        e1->print();
        out << ")";
        out << "/";
        out << "(";
        e2->print();
        out << ")";
        
    }
};
class Pow :public Expression{
    Expression* arg;
    double p;
public:
    Pow(Expression*arg1,double p1) :arg(arg1),p(p1){}
    Expression*dif(){
        return new Mul(new Number(p), new Pow(arg, p-1));
    }
    void print(){
        arg->print();
        out << "^" << p;
    }
};
class Exp : public Expression{
    Expression*e;
public:
    Exp(Expression*e1) :e(e1){}
    Expression*dif()
    {
        return new Mul(e->dif(),new Exp(e));
    }
    void print(){
        out << "e^";
        out << "(";
        e->print();
        out << ")";
    }
};
int main()
{
    Expression* l = new Pow(new Variable('x'), 3);
    Expression* j = new Res(new Number(3), new Variable('x'));
    Expression* k = new Exp(new Mul(new Number(3) ,new Variable('x')));
    Expression*i = new Add(l, k);
    i->print();
    out << endl;
    Expression*di = i->dif();
    di->print();
    out << endl;
    Expression *d2i = di->dif();
    d2i->print();
    out << endl;
    //Expression *d3i = d2i->dif();
    //d3i->print();
    //out << endl;
    system("pause");
    return 0;
    
}
