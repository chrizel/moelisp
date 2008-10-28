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
(test  12  (!= (list 1 2 3) (list 1 2 3 4)))

;; map tests
(test  13  (= (map (lambda (x) (* x 2))
                   (list 1 2 3))
              (list 2 4 6)))
(test  14  (= (map (lambda (x) x)
                   (list 9 8 7 8))
              (list 9 8 7 8)))

;; filter tests
(test  15  (= (filter (lambda (x) (= x 2))
                      (list 4 3 2 2 9 8 2 3 3 4 8 2 1 3 1 32 22 9 4 2 90))
              (list 2 2 2 2 2)))
(test  16  (= (filter (lambda (x) (= x 3))
                      (list 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20))
              nil))


;; reduce tests
(test  17  (= (reduce (lambda (a b) (+ a b))
                      0
                      (list 1 2 3 4 5))
              15))
(test  18  (= (reduce (lambda (a b) (* a b))
                      1
                      (list 1 2 3 4))
              24))

;; misc list function tests
(test  19  (= (sum (list 1 2 3)) 6))
(test  20  (= (range 5 10) (list 5 6 7 8 9)))
(test  21  (= (range 4) (list 0 1 2 3)))
(test  22  (= (second (list 6 5 2 3)) 5))
(test  23  (= (second (list (list 1 2) (list 2 3) (list 3 4)))
              (list 2 3)))
(test  24  (= (reverse (list 1 2 3)) (list 3 2 1)))
(test  25  (= (reverse (list (cons 1 2) (cons 2 3) (cons 3 4)))
              (list (cons 3 4) (cons 2 3) (cons 1 2))))
