%{

%}

delim   [ \t\n]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
id      {letter}({letter}|{digit})*
number  {digit}+(\.{digit}+)?(e[+-]?{digit}+)?
%%

[ ] {}

{number} { sscanf(yytext, "%lf", &yylval); return NUMBER; }

\n|.    {return yytext[0];}

%%