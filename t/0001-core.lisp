(test   0  (= 0 0))
(test   1  (= 1 1))
(test   2  (!= 0 1))
(test   3  (!= 1 0))
(test   4  (> 1 0))
(test   5  (= (quote hello) (quote hello)))
(test   6  (!= (quote hello) (quote world)))
(test   7  42)
(test   8  #t)
(test   9  (not #f))
(test  10  (not nil))
(test  11  (= nil (not #t)))
(test  12  (= #t (not #f)))
