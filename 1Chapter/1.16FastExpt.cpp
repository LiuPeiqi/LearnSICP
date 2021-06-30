// (define (expt-internal v b iter count)
//  (cond ((!< iter count) v)
//      ((< iter 1) expt-internal(b b iter+1 count))
//          ((!> (* 2 iter) count) expt-internal((* v v) b (* 2 iter)
//              count)) (else (if (> (- (* 2 iter) count) (- count iter)) (* v
//              (fast-expt b (- count iter))))
//                      (/ (expt-internal (* v v) b (* 2 iter) count) (fast-expt
//                      b (- (* 2 iter) count)))))
//(define (fast-expt b n)
//          (expt-internal 1 b 0 n))

#include "SICP.h"
#include "Brick/parser_bind.h"

namespace LPQ {
double FastExptInst(double b, int n);
double ExptInternal(double v, double b, int iter, int count) {
    if (iter >= count) {
        return v;
    } else if (iter < 1) {
        return ExptInternal(b, b, ++iter, count);
    } else if (2 * iter <= count) {
        return ExptInternal(v * v, b, 2 * iter, count);
    }

    int mult_remain = count - iter;
    int div_remain = 2 * iter - count;
    if (mult_remain <= div_remain) {
        return v * FastExptInst(b, mult_remain);
    }
    return ExptInternal(v * v, b, 2 * iter, count) /
           FastExptInst(b, div_remain);
}
double FastExptInst(double b, int n) { return ExptInternal(1, b, 0, n); }

double FastExpt2(double b, int n) {
    if (n == 0) {
        return 1;
    }
    auto v = 1.0;
    auto index = 1;
    while (n >= index) {
        if ((n & index) > 0) {
            v *= b;
        }
        b *= b;
        index <<= 1;
    }
    return v;
}

static RegisterFunc reg_fun1("FastExpt1", ParserBind(FastExptInst));
static RegisterFunc reg_fun2("FastExpt2", ParserBind(FastExpt2));

}  // namespace LPQ
