(define (test no pred)
  (cond (pred (print (quote -)))
        (#t   (print (quote !)))))
