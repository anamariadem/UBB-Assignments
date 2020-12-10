/*
b. For a heterogeneous list, formed from integer numbers and list of numbers, replace in every sublist all
occurrences of the first element from sublist it a new given list.
Eg.: [1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] =>
[1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]
*/

substitute([], _, _, []) :- !.
substitute([E | T], E, List, Rez) :- substitute(T, E, List, Rez1), append(List, Rez1, Rez).
substitute([H | T], E, List,[H | Rez] ) :- H =\= E, substitute(T, E, List, Rez).

/*
	replace(l1..ln, t1..tm) = {
		[], n = 0
		l1 U replace(l2..ln, t1..tm), l1 is number
		substitute(l1, e, t1..tm) U replace(l2..ln,t1..tm) ,l1 is list and e is the first
									elem of l1
	}	
*/
%replace(L1: heterogeneous list, L2: list, Rez: list)
%(i,i,o)

replace([], _, []) :- !.
replace([H | T], List,[H | Rez]) :- number(H),!, replace(T, List, Rez).
replace([ [Hi | Ti] | T], List, [Rez2 |Rez]) :- is_list([Hi | Ti]),
					!, 
					replace(T, List, Rez),
					substitute([Hi | Ti], Hi, List, Rez2).
