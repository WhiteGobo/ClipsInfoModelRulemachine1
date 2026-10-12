(defrule rule1 
	=>
	(println "rule1 rung qwertz")
	(println "test "
		(gen-literal "Hello World!")"
"
		(<http://www.w3.org/2007/rif-builtin-function#string-from-PlainLiteral> (gen-string-lang "Hello World!" "en"))"
"
		(gen-literal "en" "http://www.w3.org/2001/XMLSchema#lang")"
"
		(<http://www.w3.org/2007/rif-builtin-function#lang-from-PlainLiteral> (gen-string-lang "Hello World!" "en"))"
"
		(gen-literal "" "http://www.w3.org/2001/XMLSchema#string")"
"
		(<http://www.w3.org/2007/rif-builtin-function#lang-from-PlainLiteral> (gen-literal "Hello World!"))"
"
	)
)

(defrule rule0
	(test (eq (gen-string-lang "Hello World!" "en") (<http://www.w3.org/2007/rif-builtin-function#PlainLiteral-from-string-lang> (gen-literal "Hello World!") "en")))
	(test (eq (gen-literal "Hello World!") (<http://www.w3.org/2007/rif-builtin-function#string-from-PlainLiteral> (gen-string-lang "Hello World!" "en"))))
	(test (eq
		(gen-literal "en" "http://www.w3.org/2001/XMLSchema#lang")
		(<http://www.w3.org/2007/rif-builtin-function#lang-from-PlainLiteral> (gen-string-lang "Hello World!" "en"))
	))
	(test (eq (gen-literal "" "http://www.w3.org/2001/XMLSchema#string") (<http://www.w3.org/2007/rif-builtin-function#lang-from-PlainLiteral> (gen-literal "Hello World!"))))
	(test (eq -1 (<http://www.w3.org/2007/rif-builtin-function#PlainLiteral-compare> (gen-string-lang "hallo" "de") (gen-string-lang "welt" "de"))))
	(test (eq 1 (<http://www.w3.org/2007/rif-builtin-function#PlainLiteral-compare> (gen-string-lang "welt" "de") (gen-string-lang "hallo" "de"))))
	(test (eq 0 (<http://www.w3.org/2007/rif-builtin-function#PlainLiteral-compare> (gen-string-lang "hallo" "de") (gen-string-lang "hallo" "de"))))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#matches-language-range> (gen-string-lang "Schlagobers ist dasselbe wie Schlagsahne." "de-at") (gen-literal "de-*")))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
