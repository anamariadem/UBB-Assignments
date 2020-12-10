/*
insertAtPosition(l1..ln, e, poz):
	- [e], if list is empty
	- e U l1..ln ,  poz == 1
	- l1 U insertAtPosition(l2..ln, e, poz-1), otherwise
*/

%insertAtPosition(List: list, E: int, Poz: int, Rez: list)
%(i,i,i,o)


insertAtPosition([], E, _, [E]) :- !.
insertAtPosition(List, E, 1, [E | List]) :- !.
insertAtPosition([H | T], E, Poz, [H | Rez]) :- NewPoz is Poz -1,  insertAtPosition(T, E, NewPoz, Rez).

/*
GCD(e1, e2):
	-a, if b == 0
	-GCD(b, a%b), otherwise


GCDL(l1..ln):
	- 0, if list is empty
	- l1, if the length of the list is 1
	- GCDL(GCD(l1, l2) U  l3..ln)), otherwise
*/

%gcd(A: int, B:int, Rez: int)
%(i,i,o)

gcd(A, 0, A) :- !.
gcd(A, B, Rez) :- R is A mod B , gcd(B,R, Rez). 

%gcdList(List: list, Rez: int)
%(i,o)


gcdList([], 0) :- !.
gcdList([H], H) :- !.
gcdList([H1 |[H2 | T]], Rez) :- gcd(H1, H2, GcdH1H2),  gcdList([GcdH1H2 | T], Rez). 

