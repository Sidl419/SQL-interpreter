#include "lex.h"
#include "syntax.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main(){
    try{
        int y = 2;
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
        
        else if(y == 2){
            Parser Par("mytest.txt");
            Par.analyze();
            Par.poliz.print();
        }

        /*
        else if(y == 3){
            Interpretator I("mytest.txt");
            I.interpretation();
        }
        */
            
    	return 0;
    }
    catch(char c){
        cout << "\nunexpected symbol " << c << endl;
        return 1;
    }
    catch(Lex l){
        cout << "\nunexpected lexeme " << l << endl;
        return 1;
    }
    catch(const char *source){
        cout << source << endl;
        return 1;
    }
    catch(...){
        cout << "\nUnknown error" << endl;
        return 1;
    }
    return 0;
}