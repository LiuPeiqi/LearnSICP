// (define (fib n)
//  (fib-iter 1 0 0 1 n))
// (define (fib-iter a b p q count)
//  (cond ((= count 0) b)
//      ((even? count)
//          (fib-iter a
//                  b
//                  <??> ;compute p' := p*p + q*q
//                  <??> ;compute q' := q*q + 2*p*q
//                  ( / count 2)))
//      (else (fib-iter (+ (* b q) (* a q) (* a p))
//                      (+ (* b p) (* a q))
//                      p
//                      q
//                      (- count 1)))))
//

#include <tuple>

#include "1Chapter.h"
#include "Brick/parser_bind.h"
#include "Brick/timeof.h"

namespace LPQ {
size_t FibIter(size_t a, size_t b, size_t p, size_t q, size_t count) {
    if (count == 0) {
        return b;
    } else if (count % 2 == 0) {
        auto p2 = p * p;
        auto q2 = q * q;
        return FibIter(a, b, p2 + q2, q2 + 2 * p * q, count / 2);
    } else {
        return FibIter(a * q + b * q + a * p, b * p + a * q, p, q, count - 1);
    }
}

size_t Fib(size_t n) { return FibIter(1, 0, 0, 1, n); }

void MulTrans(size_t& p1, size_t& q1, size_t p2, size_t q2) {
    auto pp = p1 * p2;
    auto qq = q1 * q2;
    q1 = p1 * q2 + p2 * q1 + qq;
    p1 = pp + qq;
}

size_t Fib2(size_t n) {
    size_t p = 0, q = 1;
    size_t pi = p, qi = q;
    size_t iter = 1;
    while (iter < n) {
        if ((n & iter) > 0) {
            MulTrans(p, q, pi, qi);
        }
        MulTrans(pi, qi, pi, qi);
        iter <<= 1;
    }
    return p;
}

RegisterFunc reg_fun1("Fib1", ParserBind(timeof("Fib1", Fib)));
RegisterFunc reg_fun2("Fib2", ParserBind(timeof("Fib2", Fib2)));

}  // namespace LPQ
