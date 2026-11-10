(defrule test
	=>
	(AssertAtom
		<http://example.com/import-success>
		(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/non-existend-data")
	)
)
