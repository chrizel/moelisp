(test   0  (= (cons 1 nil) (cons 1 nil)))
(test   1  (= (car (cons 1 nil)) 1))
(test   2  (= (cons 1 (cons 2 (cons 3 nil)))
              (cons 1 (cons 2 (cons 3 nil)))))
(test   3  (!= (cons 2 (cons 3 (cons 1 nil)))
               (cons 3 (cons 1 (cons 2 nil)))))
(test   4  (= (list 1 2 3) (list 1 2 3)))
(test   5  (!= (list 2 3 1) (list 3 1 2)))
(test   6  (= (cons 1 (cons 2 (cons 3)))
              (list 1 2 3)))
(test   7  (= (length (list 1 2 3)) (length (list 3 2 1))))
(test   8  (!= (length (list 5 6 7)) (length (list 1 2 3 4))))
(test   9  (= (length (list 2 3 4 2)) 4))
(test  10  (= (length (list 42 81)) 2))
(test  11  (= (length nil) 0))
