(defmacro (macro-a) 1)
(test    0  (= (macro-a) 1))

(defmacro (macro-b x) x)
(test    1  (= (macro-b 42) 42))
(test    2  (= (macro-b (list 1 2 3)) (list 1 2 3)))

(defmacro (macro-c func a b)
    (list func a b))
(test    3  (= (macro-c + 1 2) 3))

(defmacro (call-reverse body...)
  (reverse body))
(test    4  (= (call-reverse 1 2 3 +) 6))
(test    5  (= (call-reverse 1 2 3 -) 0))

(defmacro (inner-macro b)
  (list (quote *) b 3))
(defmacro (outer-macro a b)
  (list (quote +) a (inner-macro b)))
(test    6  (= (outer-macro 1 2) 7))
(test    7  (= (macro-expand (outer-macro 1 2))
	       (quote (+ 1 6))))
