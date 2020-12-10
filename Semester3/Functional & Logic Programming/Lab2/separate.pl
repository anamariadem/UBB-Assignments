add_to_end([], E, [E]).
add_to_end([H | T], E, [H | Rez]) :- add_to_end(T, E, Rez).

decompose(L, Rez) :- decompose_list(L, Rez, []).

decompose_list([], Rez, Rez).
decompose_list([H | T], Rez, Col) :- 0 is H mod 2, decompose_list(T, Rez, [H | Col]).
decompose_list([H | T], Rez, Col) :- 1 is H mod 2,  add_to_end(Col, H, ColN), decompose_list(T, Rez, ColN).
