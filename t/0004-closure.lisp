(define (make-adder x)
    (lambda (y)
        (+ x y)))

(define eight-adder (make-adder 8))
(define three-adder (make-adder 3))
(define seven-adder (make-adder 7))

(test   0  (= (three-adder 9) 12))
(test   1  (= (eight-adder 2) 10))
(test   2  (= (seven-adder 2)  9))
(test   3  (= (eight-adder 5) 13))
(test   4  (= (three-adder 3)  6))
(test   5  (= (seven-adder 0)  7))
(test   6  (= (eight-adder 1)  9))

(define (make-account)
    (define value 0)
    (lambda (action x)
        (cond ((= action (quote deposit))
                   (set! value (+ value x)))
              ((= action (quote withdraw))
                   (set! value (- value x)))
              ((= action (quote get))
                   value))))

(define acc-a (make-account))
(define acc-b (make-account))

(test   7  (= (acc-a (quote get)) 0))

(acc-a (quote deposit) 100)

(test   8  (= (acc-a (quote get)) 100))
(test   9  (= (acc-b (quote get)) 0))

(acc-a (quote withdraw) 60)
(acc-b (quote deposit)  30)
(acc-a (quote deposit)   2)
(acc-b (quote withdraw)  1)
(acc-b (quote deposit)  85)

(test  10  (= (acc-b (quote get)) 114))
(test  11  (= (acc-a (quote get)) 42))

(define acc-c (make-account))
(acc-c (quote deposit) 10)
(acc-c (quote deposit)  4)
(acc-b (quote withdraw) 7)
(acc-c (quote withdraw) 3)
(acc-c (quote deposit)  8)

(test  12  (= (acc-c (quote get)) 19))
(test  13  (= (acc-b (quote get)) 107))

;; test apply
(test  14  (= (apply (lambda (x) x) (list 42)) 42))
(test  15  (= (apply (lambda (x) x) (list (quote a))) (quote a)))
(test  16  (= (apply (lambda (x) x) (list (quote a)))
	      ((lambda (x) x) (quote a))))