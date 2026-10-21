(defrule rule0
	(test (eq 2 (<http://www.w3.org/2007/rif-builtin-function#numeric-add> 1 1 )))
	(test (eq 1 (<http://www.w3.org/2007/rif-builtin-function#numeric-subtract> 2 1 )))
	(test (eq 6 (<http://www.w3.org/2007/rif-builtin-function#numeric-multiply> 2 3 )))
	(test (eq 2 (<http://www.w3.org/2007/rif-builtin-function#numeric-divide> 6 3 )))
	(test (eq 1 (<http://www.w3.org/2007/rif-builtin-function#numeric-integer-divide> 5 3 )))
	(test (eq 2 (<http://www.w3.org/2007/rif-builtin-function#numeric-integer-mod> 5 3 )))
	(test (eq 2 (<http://www.w3.org/2007/rif-builtin-function#numeric-mod> 5 3 )))

	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-equal> .0
		 (<http://www.w3.org/2007/rif-builtin-function#numeric-subtract> 1 1)))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> 0 1 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-less-than> 1 2 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-less-than-or-equal> 1 2 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-less-than-or-equal> 1 1 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> 2 -1 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than-or-equal> 2 -1 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than-or-equal> 2 2 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> 0 1 ))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
