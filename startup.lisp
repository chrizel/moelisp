(define x 3)
(define y 4)

(define (square x)
 (* x x))

(define (list params...)
    params);

(defmacro (if c then else...)
 (list (quote cond) (list c then) 
                    (cons #t else)))

(defmacro (when c then)
 (list (quote cond) (list c then)))

(define (not x)
    (cond (x nil)
          (#t #t)))

(define (even x)
 (= (mod x 2) 0))

(define (odd x)
 (not (even x)))

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

(define (sum lst)
 (reduce + 0 lst))

(define (range from to)
  (when (> to from)
      (cons from (range (+ from 1) to))))

(define funcs (list car cdr))
(define args (list 1 2 3 4 5))


(define (print-list x)
 (cond (x (println (car x))
          (print-list (cdr x)))))

;(compose car cdr)
;-->
;(lambda (args...) (apply car (apply cdr args)))
;
(define (compose funcs...)
 (lambda (args...)
  (reduce apply args funcs)))


; (defmacro (let defs body...)
;  (define x (
;
; (let ((x 5)
;       (y 3)
;       (z 4))
;  (+ x y z))
; 
; -->
; 
; ((lambda (x y z)
;   (+ x y z)) 5 3 4)
