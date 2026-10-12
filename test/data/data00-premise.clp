(defrule rule1 
	=>
	(println "rule1 rung qwertz")
	(println "test "(gen-literal "Hello World!"))
	(println "test "(gen-literal "Hello World!" "http://example.com/customdatatype"))
	(println "test "(gen-string-lang "Hello World!"))
	(println "test "(gen-string-lang "Hello World!" "en"))

	(println "test "(gen-literal "1" "http://www.w3.org/2001/XMLSchema#decimal"))
	(println "test "(gen-literal "1" "http://www.w3.org/2001/XMLSchema#integer"))
	(println "test "(gen-literal "1" "http://www.w3.org/2001/XMLSchema#boolean"))
)

(defrule rule0
	(test (eq "Hello%20World%21" (gen-literal "Hello World!")))
	(test (eq (gen-literal "Hello World!") (gen-literal "Hello World!" "http://www.w3.org/2001/XMLSchema#string")))
	(test (eq "Hello%20World%21^^http://example.com/customdatatype" (gen-literal "Hello World!" "http://example.com/customdatatype")))
	(test (eq "Hello%20World%21@@" (gen-string-lang "Hello World!")))
	(test (eq "Hello%20World%21@@en" (gen-string-lang "Hello World!" "en")))
	(test (eq 1 (gen-literal "1" "http://www.w3.org/2001/XMLSchema#decimal")))
	(test (eq 1 (gen-literal "1" "http://www.w3.org/2001/XMLSchema#integer")))

	(test (eq TRUE (gen-literal "1" "http://www.w3.org/2001/XMLSchema#boolean")))
	(test (eq FALSE (gen-literal "0" "http://www.w3.org/2001/XMLSchema#boolean")))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
