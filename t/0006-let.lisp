(test   0  (= (let ((a 42)) a) 42))
(test   1  (= (let ((a 2) (b 3)) (* a b)) 6))
(test   2  (= (let ((a 3))
		(+ (let ((a 6))
		     (+ (let ((a 9))
			  a) a)) a))
	      18))
(test   3  (= (let* ((a 3)
		     (b (* a 4))
		     (c (* a b)))
		(+ a b c))
	      51))