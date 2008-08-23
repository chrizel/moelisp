(define x 3)
(define y 4)

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

(define (range from to)
  (when (> to from)
      (cons from (range (+ from 1) to))))

(define (list params...)
    params);

(define (print-list x)
 (cond (x (println (car x))
          (print-list (cdr x)))))


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
