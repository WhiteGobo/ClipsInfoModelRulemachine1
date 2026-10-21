(defrule rule1 
	=>
	(println "rule1 rung qwertz")
	(println "test ""
	"(<http://www.w3.org/2007/rif-builtin-function#concat> "foo" "bar")"
	"(<http://www.w3.org/2007/rif-builtin-function#string-join> "foo" "bar" ",")"
	substring "(<http://www.w3.org/2007/rif-builtin-function#substring> "foobar" 3)"
	substring "(<http://www.w3.org/2007/rif-builtin-function#substring> "foobar" 0 3)"
	length "(<http://www.w3.org/2007/rif-builtin-function#string-length> "foo")"
	upper "(<http://www.w3.org/2007/rif-builtin-function#upper-case> "FooBar")"
	lower "(<http://www.w3.org/2007/rif-builtin-function#lower-case> "FooBar")"
	"(gen-literal "RIF%20Basic%20Logic%20Dialect")"
	encode for uri "(<http://www.w3.org/2007/rif-builtin-function#encode-for-uri> "RIF Basic Logic Dialect")"
	iri2uri exp "(gen-literal "http://www.example.com/~b%C3%A9b%C3%A9")"
	iri2uri     "(<http://www.w3.org/2007/rif-builtin-function#iri-to-uri> "http://www.example.com/~bébé")"
	substring before "(<http://www.w3.org/2007/rif-builtin-function#substring-before> "foobar" "bar")"
	substring after "(<http://www.w3.org/2007/rif-builtin-function#substring-after> "foobar" "foo")"
	"(gen-literal "javascript:if (navigator.browserLanguage == 'fr') window.open('http://www.example.com/~b%C3%A9b%C3%A9');")"
	escape for html 
	"(<http://www.w3.org/2007/rif-builtin-function#escape-html-uri> (gen-literal "javascript:if (navigator.browserLanguage == 'fr') window.open('http://www.example.com/~bébé');" ))"
	substring before "(<http://www.w3.org/2007/rif-builtin-function#substring-before> "foobar" "bar")"
	escape4html  in "(gen-literal "javascript:if (navigator.browserLanguage == 'fr') window.open('http://www.example.com/~b%C3%A9b%C3%A9');")"
	escape4html out "(<http://www.w3.org/2007/rif-builtin-function#escape-html-uri> (gen-literal "javascript:if (navigator.browserLanguage == 'fr') window.open('http://www.example.com/~bébé');" ))"
	replace     "(<http://www.w3.org/2007/rif-builtin-function#replace> "abcd" (gen-literal "(ab)|(a)") (gen-literal "[1=$1][2=$2]"))"
"
	)
)



(defrule rule0
	(test (eq -1 (<http://www.w3.org/2007/rif-builtin-function#compare> "bar" "foo")))
	(test (eq 1 (<http://www.w3.org/2007/rif-builtin-function#compare> "foo" "bar")))
	(test (eq 0 (<http://www.w3.org/2007/rif-builtin-function#compare> "bar" "bar")))
	(test (eq (gen-literal "foobar") (<http://www.w3.org/2007/rif-builtin-function#concat> "foo" "bar")))
	(test (eq (gen-literal "foobarfoo") (<http://www.w3.org/2007/rif-builtin-function#concat> "foo" "bar" "foo")))
	(test (eq (gen-literal "foo,bar") (<http://www.w3.org/2007/rif-builtin-function#string-join> "foo" "bar" ",")))
	(test (eq (gen-literal "bar") (<http://www.w3.org/2007/rif-builtin-function#substring> "foobar" 3)))
	(test (eq (gen-literal "fo") (<http://www.w3.org/2007/rif-builtin-function#substring> "foobar" 0 3)))
	(test (eq 3 (<http://www.w3.org/2007/rif-builtin-function#string-length> "foo")))
	(test (eq "FOOBAR" (<http://www.w3.org/2007/rif-builtin-function#upper-case> "FooBar")))
	(test (eq "foobar" (<http://www.w3.org/2007/rif-builtin-function#lower-case> "FooBar")))
	(test (eq
		(gen-literal "RIF%20Basic%20Logic%20Dialect")
		(<http://www.w3.org/2007/rif-builtin-function#encode-for-uri> "RIF Basic Logic Dialect")
	))
	(test (eq
		(gen-literal "http://www.example.com/~b%C3%A9b%C3%A9")
		(<http://www.w3.org/2007/rif-builtin-function#iri-to-uri> "http://www.example.com/~bébé")
	))
     	(test (eq
		(gen-literal "javascript:if (navigator.browserLanguage == 'fr') window.open('http://www.example.com/~b%C3%A9b%C3%A9');")
		(<http://www.w3.org/2007/rif-builtin-function#escape-html-uri> (gen-literal "javascript:if (navigator.browserLanguage == 'fr') window.open('http://www.example.com/~bébé');" ))
	))
     	(test (eq "foo"
		(<http://www.w3.org/2007/rif-builtin-function#substring-before> "foobar" "bar")
	))
     	(test (eq "bar"
		(<http://www.w3.org/2007/rif-builtin-function#substring-after> "foobar" "foo")
	))
     	(test (eq (gen-literal "[1=ab][2=]cd")
		(<http://www.w3.org/2007/rif-builtin-function#replace> "abcd" (gen-literal "(ab)|(a)") (gen-literal "[1=$1][2=$2]"))
	))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#contains> "foobar" "foo"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#starts-with> "foobar" "foo"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#ends-with> "foobar" "bar"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#matches> "abracadabra" (gen-literal "^a.*a$")))
     	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-anyURI>
		(gen-literal "http://www.example.org" "http://www.w3.org/2001/XMLSchema#anyURI" ) ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-anyURI> 1 ))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-anyURI>
		(<http://www.w3.org/2001/XMLSchema#anyURI> "http://www.example.org"  )))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
