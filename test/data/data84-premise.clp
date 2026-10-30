(defrule rule0
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data84-conclusion.rifps")
	(bind ?data (<http://white.gobo/ClipsInfoModelRulemachine1#export-rdf> "ttl"))
	(<http://www.w3.org/2007/rif-builtin-action#print> "CIMR1:export-rdf produced: " ?data)
	(reset)
	(<http://white.gobo/ClipsInfoModelRulemachine1#load> ?data "ttl" "http://www.w3.org/ns/entailment/RDFS")
	(facts)
	(halt)
)
