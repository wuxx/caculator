# caculator

caculator written in C, for myself to learn the decline recursive analysis
inspired by Ruslan Spivak

https://ruslanspivak.com/lsbasi-part1/

http://blog.jobbole.com/88152/


expr : term( (PLUS|MINUS) term)*

term : factor( (MUL|DIV) factor)*

factor : INTEGER | LPAREN expr RPAREN
