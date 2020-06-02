#ifndef LEX
#define LEX

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#define TWlen 23
#define TDlen 14

using namespace std;

enum type_of_lex{
    LEX_NULL,       //0 NULL
    LEX_AND,        //1 AND
    LEX_SELECT,     //2 SELECT
    LEX_LOGIC,      //3 LOGIC
    LEX_INSERT,     //4 INSERT
    LEX_UPDATE,     //5 UPDATE
    LEX_DELETE,     //6 DELETE
    LEX_FALSE,      //7 FALSE
    LEX_LONG,       //8 LONG
    LEX_NOT,        //9 NOT
    LEX_OR,         //10 OR
    LEX_CREATE,     //11 CREATE
    LEX_DROP,       //12 DROP
    LEX_TRUE,       //13 TRUE
    LEX_WHERE,      //14 WHERE
    LEX_TABLE,      //15 TABLE
    LEX_INTO,       //16 INTO
    LEX_FROM,       //17 FROM
    LEX_SET,        //18 SET
    LEX_IN,         //19 IN
    LEX_ALL,        //20 ALL
    LEX_TEXT,       //21 TEXT
    LEX_EXIT,       //22 EXIT
    LEX_COMMA,      //23 ,
    LEX_LPAREN,     //24 (
    LEX_RPAREN,     //25 )
    LEX_EQ,         //26 =
    LEX_LSS,        //27 <
    LEX_GTR,        //28 >
    LEX_PLUS,       //29 +
    LEX_MINUS,      //30 -
    LEX_TIMES,      //31 *
    LEX_SLASH,      //32 /
    LEX_LEQ,        //33 <=
    LEX_NEQ,        //34 !=
    LEX_GEQ,        //35 >=
    LEX_MOD,        //36 %
    LEX_ALLCOLS,    //37 * (в таблице)
    LEX_UNMINUS,    //38 - (унарный)
    LEX_NUM,        //39 число
    LEX_ID,         //40 идентификатор
    LEX_LETTER,     //41 сообщение в кавычках
    POLIZ_SENTENCE, //42 конец SQL-предложения
};

class Lex{
    type_of_lex t_lex;
    int v_lex;
    string name_of_lex;
public:
    Lex(type_of_lex t = LEX_NULL, int v = 0, string n = ""){
        t_lex = t;
        v_lex = v;
        name_of_lex = n;
    }

    type_of_lex get_type() const {return t_lex;}
    int get_value(){return v_lex;}
    string get_string(){return name_of_lex;}
    friend ostream& operator<< (ostream & s, Lex l);
};

class Ident{
    string name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
public:
    Ident(){ 
        declare = false; 
        assign = false; 
    }

    Ident(const string nam){
        name = nam; 
        declare = false; 
        assign = false; 
    }

    bool operator== (const string& s) const {return name == s;}
    string get_name() {return name;}
    bool get_declare() {return declare;}
    void put_declare() {declare = true;}
    type_of_lex get_type() {return type;}
    void put_type(type_of_lex t) {type = t;}
    bool get_assign() {return assign;}
    void put_assign() {assign = true;}
    int get_value() {return value;}
    void put_value(int v) {value = v;}
};

extern vector <Ident> TID;

int put(const string & buf);

class Scanner{
    FILE *fp;
    char c;
    int look(const string& buf, string *list, int n){
        int i = 0;
        while (i < n) {
            if (buf == list[i]){
                return i;
            }
            i++; 
        }
        return 0; 
    }

    void gc(){ 
        c = fgetc(fp); 
    }

public:
    static string TW[], TD[];
    Scanner(const char *program){
        fp = fopen(program, "r");
    }
    Lex get_lex();
};

#endif