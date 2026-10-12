(defrule print-matches-for-rule0 =>
	(println "testing: 
(<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> 1 \"1\"): "
		(<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> 1 "1") "
(<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> 1 2): "
		(<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> 1 2)"
(<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> \"Hello world@^^http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral\" \"Hello world@^^http://www.w3.org/2001/XMLSchema#string\"): "
		(<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> "Hello world@^^http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral" "Hello world@^^http://www.w3.org/2001/XMLSchema#string")
	)
	(println "print matches:") (matches rule0)
)

(defrule rule0
	(test (<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> 1 "1"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical> 1 2))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#literal-not-identical>
		"Hello world@^^http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral"
		"Hello world@^^http://www.w3.org/2001/XMLSchema#string"
	))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
