#|
3.
a) Write a function that inserts in a linear list a given atom A after the 
2nd, 4th, 6th, ... element.
b) Write a function to get from a given list the list of all atoms, on any
 level, but reverse order. Example:
 (((A B) C) (D E)) ==> (E D C B A)
c) Write a function that returns the greatest common divisor of all numbers 
in a nonlinear list.
d) Write a function that determines the number of occurrences of a given atom in 
a nonlinear list.
|#

#|
	insertAfterAux(e, l1..ln, pos) = {
		[], n=0
		l1 U e U insertAfterAux(e, l2..ln, pos+1), pos > 0 pos even
		l1 U insertAfterAux(e, l2..ln, pos+1), otherwise
	}

	insertAfter(e, l1..ln) = insertAfterAux(e, l1..ln, 1)

	getAtomsAux(l1..ln, col) ={
		col, n=0
		getAtomsAux(l2..ln, l1 U col), if l1 atom
		getAtomsAux(l2..ln, getAtomsAux(l1) U col), if l1 list
	}

	getAtoms(l1..ln) = getAtomsAux(l1..ln, [])

	greatestCommonDivisor(a, b) = {
		a, b=0
		greatestCommonDivisor(b, a%b), otherwise
	}

	gcdList(l1..ln) = {
		l1, n=1
		greatestCommonDivisor(l1, l2), n=2
		gcdList(greatestCommonDivisor(l1, l2) U l3..ln), otherwise
	}

	gcdNonLinearList(l1..ln) = gcdList(getAtoms(l1..ln))

	nrOfOccurences(l1..ln, e) = {
		0, n=0
		nrOfOccurences(l2..ln, e) + 1, l1 atom and l1 = e
		nrOfOccurences(l1, e) + nrOfOccurences(l2..ln, e), l1 list
		nrOfOccurences(l2..ln, e), l1 atom
	}
	
|#

;a
(defun insertAfterAux(element givenList cPosition)
	(cond 
		((null givenList) (car nil))

		((and (> cPosition 0) (= (mod cPosition 2) 0)) 
			(cons (car givenList) (cons element (insertAfterAux element (cdr givenList) (+ cPosition 1)))))

		(t(cons (car givenList) (insertAfterAux element (cdr givenList) (+ cPosition 1))))

	)
)

(defun insertAfter(element givenList)
	(insertAfterAux element givenList '1 )
)

;(load "problem3.lisp")
;(insertAfterAux '7 '(1 2 3 4 5) '0)

;b

(defun getAtomsAux(givenList col)
	(cond
		((null givenList) col)

		((atom (car givenList)) 
			(getAtomsAux (cdr givenList) (cons (car givenList) col)))

		((listp (car givenList)) 
			(getAtomsAux (cdr givenList) (append (getAtomsAux (car givenList) '()) col)))
	)
)

(defun getAtoms(givenList)
	(getAtomsAux givenList '())
)

;c
(defun greatestCommonDivisor(a b)
	(cond
		((= b 0) a)

		(t(greatestCommonDivisor b (mod a b))) 

	)
)

(defun gcdList(givenList)
	(cond
		((null (cdr givenList)) (car givenList))

		((null (cdr(cdr givenList))) (greatestCommonDivisor (car givenList) (car (cdr givenList))))

		(t(gcdList (cons (greatestCommonDivisor (car givenList) (car (cdr givenList))) 
					(cdr (cdr givenList)) )))

	)

)

(defun gcdNonLinearList(givenList)
	(gcdList (getAtoms givenList))
)

#|(defun gcdNonLinearList(givenList)
	(cond
		((null (cdr givenList)) (car givenList))

		((and (null (cdr(cdr givenList))) (atom (car givenList)) (atom (car(cdr givenList))))
			(greatestCommonDivisor (car givenList) (car(cdr givenList))))

		( (and (atom (car givenList)) (atom (car(cdr givenList))))
			(gcdNonLinearList (cons (greatestCommonDivisor (car givenList) (car(cdr givenList))) 
								(cdr (cdr givenList)) ) )) 
		((listp (car givenList)) 
			(gcdNonLinearList (cons (gcdNonLinearList (car givenList)) (cdr givenList)) ))
	)

)|#


;d
(defun nrOfOccurences(givenList element)
	(cond
		((null givenList) 0)

		((and (atom (car givenList)) (equal element (car givenList))) 
			(+ 1 (nrOfOccurences (cdr givenList) element)))

		((atom (car givenList)) (nrOfOccurences (cdr givenList) element))

		((listp (car givenList)) 
			(+ (nrOfOccurences (car givenList) element) 
				(nrOfOccurences (cdr givenList) element)))
	)

)



























