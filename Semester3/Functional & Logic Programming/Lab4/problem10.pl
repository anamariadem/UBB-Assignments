/*
10. For a list a1... an with integer and distinct numbers, define a predicate to determine all subsets with sum of elements divisible with n.
*/

/*
	sumElem(l1..ln) = {
		0, n = 0
		l1 + sumElem(l2..ln), otherwise
	}
	
	subset(l1..ln) = {
		1. [], n=0
		2. l1 U subset(l2..ln)
		3. subset(l2..ln)
	
	checkSum(l1..ln, n) = {
		[], n=0
		l1 U checkSum(l2..ln, n), if sum(l1) mod n = 0
		checkSum(l2..ln, n)
	} 
	
	checkSubsetsSum(l1..ln, n) = {
		checkSum(U subsets(l1..ln))
	} 
	
*/

%sumElem(L: list, S: int)
%(i,o) - deterministic

sumElem([], 0) :- !.
sumElem([H | T], S) :- sumElem(T, N), S is H + N.

%subset(L: list, Rez: list)
%(i,o) - non-deterministic
subset([], []).
subset([E|T], [E|Tail]) :- subset(T, Tail).
subset([_|T], Tail) :- subset(T, Tail).

%checkSum(L: list, Rez: list, N: int)
%(i,o,i)
checkSum([], [], _).
checkSum([H | T], [H | Rez], N) :- sumElem(H, Sum), 
				R is mod(Sum, N),
				R =:= 0, 
				!, 
				checkSum(T, Rez, N).
checkSum([_ | T], Rez, N) :- checkSum(T, Rez, N).


checkSubsetsSum(List, Rez, N) :- findall(Subset, subset(List, Subset), Subsets),
				checkSum(Subsets, Rez, N).

 
