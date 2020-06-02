#include "execute.h"

using namespace std;

template <typename T, typename T_EL> 
void from_st(T& t, T_EL & x){
    x = t.top();
}

void Interpretator::expression(Poliz& poliz){
    Lex local_pol;
    string buf_1, buf_2;
    long i, j;
    int exp_size = poliz.size(), index = 0;
    try{
        while(index < exp_size){
            local_pol = poliz[index];
            switch(local_pol.get_type()){
                case LEX_NUM:
                    args.push(local_pol.get_value());
                    break;
                case LEX_LETTER:
                    str_args.push(local_pol.get_string());
                    break;
                case LEX_NULL:
                    break;
                case LEX_ID:{
                    i = local_pol.get_value();

                    if((TID[i].get_type() == LEX_TEXT)){ 
                        char *buf;
                        getText(table, (char *) local_pol.get_string().c_str(), &buf);
                        str_args.push(buf);
                    }else{ 
                        getLong(table, (char *) local_pol.get_string().c_str(), &j);
                        args.push(j);
                    }
                    break;
                }
                case LEX_NOT:
                    from_st(args, i);
                    args.pop();
                    args.push(!i);
                    break;
                case LEX_UNMINUS:
                    from_st(args, i);
                    args.pop();
                    args.push(-i);
                    break;
                case LEX_OR:
                    from_st(args, i);
                    args.pop();
                    from_st(args, j);
                    args.pop();
                    args.push(i || j);
                    break;
                case LEX_AND:
                    from_st(args, i);
                    args.pop();
                    from_st(args, j);
                    args.pop();
                    args.push(i && j);
                    break;
                case LEX_PLUS:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(i + j);
                    }else{
                        from_st(str_args, buf_1);
                        str_args.pop();
                        from_st(str_args, buf_2);
                        str_args.pop();
                        str_args.push(buf_2 + buf_1); 
                    }
                    break;
                case LEX_TIMES:
                    from_st(args, i);
                    args.pop();
                    from_st(args, j);
                    args.pop();
                    args.push (i * j);
                    break;
                case LEX_MINUS:
                    from_st(args, i);
                    args.pop();
                    from_st(args, j);
                    args.pop();
                    args.push(j - i);
                    break;
                case LEX_SLASH:
                    from_st(args, i);
                    args.pop();
                    from_st(args, j);
                    args.pop();
                    if(i){ 
                        args.push (j / i); 
                        break; 
                    }else
                        throw "poliz: division by zero";
                case LEX_MOD:
                    from_st(args, i);
                    args.pop();
                    from_st(args, j);
                    args.pop();
                    if(i){ 
                        args.push(j % i); 
                        break; 
                    }else 
                        throw "poliz: division by zero";
                case LEX_EQ:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(i == j); 
                    }else{
                        from_st(str_args, buf_1);
                        str_args.pop();
                        from_st(str_args, buf_2);
                        str_args.pop();
                        args.push(buf_1 == buf_2);
                    }
                    break;
                case LEX_GEQ:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(j >= i); 
                    }else{
                        from_st(str_args, buf_1);
                        str_args.pop();
                        from_st(str_args, buf_2);
                        str_args.pop();
                        args.push(buf_2 >= buf_1);
                    }
                    break;
                case LEX_LEQ:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(j <= i); 
                    }else{
                        from_st(str_args, buf_1);
                        str_args.pop();
                        from_st(str_args, buf_2);
                        str_args.pop();
                        args.push(buf_2 <= buf_1);
                    }
                    break;
                case LEX_LSS:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(j < i); 
                    }else{
                        from_st(str_args, buf_1);
                        str_args.pop();
                        from_st(str_args, buf_2);
                        str_args.pop();
                        args.push(buf_2 < buf_1);
                    }
                    break;
                case LEX_GTR:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(j > i); 
                    } 
                    else{
                        from_st (str_args, buf_1);
                        str_args.pop();
                        from_st (str_args, buf_2);
                        str_args.pop();
                        args.push (buf_2 > buf_1);
                    }
                    break;
                case LEX_NEQ:
                    if(str_args.empty()){
                        from_st(args, i);
                        args.pop();
                        from_st(args, j);
                        args.pop();
                        args.push(j != i); 
                    }else{
                        from_st(str_args, buf_1);
                        str_args.pop();
                        from_st(str_args, buf_2);
                        str_args.pop();
                        args.push(buf_2 != buf_1);
                    }
                    break;
                default:
                    throw 0;
            }
            ++index;
        }
    }catch(int a){}
}

vector<bool> Interpretator::where(){
    long t;
    vector<bool> res;

    gp();
    Poliz exp(1000);
    if(pc_el.get_type() == LEX_ALL){
        while(!afterLast(table)){
            res.push_back(1);
            moveNext(table);
        }
        gp();
    }else{
        while((pc_el.get_type() != POLIZ_SENTENCE) && (pc_el.get_type() != LEX_IN) && (pc_el.get_type() != LEX_NOT)){
            exp.put_lex(pc_el);
            gp();
        }
        moveFirst(table);
        if(pc_el.get_type() != POLIZ_SENTENCE){
            int flag = 0;
            
            if(pc_el.get_type() == LEX_NOT){
                flag = 1;
                gp();
            }
            gp();

            if(pc_el.get_type() == LEX_NUM){
                vector<int> constants;
                long l;
                while(pc_el.get_type() != POLIZ_SENTENCE){
                    constants.push_back(pc_el.get_value());
                    gp();
                }
                while(!afterLast(table)){
                    expression(exp);
                    from_st(args, l);
                    if(flag){
                        t = 1;
                        for(int i = 0; i < constants.size(); i++){
                            if(l == constants[i])
                                t = 0;
                        }
                    }else{
                        t = 0;
                        for(int i = 0; i < constants.size(); i++){
                            if(l == constants[i])
                                t = 1;
                        }
                    }
                    res.push_back(t);
                    moveNext(table);
                }
            }else{
                vector<string> constants;
                string str;
                while(pc_el.get_type() != POLIZ_SENTENCE){
                    constants.push_back(pc_el.get_string());
                    gp();
                }
                while(!afterLast(table)){
                    expression(exp);
                    from_st(str_args, str);
                    if(flag){
                        t = 1;
                        for(int i = 0; i < constants.size(); i++){
                            if(str == constants[i])
                                t = 0;
                        }
                    }else{
                        t = 0;
                        for(int i = 0; i < constants.size(); i++){
                            if(str == constants[i])
                                t = 1;
                        }
                    }
                    res.push_back(t);
                    moveNext(table);
                }
            }
        }else{
            while(!afterLast(table)){
                expression(exp);
                from_st(args, t);
                res.push_back(t);
                moveNext(table);
            }
        }
    }
    return res;
}

void Interpretator::execute(){
    pc_el = pars.poliz[c_poliz];
    while(c_poliz < size){
        switch(pc_el.get_type()){
            case LEX_CREATE:{
                vector<struct FieldDef> table;
                gp();
                c_table = pc_el.get_string();
                gp();
                while(pc_el.get_type() != POLIZ_SENTENCE){
                    struct FieldDef temp;
                    strcpy(temp.name, pc_el.get_string().c_str());
                    gp();
                    if(pc_el.get_type() == LEX_TEXT){
                        temp.type = Text;
                        gp();
                        temp.len = pc_el.get_value();
                    }else{
                        temp.type = Long;
                        temp.len = 10;
                    }
                    table.push_back(temp);
                    gp();
                }

                struct TableStruct temp;
                temp.numOfFields = table.size();
                temp.fieldsDef = table.data();
                createTable((char *) c_table.c_str(), &temp);

                break;
            }
            case LEX_DROP:
                gp();
                c_table = pc_el.get_string();
                deleteTable((char *) c_table.c_str());
                gp();
                break;
            case LEX_INSERT:{
                gp();
                c_table = pc_el.get_string();
                openTable((char *) c_table.c_str(), &table);
                createNew(table);

                unsigned len;
                getFieldsNum(table, &len);
                vector<string> fieldNames;
                char* name;
                for(int i = 0; i < len; i++){
                    getFieldName(table, i, &name);
                    fieldNames.push_back(name);
                }

                int i = 0;
                gp();
                while(pc_el.get_type() != POLIZ_SENTENCE){
                    if((pc_el.get_type() == LEX_LETTER) || (pc_el.get_type() == LEX_TEXT)){
                        putTextNew(table, (char *) fieldNames[i].c_str(), (char *) pc_el.get_string().c_str());
                    }else
                        putLongNew(table, (char *) fieldNames[i].c_str(), pc_el.get_value());
                    i++;
                    gp();
                }

                insertzNew(table);
                closeTable(table);
                break;
            }
            case LEX_DELETE:{
                gp();
                c_table = pc_el.get_string();
                openTable((char *) c_table.c_str(), &table);
                gp();
                vector<bool> wh = where();
                moveFirst(table);
                for(int i = 0; i < wh.size(); i++){
                    if(wh[i])
                        deleteRec(table);
                    moveNext(table);
                }
                closeTable(table);
                break;
            }
            case LEX_UPDATE:{
                gp();
                c_table = pc_el.get_string();
                openTable((char *) c_table.c_str(), &table);
                gp();
                string active_column = pc_el.get_string();
                type_of_lex column_type = TID[pc_el.get_value()].get_type();
                gp();
                Poliz assign_exp(1000);
                while(pc_el.get_type() != LEX_WHERE){
                    assign_exp.put_lex(pc_el);
                    gp();
                }
                vector<bool> wh = where();
                moveFirst(table);
                for(int i = 0; i < wh.size(); i++){
                    if(wh[i]){
                        expression(assign_exp);
                        startEdit(table);
                        if(column_type == LEX_TEXT){
                            string buf;
                            from_st(str_args, buf);
                            putText(table, (char *) active_column.c_str(), (char *) buf.c_str());
                        }else{
                            long buf;
                            from_st(args, buf);
                            putLong(table, (char *) active_column.c_str(), buf);
                        }
                        finishEdit(table);
                    }
                    moveNext(table);
                }
                closeTable(table);
                break;
            }
            case LEX_SELECT:
                bool all = false;
                vector<string> columns;
                gp();
                if(pc_el.get_type() == LEX_ALLCOLS){
                    all = true;
                    gp();
                }else{
                    while(pc_el.get_type() != LEX_FROM){
                        columns.push_back(pc_el.get_string());
                        gp();
                    }
                }
                gp();
                c_table = pc_el.get_string();
                openTable((char *) c_table.c_str(), &table);

                if(all){
                    unsigned len;
                    getFieldsNum(table, &len);
                    char* name;
                    for(int i = 0; i < len; i++){
                        getFieldName(table, i, &name);
                        columns.push_back(name);
                    }
                }

                gp();
                vector<bool> wh = where();
                moveFirst(table);

                int width = 0;
                unsigned b;
                vector<unsigned> col_w;
                FieldType type;
                long pvalue;
                char *buf;

                for(int i = 0; i < columns.size(); i++){
                    getFieldLen(table, (char *) columns[i].c_str(), &b);
                    width += b + 1;
                    b = max(b,(unsigned) columns[i].size());
                    col_w.push_back(b);
                }
                cout << ' ';
                for(int i = 0; i < width - 1; i++){
                    cout << '-';
                }
                cout << endl;
                for(int i = 0; i < columns.size(); i++){
                    cout << '|';
                    cout << columns[i];
                    for(int j = 0; j < col_w[i] - columns[i].size(); j++)
                        cout << ' ';
                }
                cout << '|' << endl << ' ';
                for(int i = 0; i < width - 1; i++){
                    cout << '-';
                }
                cout << endl;
                int length;
                for(int i = 0; i < wh.size(); i++){
                    if(wh[i]){
                        for(int i = 0; i < columns.size(); i++){
                            cout << '|';
                            getFieldType(table, (char *) columns[i].c_str(), &type);
                            if(type == Text){
                                getText(table, (char *) columns[i].c_str(), &buf);
                                cout << buf;
                                length = strlen(buf);
                            }else{
                                getLong(table, (char *) columns[i].c_str(), &pvalue);
                                cout << pvalue;
                                length = to_string(pvalue).length();
                            }
                            for(int j = 0; j < col_w[i] - length; j++)
                                cout << ' ';
                        }
                        cout << '|' << endl;
                    }
                    moveNext(table);
                }
                cout << ' ';
                for(int i = 0; i < width - 1; i++){
                    cout << '-';
                }
                cout << endl << endl;
                closeTable(table);
                break;
        }
        gp();
    }
}