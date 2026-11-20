(defrule test
	(test (<http://white.gobo/ClipsInfoModelRulemachine1#can-be-imported>
			"http://example.com/data01-import"))
	=>
	(AssertAtom <http://example.com/ok>)
)
