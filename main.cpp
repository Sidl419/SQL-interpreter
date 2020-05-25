#include "lex.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main(){
    try{
        int y = 1;
        //cout << "What part do you want to test? (1 - lexical, 2 - syntax, 3 - execute)" << endl;
        //cin >> y;
        if(y == 1){
            Scanner scan("mytest.txt");
            Lex H = scan.get_lex();
            cout << H << endl;
            while(H.get_type() != LEX_EXIT){
                H = scan.get_lex();
                cout << H << endl;
            }
                
        }
            
    	return 0;
    }
    catch(char c){
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch(Lex l){
        cout << "unexpected lexeme" << l << endl;
        return 1;
    }
    catch(const char *source){
        cout << source << endl;
        return 1;
    }
    catch(...){
        cout << "Unknown error" << endl;
        return 1;
    }
    return 0;
}