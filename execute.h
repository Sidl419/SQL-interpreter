#ifndef EXEC
#define EXEC

#include "lex.h"
#include "syntax.h"

#include <stack>
#include <vector>

using namespace std;

class Executer{
public:
    void execute(Poliz & poliz);
};
class Interpretator{
    Parser pars;
    Executer E;
public:
    Interpretator(const char * program) : pars(program){};
    void interpretation();
};

#endif