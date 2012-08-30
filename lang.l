%{
#include <string.h>
#include <stdlib.h>


%}

%%

[0-9]+ { yylval.num = atoi(yytext); return NUMBER; }
"show" return SHOW;
"do" return DO;
"times" return TIMES;
"stop" return STOP;
"if" return IF;
"loop" return LOOP;
"fun" return FUN;
"return" return RET;
"==" return EQ;
">=" return GTEQ;
"<=" return LTEQ;
"!=" return NEQ;
"::int" { yylval.num = (0); return NUMBER; }
"::bool" { yylval.num = (1); return NUMBER; }
"::char" { yylval.num = (2); return NUMBER; }
"true" { yylval.num = (1); return NUMBER; }
"false" { yylval.num = (0); return NUMBER; }

[a-zA-Z][a-zA-z0-9]* { yylval.name = malloc(strlen(yytext)); strcpy(yylval.name, yytext); return IDENTIFIER; }

[ \t\n] /* ignore blanks and tabs */ ;

\n|. return yytext[0];

%%

