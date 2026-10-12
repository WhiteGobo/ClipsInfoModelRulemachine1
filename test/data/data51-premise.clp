(defrule rule0
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-hexBinary> "aabb^^http://www.w3.org/2001/XMLSchema#hexBinary"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-base64Binary>
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz%2F%2B0123456789^^http://www.w3.org/2001/XMLSchema#base64Binary"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-hexBinary>
		"aabb^^http://www.w3.org/2001/XMLSchema#hexBinary"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-base64Binary>
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz%2F%2B0123456789^^http://www.w3.org/2001/XMLSchema#string"))

	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-base64Binary>
		"SGVsbG8sIHdvcmxkIQ==^^http://www.w3.org/2001/XMLSchema#base64Binary"))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#is-literal-base64Binary>
		"TWE=^^http://www.w3.org/2001/XMLSchema#base64Binary"))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
