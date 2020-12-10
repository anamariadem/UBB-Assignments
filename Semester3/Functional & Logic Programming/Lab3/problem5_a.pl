/*
5.
a. Substitute all occurrences of an element of a list with all the elements of another list.
Eg. subst([1,2,1,3,1,4],1,[10,11],X) produces X=[10,11,2,10,11,3,10,11,4].
b. For a heterogeneous list, formed from integer numbers and list of numbers, replace in every sublist all
occurrences of the first element from sublist it a new given list.
Eg.: [1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] =>
[1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]
*/

/*
	concat(l1...ln, t1..tm) = {
		t1...tm, if n=0
		l1 U append(l2..ln, t1..tm)
	}
*/
%concat(L1: List, L2: List, Rez: List) 
%(i,i,o)

concat([], X, X) :- !.
concat([H | T], X,[H | Rez]) :-
    			concat(T, X, Rez).

/*
	substitute(l1..ln, e, t1..tm) = {
		[], n = 0
		t1..tm U substitute(l2..ln, e, t1..tm), l1 = e
		l1 U substitute(l2..ln, e, t1..tm), l1 != e
	}
*/
%substitute(L1: list, E: int, L2: list, Rez: list)
%(i,i,i,o)

substitute([], _, _, []) :- !.
substitute([E | T], E, List, Rez) :-!, substitute(T, E, List, Rez1), append(List, Rez1, Rez). 
substitute([H | T], E, List,[H | Rez] ) :- substitute(T, E, List, Rez). 

