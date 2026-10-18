(defrule rule1 
	=>
	(println "test rule1 
not"		(<http://www.w3.org/2007/rif-builtin-function#not> FALSE)"
equal"		(<http://www.w3.org/2007/rif-builtin-predicate#boolean-equal> FALSE FALSE)"
less-than"		(<http://www.w3.org/2007/rif-builtin-predicate#boolean-less-than> FALSE TRUE)"
greater-than"		(<http://www.w3.org/2007/rif-builtin-predicate#boolean-greater-than> TRUE FALSE)
	)
)

(defrule rule0
	(test (eq TRUE (<http://www.w3.org/2007/rif-builtin-function#not> FALSE) ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#boolean-equal> FALSE FALSE))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#boolean-less-than> FALSE TRUE))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#boolean-greater-than> TRUE FALSE))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-boolean> TRUE ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-boolean> "foo" ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-boolean> (<http://www.w3.org/2001/XMLSchema#boolean> "1" ) ) )
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
