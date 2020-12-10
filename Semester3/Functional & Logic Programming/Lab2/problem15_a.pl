/*
	member(elem, l1..ln) = {
		False, list is empty
		True, l1 = elem
		member(l2..ln), otherwise
	}

	list_to_set(list) = list_to_set_aux(list, [])
	list_to_set_aux(list, aux_list) = {
		list, if list = []
		l1 U list_to_set_aux(l2..ln, l1 U aux_list), l1 not in  aux_list
		list_to_set_aux(l2..ln, aux_list), otherwise 
	}
*/
%member (E: int, List : list)
%(i,i)

member(E,[E|_]) :- !.
member(E,[_|L]) :- member(E,L).

%list_to_set(L : List, Rez : List)
%(i,o) 
list_to_set(L, Rez) :- list_to_set_aux(L, [], Rez).

list_to_set_aux([], List, []) :- !.
list_to_set_aux([H | T], List, [H |Rez]) :- \+ member(H, List), ! , list_to_set_aux(T, [H | List], Rez).
list_to_set_aux([H | T], List, Rez) :- member(H, List) , list_to_set_aux(T, List, Rez).
 
