%{
    #include <ctype.h>
    #include <stdio.h>
    #include <stdlib.h>
    #define YYSTYPE double
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

lines : lines expr '\n' { printf("%g\n", $2); }
    | lines '\n'
    |
    ;

expr : expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = - $2; }
    | NUMBER
    ;

%%

yylex()
{
    int c = getchar();
    while(c == ' ')
    {
        c = getchar();
    } 

    if (isdigit(c) || c == '.')
    {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }

    return c;
}