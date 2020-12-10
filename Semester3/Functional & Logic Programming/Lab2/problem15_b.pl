/*
	add_to_end(l1..ln, elem) = {
		[elem], n=0
		l1 U add_to_end(l2..ln, elem)
	}

	decompose_list(l1..ln, Nr_Even, Nr_Odd, Col) = {
		Col, Nr_Even, Nr_Odd, if l1..ln empty
		decompose_list(l2..ln,  Nr_Even + 1, Nr_Odd, l1 U Col), l1 even
		decompose_list(l2..ln,  Nr_Even, Nr_Odd + 1, Col U l1), otherwise
	}	
	decompose(l1..ln) = decompose_list(l1..ln, 0, 0, [])
*/

%add_to_end(L: list, E: int, Rez: list)
%(i,i,o)

add_to_end([], E, [E]).
add_to_end([H | T], E, [H | Rez]) :- add_to_end(T, E, Rez).   

%decompose(L: list, Rez: list, No: int, Ne: int)
%(i,o,o,o)

decompose(L, Rez, No, Ne) :- decompose_list(L, Rez, No, Ne, 0, 0, []).

decompose_list([], Rez, No, Ne, No, Ne, Rez) :- !.
decompose_list([H | T], Rez, No, Ne, ColNo, ColNe ,Col) :- 0 is H mod 2, 
							NewColNe is ColNe +1, 
							decompose_list(T, Rez, No, Ne, ColNo, NewColNe, [H | Col]).
decompose_list([H | T], Rez, No, Ne, ColNo, ColNe, Col) :- 1 is H mod 2, 
							NewColNo is ColNo +1, 
							add_to_end(Col, H, NewCol), 
							decompose_list(T, Rez, No, Ne, NewColNo, ColNe,  NewCol).

  
