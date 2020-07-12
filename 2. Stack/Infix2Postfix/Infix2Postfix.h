/*
 This Header Require 'Stack.h' with 'Stack.c'
 */
#ifndef __INFIX2POSTFIX_H__
#define __INFIX2POSTFIX_H__

#include"Stack.h"
#define MAX_EXP_LEN 10000

typedef struct _ExpInfo{
    int *params;
    char *raw_exp;
    char *operators;
} ExpInfo;

typedef struct _ConvertedExp{
    char *str_conv_exp;
    char **convExp;
    int convLen;
} ConvertedExp;

int Power(int, int);
int Strlen(char*);
char* Strcat(char*, char*);
int Find(char, char*);
char* StrFliper(char*);
int Search(char*, char*);
int IsDigit(char);
int ctoi(char);
char itoc(int);
int strtoi(char*);
char* itostr(int);
char* chartostr(char);
int OpPriority(char);
void SetExpInfo(ExpInfo*);
ConvertedExp* Infix2Postfix(char*);
int ComputePostfixExp(ConvertedExp*);

#endif
