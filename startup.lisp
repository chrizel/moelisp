(define x 3)
(define y 4)

(define (square x)
    (* x x))

(define (not x)
    (cond (x nil)
          (#t #t)))

(define (list params...)
    params);

(define (print-list x)
 (cond (x (println (car x))
          (print-list (cdr x)))))

(defmacro (if c then else...)
 (list (quote cond) (list c then) 
                    (cons #t else)))

(defmacro (when c then)
 (list (quote cond) (list c then)))
