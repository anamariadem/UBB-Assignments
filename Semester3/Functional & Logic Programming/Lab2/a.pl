adaug(E, [],[E]).
adaug(E, [H|T], [H|Rez]) :-adaug(E, T, Rez).



pare(L,Rez):-pare_aux(L,Rez,[]).

pare_aux([],Rez,Rez).
pare_aux([H|T],Rez,Col):- H mod 2=:=0,!, adaug(H,Col,ColN), pare_aux(T,Rez,ColN).
pare_aux([_|T],Rez,Col):-pare_aux(T,Rez,Col).
