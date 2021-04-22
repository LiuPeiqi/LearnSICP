//(define (f_recursion n)
//  (cond ((< 4 n) n)
//          (else (+ f_recursion(n-3) f_recursion(n-2) f_recursion(n-1) ))))
//
//(define (inter_iter a b c count max)
//  (if (>= count max)
//      (+ a b c)
//      (iter_iter b c (+ a b c) (+ 1 count) max ) ) )
//
//(define (f_iteration n)
//  (if (< 4 n)
//      n
//      (else (inter_iter(1 2 3 4 n) ) ) ))

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {
unsigned int FRecursion(unsigned int n) {
    if (n <= 3) {
        return n;
    } else {
        return FRecursion(n - 1) + FRecursion(n - 2) + FRecursion(n - 3);
    }
}

unsigned int inter_iter(unsigned int a, unsigned int b, unsigned int c,
                        unsigned int count, unsigned int max) {
    if (count >= max) {
        return a + b + c;
    }
    return inter_iter(b, c, a + b + c, count + 1, max);
}

unsigned int FIteration(unsigned int n) {
    if (n <= 3) {
        return n;
    } else {
        return inter_iter(1, 2, 3, 4, n);
    }
}

static RegisterFunc reg_func1("FRecursion", ParserBind(FRecursion));
static RegisterFunc reg_func2("FIteration", ParserBind(FIteration));

}  // namespace LPQ
