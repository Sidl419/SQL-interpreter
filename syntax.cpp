#include "syntax.h"

using namespace std;

void Parser::P(){
    while(c_type == LEX_SELECT || c_type == LEX_INSERT || c_type == LEX_UPDATE 
        || c_type == LEX_DELETE || c_type == LEX_CREATE || c_type == LEX_DROP){
        switch(c_type){
            case LEX_SELECT:
                poliz.put_lex(curr_lex);  
                gl();
                SE();
                poliz.put_lex(POLIZ_SENTENCE);
                break;
            case LEX_INSERT:
                poliz.put_lex(curr_lex);  
                gl();
                IN();
                poliz.put_lex(POLIZ_SENTENCE);
                break;
            case LEX_UPDATE:
                poliz.put_lex(curr_lex);  
                gl();
                UP();
                poliz.put_lex(POLIZ_SENTENCE);
                break;
            case LEX_DELETE:
                poliz.put_lex(curr_lex);  
                gl();
                DE();
                poliz.put_lex(POLIZ_SENTENCE);
                break;
            case LEX_CREATE:
                poliz.put_lex(curr_lex); 
                gl();
                CR();
                poliz.put_lex(POLIZ_SENTENCE);
                break;
            case LEX_DROP:
                poliz.put_lex(curr_lex);  
                gl();
                DR();
                poliz.put_lex(POLIZ_SENTENCE);
                break;
            default:
                throw curr_lex;
        }
    }

    if (c_type != LEX_EXIT)
        throw curr_lex;
}

void Parser::SE() {
    if(c_type == LEX_TIMES){
        poliz.put_lex(Lex(LEX_ALLCOLS, LEX_ALLCOLS, "*"));
        gl();
    }else{
        if(c_type == LEX_ID){ //IDENT
            check_id();
            poliz.put_lex(curr_lex);
            gl();
            while (c_type == LEX_COMMA){ // ,
                gl();
                if (c_type != LEX_ID)
                    throw curr_lex;
                check_id();
                poliz.put_lex(curr_lex);  
                gl();
            }
        }else
            throw curr_lex;
    }

    if(c_type == LEX_FROM){
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;

    if(c_type == LEX_ID){ //IDENT
        check_id();
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;
    
    WH();
}

void Parser::IN() {
    if(c_type == LEX_INTO){
        gl();
    }
    else
        throw curr_lex;
    
    if(c_type == LEX_ID){ //IDENT
        check_id();
        TID[c_val].put_assign();
        poliz.put_lex(curr_lex);  
        gl();
    }else{
        throw curr_lex;
    }

    if(c_type == LEX_LPAREN){
        gl();
        CV();
        gl();
        while (c_type == LEX_COMMA){ // ,
            gl();
            CV();
            gl();
        }
        if(c_type != LEX_RPAREN){
            throw curr_lex;
        }
        gl();
    }else throw curr_lex; 
}

void Parser::UP(){
    if(c_type == LEX_ID){ //IDENT
        check_id();
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;

    if(c_type == LEX_SET){
        gl();
    }
    else
        throw curr_lex;

    if(c_type == LEX_ID){ //IDENT
        check_id();
        poliz.put_lex(curr_lex);  
        st_lex.push(TID[c_val].get_type());
        gl();
    }else
        throw curr_lex;

    if(c_type == LEX_EQ){
        gl();
    }
    else
        throw curr_lex;

    E();
    eq_type();

    WH();
}

void Parser::DE(){
    if(c_type == LEX_FROM){ 
        gl();
    }
    else
        throw curr_lex;

    if(c_type == LEX_ID){ //IDENT
        check_id();
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;

    WH();
}

void Parser::DR(){
    if(c_type == LEX_TABLE){
        gl();
    }
    else
        throw curr_lex;

    if(c_type == LEX_ID){ //IDENT
        check_id();
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;
}

void Parser::CR(){
    if(c_type == LEX_TABLE){
        gl();
    }
    else
        throw curr_lex;

    if(c_type == LEX_ID){ //IDENT
        st_int.push(c_val);
        dec(LEX_TABLE);
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;

    if(c_type == LEX_LPAREN){
        gl();
        DS();
        gl();
        while (c_type == LEX_COMMA){ // ,
            gl();
            DS ();
            gl();
        }
        if(c_type != LEX_RPAREN){
            throw curr_lex;
        }
        gl();
    }else throw curr_lex; 
}

void Parser::DS(){
    if(c_type == LEX_ID){ //IDENT
        st_int.push(c_val);
        poliz.put_lex(curr_lex);  
        gl();
    }else
        throw curr_lex;

    switch(c_type){
        case LEX_TEXT:
            poliz.put_lex(curr_lex);  
            dec(c_type);
            gl();
            if(c_type == LEX_LPAREN){
                gl();
                if(c_type == LEX_NUM){
                    poliz.put_lex(curr_lex);  
                    gl();
                    if(c_type != LEX_RPAREN)
                        throw curr_lex; 

                }else throw curr_lex; 

            }else throw curr_lex; 
            break;

        case LEX_LONG:
            poliz.put_lex(curr_lex);  
            dec(c_type);
            break;

        default:
            throw curr_lex; 
    }
}

void Parser::CV(){
    switch(c_type){
        case LEX_NUM:
            poliz.put_lex(curr_lex);
            break;
        case LEX_LETTER:
            poliz.put_lex(curr_lex);
            break;
        default:
            throw curr_lex; 
    }
}

void Parser::WH(){
    if(c_type == LEX_WHERE){
        poliz.put_lex(curr_lex);
        gl();
        if(c_type == LEX_ALL){
            poliz.put_lex(curr_lex);
            gl();
        }else{
            E();
            if(st_lex.top() != LEX_LOGIC){
                if(c_type == LEX_NOT){
                    poliz.put_lex(curr_lex);
                    gl();
                }

                if(c_type == LEX_IN){
                    poliz.put_lex(curr_lex);
                    gl();
                }else
                    throw curr_lex; 

                if(c_type == LEX_LPAREN){
                    gl();
                    if(c_type == LEX_NUM){
                        st_lex.push(LEX_LONG);
                        poliz.put_lex(curr_lex);
                        gl();
                        while (c_type == LEX_COMMA){ // ,
                            gl();
                            if(c_type == LEX_NUM)
                                poliz.put_lex(curr_lex); 
                            else
                                throw curr_lex;
                            gl();
                        }
                    }else{
                        if(c_type == LEX_LETTER){
                            st_lex.push(LEX_TEXT);
                            poliz.put_lex(curr_lex); 
                        }else
                            throw curr_lex;
                        gl();
                        while (c_type == LEX_COMMA){ // ,
                            gl();
                            if(c_type == LEX_LETTER)
                                poliz.put_lex(curr_lex); 
                            else
                                throw curr_lex;
                            gl();
                        }
                    }
                    if(c_type != LEX_RPAREN){
                        throw curr_lex;
                    }
                    eq_type();
                    gl();
                }else throw curr_lex; 
            }else{
                st_lex.pop();
            }
        }
    }else
        throw curr_lex;
}

void Parser::E(){
    E1();
    if((c_type == LEX_EQ) || (c_type == LEX_LSS) || (c_type == LEX_GTR) || 
    (c_type == LEX_LEQ) || (c_type == LEX_GEQ) || (c_type == LEX_NEQ)){
        st_lex.push(c_type);
        gl();
        E1();
        check_op();
    }
}

void Parser::E1(){
    T();
    while((c_type == LEX_PLUS) || (c_type == LEX_MINUS) || (c_type == LEX_OR)){
        st_lex.push(c_type);
        gl();
        T();
        check_op();
    }
}

void Parser::T(){
    F();
    gl();
    while((c_type == LEX_TIMES) || (c_type == LEX_AND) || (c_type == LEX_SLASH) || (c_type == LEX_MOD)){
        st_lex.push(c_type);
        gl();
        F();
        check_op();
        gl();
    }
}

void Parser::F(){
    switch(c_type){
        case LEX_ID:
            check_id();
            poliz.put_lex(curr_lex);
        break;

        case LEX_NUM:
            st_lex.push(LEX_LONG);
            poliz.put_lex(curr_lex);
        break;

        case LEX_LETTER:
            st_lex.push(LEX_TEXT); 
            poliz.put_lex(curr_lex);  
        break;

        case LEX_NOT:
            gl();
            F();
            check_not();
        break;

        case LEX_MINUS:
            gl();
            F();
            check_minus();
        break;

        case LEX_LPAREN:
            gl();
            E();
            if (c_type != LEX_RPAREN)
                throw curr_lex;
        break;

        default:
            throw curr_lex;
    }
}

template <typename T, typename T_EL> 
void from_st(T& t, T_EL & x){
    x = t.top();
    t.pop();
}

void Parser::dec(type_of_lex type){
    int i;
    while(!st_int.empty()){
        from_st(st_int, i);
        if(TID[i].get_declare())
            throw "ERROR: twice declaration";
        else{
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}

void Parser::check_id(){
    if(TID[c_val].get_declare())
        st_lex.push(TID[c_val].get_type());
    else
        throw "ERROR: not declared";
}

void Parser::check_op(){
    type_of_lex t1, t2, op, res = LEX_LOGIC;
    from_st(st_lex, t2);
    from_st(st_lex, op);
    from_st(st_lex, t1);

    if(op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH || op == LEX_MOD)
        if(t1 == LEX_LONG)
            res = LEX_LONG;

    if(op == LEX_OR || op == LEX_AND)
        res = LEX_LOGIC;

    if(op == LEX_EQ){
        if(t1 == LEX_LONG)
            res = LEX_LOGIC;

        if(t1 == LEX_LOGIC)
            res = LEX_LOGIC;

        if(t1 == LEX_TEXT)
            res = LEX_LOGIC;
    }

    if(op == LEX_LSS || op == LEX_GTR || op == LEX_LEQ || op == LEX_GEQ){
        if(t1 == LEX_TEXT)
            res = LEX_LOGIC;

        if(t1 == LEX_LONG)
            res = LEX_LOGIC;
    }

    if(t1 == t2)
        st_lex.push(res);
    else
        throw "wrong types in operation";

    poliz.put_lex(Lex(op, op));
}

void Parser::check_not(){
    if(st_lex.top() != LEX_LOGIC)
        throw "NOT requires logical statement";
    else
        poliz.put_lex(Lex(LEX_NOT));
}

void Parser::check_minus(){
    if(st_lex.top() != LEX_LONG)
        throw "unary minus requires number";
    else
        poliz.put_lex(Lex(LEX_UNMINUS));
}

void Parser::eq_type(){
    type_of_lex t; 
    from_st(st_lex, t);
    if(t != st_lex.top())
        throw "wrong types in =";
        
    st_lex.pop();
}

void Parser::eq_bool(){
    if(st_lex.top() != LEX_LOGIC)
        throw "ERROR: expression is not boolean";
    st_lex.pop();
}