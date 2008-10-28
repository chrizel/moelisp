;; This initial tests return some false tests...
;; the do-tests.pl script has hard coded the test
;; results for this test cases, so we make sure
;; that the testing system itself works as intended.
(test   0  #t)
(test   1  nil)
(test   2  #f)
(test   3  9)
(test   4  1)
(test   5  #t)
(test   6  #f)
(test   7  #f)
(test   8  nil)
(test   9  42)
(test  10  #f)
