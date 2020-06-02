#ifndef POLIZ
#define POLIZ

#include "lex.h"

#include <stack>
#include <vector>

using namespace std;

class Poliz {
    Lex *p;
    int sizen;
    int free;
public:
    Poliz(int maxxx){
        sizen = maxxx;
        p = new Lex[sizen];
        free = 0;
    }
    ~Poliz() {delete []p;}

    int size() {return sizen;}
    void put_lex(Lex l){ 
        p[free]=l;
        ++free; 
    }
    void put_lex(Lex l, int place) {p[place]=l;}
    void blank() {++free;}
    int get_free() {return free;}
    Lex& operator[] (int index);
    void operator=(Poliz& A);
    void print();
};

#endif