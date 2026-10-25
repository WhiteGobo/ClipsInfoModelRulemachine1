(defrule rule0
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data82-conclusion.rifps")
	(bind ?data (<http://white.gobo/ClipsInfoModelRulemachine1#export-rdf> "ttl"))
	(println "CIMR1:export-rdf produced: " ?data)
	(reset)
	(<http://white.gobo/ClipsInfoModelRulemachine1#load> ?data "ttl" "http://www.w3.org/ns/entailment/Simple")
	(facts)
	(halt)
)
