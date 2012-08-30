%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//int yydebug=1;
    
typedef struct cmd cmd;
typedef struct cmdList cmdList;
typedef struct symtab symtab;
typedef struct funtab funtab;
typedef struct exprn exprn;
typedef struct arglist arglist;
typedef enum boolean boolean;

struct arglist {
    char *name;
    arglist *next;
};

enum boolean {false, true};

struct symtab {
    char *name;
    int ival;
    boolean bval;
    char cval;
    int type;
    symtab *next;
};


struct funtab {
    char *name;
    arglist *args;
    cmdList *body;
    funtab *next;
};

struct exprn {
    char type;  //+-*/><, = - ==, G - >=, L - <=, N - !=, ! - not, n - number, v - variable, f - function, t - type
    int val;    //if it's a number
    char *var;  //if it's a variable
    exprn *left;
    exprn *right;
    arglist *args;
};


struct cmd {
    char type; //a - assignment, d - do, i - if, s - show, z - stop, l - loop, e - bare expression, r - return
    char *var;
    exprn *exp;
    cmdList *cmnd;
};

struct cmdList {
    cmd *curr;
    cmdList *rest;
};

arglist * makeArgList(char *arg, arglist *n) {
    arglist *ret = malloc(sizeof(arglist));
    ret->name = arg;
    ret->next = n;
    return ret;
}

cmdList * makeCmdList(cmd *c, cmdList *r) {
    cmdList *ret = malloc(sizeof(cmdList));
    ret->curr = c;
    ret->rest = r;
    return ret;
}

cmd * makeCmd(char t, char *v, exprn *e, cmdList *c) {
    cmd *ret = malloc(sizeof(cmd));
    ret->type = t;
    ret->var = v;
    ret->exp = e;
    ret->cmnd = c;
    return ret;
}

exprn * makeExprn(char t, int v, char* name, exprn *l, exprn *r) {
    exprn *ret = malloc(sizeof(exprn));
    ret->type = t;
    ret->val = v;
    ret->var = name;
    ret->left = l;
    ret->right = r;
    return ret;
}

exprn * makeFunctionExprn(char *name, arglist *args) {
    exprn *ret = malloc(sizeof(exprn));
    ret->type = 'f';
    ret->var = name;
    ret->args = args;
    return ret;
}

cmdList * getFunBody(char *name, funtab *t) {
    if(strcmp(name, t->name) == 0)
        return t->body;
    else if(t->next != NULL)
        return getFunBody(name, t->next);
    printf("Error, function %s not defined before use\n", name);
    return NULL;
}

arglist * getFunArgs(char *name, funtab *t) {
    if(strcmp(name, t->name) == 0)
        return t->args;
    else if(t->next != NULL)
        return getFunArgs(name, t->next);
    printf("Error, function %s does not have suitable args\n", name);
    return NULL;
}

void setFun(char *name, arglist *args, cmdList *body,funtab *t) {
    if(strcmp(name, t->name) == 0) {
        t->body = body;
        t->args = args;
    }
    else if(t->next != NULL)
        setFun(name, args, body, t->next);
    else {
        t->next = malloc(sizeof(funtab));
        t->next->name = malloc(strlen(name));
        strcpy(t->next->name, name);
        t->next->args = args;
        t->next->body = body;
        t->next->next = NULL;
    }
}

funtab functions = {"main", NULL, NULL};
%}

%union {
	cmdList *cList;
	int  num;
    exprn *exp;
    cmd *c;
    char *name;
    arglist *arg;
}

%token <num> NUMBER
%token <name> IDENTIFIER

%token SHOW DO TIMES STOP END IF GTEQ LTEQ EQ NEQ LOOP FUN RET

%type <cList> commlist
%type <cList> block
%type <c> comm
%type <exp> expr
%type <arg> args

%left '+' '-'
%left '*' '/'
%left '>' '<' EQ GTEQ LTEQ NEQ
%nonassoc '!'

%%

prog: funlist
    | error { yyerrok; printf("Error!\n"); }
    ;

funlist: FUN IDENTIFIER '(' args ')' block funlist { setFun($2, $4, $6, &functions); }
       | /* empty */
       ;

commlist: comm commlist { $$ = makeCmdList($1, $2); }
        | /* empty */ { $$ = NULL; }
        ;

block: comm { $$ = makeCmdList($1, NULL); }
     | '{' commlist '}' { $$ = $2; }
     ;

comm: IDENTIFIER '=' expr ';'{ $$ = makeCmd('a', $1, $3, NULL); }
    | DO expr TIMES block { $$ = makeCmd('d', NULL, $2, $4); }
    | IF '(' expr ')' block { $$ = makeCmd('i', NULL, $3, $5); }
    | SHOW expr ';' { $$ = makeCmd('s', NULL, $2, NULL); }
    | STOP ';' { $$ = makeCmd('z', NULL, NULL, NULL); }
    | LOOP block { $$ = makeCmd('l', NULL, NULL, $2); }
    | expr ';' { $$ = makeCmd('e', NULL, $1, NULL); }
    | RET expr ';' { $$ = makeCmd('r', NULL, $2, NULL); }
    ;

expr: '(' expr ')' { $$ = $2; }
    | expr '+' expr { $$ = makeExprn('+', 0, NULL, $1, $3); }
    | expr '-' expr { $$ = makeExprn('-', 0, NULL, $1, $3); }
    | '-' expr { $$ = makeExprn('-', 0, NULL, makeExprn('n', 0, NULL, NULL, NULL), $2); }
    | expr '*' expr { $$ = makeExprn('*', 0, NULL, $1, $3); }
    | expr '/' expr { $$ = makeExprn('/', 0, NULL, $1, $3); }
    | expr '>' expr { $$ = makeExprn('>', 0, NULL, $1, $3); }
    | expr '<' expr { $$ = makeExprn('<', 0, NULL, $1, $3); }
    | expr EQ expr { $$ = makeExprn('=', 0, NULL, $1, $3); }
    | expr GTEQ expr { $$ = makeExprn('G', 0, NULL, $1, $3); }
    | expr LTEQ expr { $$ = makeExprn('L', 0, NULL, $1, $3); }
    | expr NEQ expr { $$ = makeExprn('N', 0, NULL, $1, $3); }
    | '!' expr { $$ = makeExprn('!', 0, NULL, $2, NULL); }
    | IDENTIFIER '(' args ')' { $$ = makeFunctionExprn($1, $3); }
    | NUMBER { $$ = makeExprn('n', $1, NULL, NULL, NULL); }
    | IDENTIFIER { $$ = makeExprn('v', 0, $1, NULL, NULL); }
    | IDENTIFIER ':' ':' { $$ = makeExprn('t', 0, $1, NULL, NULL); }
    ;

args: IDENTIFIER ',' args    { $$ = makeArgList($1, $3); }
    | IDENTIFIER  { $$ = makeArgList($1, NULL); }
    ;
//should really make it so functions are called with expression lists... oh well

%%

#include "lex.yy.c"

yyerror(s)
char *s;
{printf("%s\n", s);
}

void setVal(int val, symtab *t, int type) {
    if(type==0) {
            t->ival = val;
    } else if(type==1) {
        if(val%1) {
            t->bval = true;
        } else {
            t->bval = false;
        }
    } else {
        t->cval = (char)val;
    }
}

symtab *findVar(char *name, symtab *t) {
    if(t == NULL) return NULL;
    if(strcmp(name, t->name) == 0) {
        return t;
    }
    else if(t->next != NULL)
        return findVar(name, t->next);
    else return NULL;
}

int getType(char* name, symtab *t) {
    if(strcmp(name, t->name) == 0) {
        return t->type;
    } else if(t->next != NULL)
        return getType(name, t->next);
    else {
        return rand()%3;
    }
}

int getVar(char *name, symtab *t) {
    if(strcmp(name, t->name) == 0) {
        int oldtype = t->type;
        t->type = rand()%3;
        if(oldtype == 0) return t->ival;
        else if(oldtype == 1) return t->bval;
        else return t->cval;
    } else if(t->next != NULL)
        return getVar(name, t->next);
    else {
        t->next = malloc(sizeof(symtab));
        t->next->name = malloc(strlen(name));
        strcpy(t->next->name, name);
        t->type = rand()%3;
        setVal(0, t, t->type);
        t->type = rand()%3;
        t->next->next = NULL;
        printf("Auto-initializing %s\n", name);
        return 0;
    }
}

void setVar(char *name, int val, symtab *t) {
    if(strcmp(name, t->name) == 0) {
        setVal(val, t, t->type);
        t->type = rand()%3;
    }
    else if(t->next != NULL)
        setVar(name, val, t->next);
    else {
        t->next = malloc(sizeof(symtab));
        t->next->name = malloc(strlen(name));
        t->type = rand()%3;
        strcpy(t->next->name, name);
        setVal(val, t, t->type);
	t->type = rand()%3;
        t->next->next = NULL;
    }
}

void copyVars(arglist *oldargs, symtab *old, arglist *newargs, symtab *new) {
    while(oldargs != NULL && newargs != NULL) {
        setVar(newargs->name, getVar(oldargs->name, old), new);
        symtab *nvar = findVar(newargs->name, new), *ovar = findVar(oldargs->name, old);
        if(nvar != NULL && ovar != NULL) {
            nvar->ival = ovar->ival;
            nvar->bval = ovar->bval;
            nvar->cval = ovar->cval;
        }
        oldargs = oldargs->next;
        newargs = newargs->next;
    }
    if(oldargs!= NULL || newargs !=NULL)
        printf("Error! Not enough arguments!\n");
}
    
int applyFun(char *name, arglist *args, symtab *table) {
    symtab newtab = {"zero", 0, 0, 0, 0, NULL};
    copyVars(args, table, getFunArgs(name, &functions), &newtab);
    int ret = executeList(getFunBody(name, &functions), &newtab);
    return ret;
}
    

int evalExpr(exprn *e, symtab *table) {
    if(e==NULL) return 0;
    switch (e->type) {
        case '+' : return evalExpr(e->left, table)+evalExpr(e->right, table);
        case '-' : return evalExpr(e->left, table)-evalExpr(e->right, table);
        case '*' : return evalExpr(e->left, table)*evalExpr(e->right, table);
        case '/' : return evalExpr(e->left, table)/evalExpr(e->right, table);
        case '>' : return evalExpr(e->left, table)>evalExpr(e->right, table);
        case '<' : return evalExpr(e->left, table)<evalExpr(e->right, table);
        case '=' : return evalExpr(e->left, table)==evalExpr(e->right, table);
        case 'G' : return evalExpr(e->left, table)>=evalExpr(e->right, table);
        case 'L' : return evalExpr(e->left, table)<=evalExpr(e->right, table);
        case 'N' : return evalExpr(e->left, table)!=evalExpr(e->right, table);
        case '!' : return !(evalExpr(e->left, table));
        case 'f' : return applyFun(e->var, e->args, table);
        case 'n' : return e->val;
        case 'v' : return getVar(e->var, table);
        case 't' : return getType(e->var, table);
        default : return 0;
    }
}

int breakFlag = 0;
int retFlag = 0;
int retval = 0;
int executeList(cmdList *tree, symtab *table) {    //return value says if we had 'stop'

    if(tree==NULL) return 0;
    while(tree->curr != NULL) {
        cmd *curr = tree->curr;
        switch(curr->type){
            case 'a':
                setVar(curr->var, evalExpr(tree->curr->exp, table), table); break;
            case 'd': { //for the variable
                int count = evalExpr(curr->exp, table);
                while(count-->0 && breakFlag==0 && retFlag==0) { executeList(curr->cmnd, table);}
                } breakFlag = 0; if(retFlag!=0) {return retval; }break;
            case 'l': while(breakFlag==0) {executeList(curr->cmnd, table);} breakFlag = 0; if(retFlag!=0) {
retFlag=0; return retval; } break;
            case 's':
                printf("%d\n", evalExpr(curr->exp, table)); break;
            case 'z': breakFlag = 1; return 0; break;
            case 'i': if(evalExpr(curr->exp, table)) { int ret = executeList(curr->cmnd, table); if(retFlag!=0) { breakFlag =0; retFlag = 0; return ret; } if(breakFlag!=0) { return 0; } }break;
            case 'e': evalExpr(curr->exp, table); break;
            case 'r': {breakFlag = 1; retFlag = 1; retval = evalExpr(curr->exp, table); return retval;} break;
            default :
                printf("Unsupported Op: %c\n", curr->type);
        }
    

        if(tree == NULL || tree->rest == NULL) break;
        tree = tree->rest;
    }
    return retval;  
}
    
main()
{ srand(time(NULL));
  yyparse();
  symtab table = {"zero", 0, 0, 0, 0, NULL};
  executeList(functions.body, &table);
}
