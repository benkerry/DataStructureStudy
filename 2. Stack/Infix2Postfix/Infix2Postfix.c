#include"Infix2Postfix.h"

int Power(int origin, int up){
    int result = 1;
    
    for(int i = 0; i < up; i++){
        result *= origin;
    }
    return result;
}

int Strlen(char *str){
    int strlen = 0;
    
    while(str[strlen]){
        strlen++;
    }
    
    return strlen;
}

char* Strcat(char *src, char *add){
    int srclen = Strlen(src);
    int addlen = Strlen(add);
    char* result = (char*)malloc(sizeof(char) * (srclen + addlen + 1));
    
    for(int i = 0; i < srclen; i++)
        result[i] = src[i];
    for(int i = 0; i < addlen; i++)
        result[srclen + i] = add[i];
    result[srclen + addlen] = '\0';
    
    return result;
}

int Find(char tgt, char* src){
    int i = 0;
    
    while(src[i] != '\0'){
        if(tgt == src[i]){
            return i;
        }
        i++;
    }
    
    return -1;
}

char* StrFliper(char *str){
    char tmp;
    int strlen = Strlen(str);
    
    for(int i = 0; i < strlen / 2; i++){
        tmp = str[i];
        str[i] = str[strlen - i - 1];
        str[strlen - i - 1] = tmp;
    }
    
    return str;
}

int Search(char *tgt, char *src){
    int tgtlen = Strlen(tgt);
    int srclen = Strlen(src);
    int index = 0;
    char isSubstring = 0;
    
    while(tgtlen <= srclen - index){
        if(tgt[0] == src[index]){
            isSubstring = 1;
            for(int i = 0; i < tgtlen; i++){
                if(tgt[i] != src[index + i]){
                    isSubstring = 0;
                    break;
                }
            }
        }
        
        if(isSubstring)
            return index;
        
        index++;
    }
    return -1;
}

int IsDigit(char ch){
    if('0' <= ch && ch <= '9')
        return 1;
    else
        return 0;
}

int ctoi(char ch){
    return ch - 48;
}

char itoc(int i){
    return i + 48;
}

int strtoi(char *str){
    int result = 0;
    int strlen = Strlen(str);
    
    for(int i = 0; i < strlen; i++){
        result += ctoi(str[i]) * Power(10, strlen - i - 1);
    }
    
    return result;
}

char* itostr(int i){
    int num;
    int strPointer = 0;
    int cutter;
    char *str = (char*)malloc(sizeof(char) * MAX_EXP_LEN);
    
    while(i){
        num = (cutter = i % Power(10, strPointer + 1)) / Power(10, strPointer);
        i -= cutter;
        str[strPointer++] = itoc(num);
    }
    str[strPointer] = '\0';
    
    return StrFliper(str);
}

char* chartostr(char ch){
    char *result = (char*)malloc(sizeof(char) * 2);
    result[0] = ch;
    result[1] = '\0';
    
    return result;
}

int OpPriority(char ch){
    if(ch == '+' || ch == '-'){
        return 1;
    }
    else if(ch == '*' || ch == '/'){
        return 2;
    }
    else{
        return 0;
    }
}

void SetExpInfo(ExpInfo *info){
    int i;
    int opPointer = 0;
    int paramPointer = 0;
    int numOfParams = 0;
    int *params;
    char tempParams[MAX_EXP_LEN + MAX_EXP_LEN / 10];
    char *tempParam = chartostr('\0');
    char *del, *add;
    
    info->operators = (char*)malloc(sizeof(char) * MAX_EXP_LEN);
    
    for(i = 0; i < Strlen(info->raw_exp); i++){
        if(IsDigit(info->raw_exp[i])){
            tempParams[i] = info->raw_exp[i];
        }
        else{
            info->operators[opPointer++] = info->raw_exp[i];
            tempParams[i] = '\0';
            numOfParams++;
        }
    }
    tempParams[i] = '?';
    info->operators[opPointer] = '\0';
    numOfParams++;
    params = (int*)malloc(sizeof(int) * numOfParams);
    
    i = 0;
    
    while(1){
        if(tempParams[i] != '\0' && tempParams[i] != '?'){
            del = tempParam;
            add = chartostr(tempParams[i]);
            tempParam = Strcat(tempParam, add);
            
            free(del);
            free(add);
        }
        else{
            params[paramPointer++] = strtoi(tempParam);
            free(tempParam);
            tempParam = chartostr('\0');
            
            if(tempParams[i] == '?')
                break;
        }
        i++;
    }
    info->params = params;
}

ConvertedExp* Infix2Postfix(char *strexp){
    Stack *opStack = InitStack();
    ExpInfo *exp = (ExpInfo*)malloc(sizeof(ExpInfo));
    ConvertedExp *result = (ConvertedExp*)malloc(sizeof(ConvertedExp));
    int strlen = Strlen(strexp);
    int convlen;
    int expPointer = 0;
    int paramsPointer = 0;
    int opPointer = 0;
    char *strexp_result = chartostr('\0');
    char *add, *del;
    char **convExp;
    
    if(strlen >= MAX_EXP_LEN)
        return NULL;
    
    exp->raw_exp = strexp;
    SetExpInfo(exp);
    
    convlen = Strlen(exp->operators) * 2 + 1;
    convExp = (char**)malloc(sizeof(char*) * convlen);
    
    for(int i = 0; i < convlen; i++){
        if(i % 2 == 0){
            convExp[expPointer++] = itostr(exp->params[paramsPointer++]);
        }
        else{
            if(opStack->numOfData == 0 || (opStack->numOfData > 0 && OpPriority(SPick(opStack)[0]) < OpPriority(exp->operators[opPointer]))){
                SPush(opStack, chartostr(exp->operators[opPointer++]));
            }
            else{
                convExp[expPointer++] = SPop(opStack);
                SPush(opStack, chartostr(exp->operators[opPointer++]));
            }
        }
    }
    
    while(opStack->numOfData){
        convExp[expPointer++] = SPop(opStack);
    }
    
    for(int i = 0; i < convlen; i++){
        add = Strcat(convExp[i], chartostr(' '));
        del = strexp_result;
        strexp_result = Strcat(strexp_result, add);
        
        free(add);
        free(del);
    }
    
    strexp_result[Strlen(strexp_result) - 1] = '\0';
    
    free(exp->params);
    free(exp->operators);
    free(exp);
    free(opStack);
    
    result->str_conv_exp = strexp_result;
    result->convExp = convExp;
    result->convLen = convlen;
    
    return result;
}

int ComputePostfixExp(ConvertedExp *exp){
    Stack *numStack = InitStack();
    int a, b;
    int result;
    
    for(int i = 0; i < exp->convLen; i++){
        if(OpPriority(exp->convExp[i][0])){
            a = strtoi(SPop(numStack));
            b = strtoi(SPop(numStack));
            
            switch(exp->convExp[i][0]){
                case '+':
                    SPush(numStack, itostr(a + b));
                    break;
                case '-':
                    SPush(numStack, itostr(a - b));
                    break;
                case '*':
                    SPush(numStack, itostr(a * b));
                    break;
                case '/':
                    SPush(numStack, itostr(a / b));
                    break;
            }
        }
        else{
            SPush(numStack, exp->convExp[i]);
        }
    }
    
    result = strtoi(SPop(numStack));
    free(numStack);
    
    return result;
}
