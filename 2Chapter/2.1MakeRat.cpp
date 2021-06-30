// (define (cons x y)
//  (lambda (index)
//      (cond ((= index 0) x)
//          ((= index 1) y)
//          else ())))
//  
// (define (car n) (n 0))
// (define (cdr n) (n 1))
//
// (define (make-rat n d)
//  (cons n d))
//
// (define (number x)
//  (let ((g (gcd (car x) ( cdr x))))
//      (/ (car x) g)))
// 
// (define (denom x)
//  (let ((g (gcd (car x) (cdr x))))
//      (/ (cdr x) g)))
//
// (define (sign x)
//  (cond ((= x 0) 1)
//      ((> x 0) 1)
//      ((< x 0) -1)))
// 
// (define (abs x)
//  (cond ((< x 0) (- x))
//      (else x)))
//
// (define (make-rat n d)
//  (cond ((< (sign (* n d)) 0)
//          (cons (- (abs n)) (abs d)))
//      (else (cons (abs n) (abs d)))))
//
