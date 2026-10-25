(defrule rule0
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
	(bind ?data (<http://white.gobo/ClipsInfoModelRulemachine1#export-rif> "ttl"))
	(println "CIMR1:export-rif produced: " ?data)
	(reset)
	(<http://white.gobo/ClipsInfoModelRulemachine1#load> ?data "ttl")
	(facts)
	(halt)
)
