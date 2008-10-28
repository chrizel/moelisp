;;
;; core
;;
(define (list params...)
    params)

(define (!= x y)
 (not (= x y)))

(defmacro (if c then else...)
 (list (quote cond) (list c then) 
                    (cons #t else)))

(defmacro (when c then)
 (list (quote cond) (list c then)))

(define (not x)
    (cond (x nil)
          (#t #t)))

(define (compose funcs...)
 (lambda (args...)
  (reduce apply args funcs)))

(defmacro (let defs body...)
    (list (quote apply) 
        (cons (quote lambda)
            (cons (map car defs) body))
     (cons (quote list) (map second defs))))

;;
;; list operations
;;
(define (map func lst)
 (when (car lst)
     (cons (func (car lst))
           (map func (cdr lst)))))

(define (filter func lst)
 (when (car lst)
     (if (func (car lst))
         (cons (car lst)
               (filter func (cdr lst)))
         (filter func (cdr lst)))))

(define (reduce func init lst)
 (if lst
     (func (car lst)
           (reduce func init (cdr lst)))
     init))

(define (length lst)
 (reduce (lambda (_ x) (+ x 1)) 0 lst))

(define (sum lst)
 (reduce + 0 lst))

(define (range from to)
 (let ((from (if to from 0))
       (to (if to to from)))
      (when (> to from)
          (cons from (range (+ from 1) to)))))

(define (print-list x)
 (cond (x (println (car x))
          (print-list (cdr x)))))

(define (second lst)
    (car (cdr lst)))

(define (reverse lst)
    (define (internal-reverse sub-lst new-lst)
        (if sub-lst
            (internal-reverse (cdr sub-lst)
                              (cons (car sub-lst) new-lst))
            new-lst))
    (internal-reverse lst nil))

;;
;; math
;;
(define (square x)
 (* x x))

(define (even x)
 (= (mod x 2) 0))

(define (odd x)
 (not (even x)))


(collect)
