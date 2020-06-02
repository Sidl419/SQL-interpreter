#ifndef EXEC
#define EXEC

#include "lex.h"
#include "syntax.h"
#include "Table.h"

#include <stack>
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

class Interpretator{
    Lex pc_el;
    int c_poliz;
    string c_table;
    THandle table;
    int size;
    Parser pars;

    stack<long> args;
    stack<string> str_args;

    void expression(Poliz& poliz);
    vector<bool> where();
    void execute();
    void gp(){
        c_poliz++;
        pc_el = pars.poliz[c_poliz];
        //cout << pc_el;
    }
public:
    Interpretator(const char *program):pars(program){
        c_poliz = 0;
    }
    void interpretation(){
        pars.analyze();
        size = pars.poliz.get_free();
        execute();
    }
};

#endif