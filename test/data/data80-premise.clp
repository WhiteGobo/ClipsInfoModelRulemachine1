(defrule rule0
	=>
	(AssertEqual <http://example.org/A> <http://example.org/B>)
	(AssertEqual <http://example.org/B> <http://example.org/A>)
)

(defrule rule1
	;Equal sorts left and right so not both these facts can be true
	(Equal (left <http://example.org/A>) (right <http://example.org/B>))
	(Equal (left <http://example.org/B>) (right <http://example.org/A>))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
