//(define (expt-internal v b iter count)
//          (cond ((!< iter count) v)
//              ((< iter 1) expt-internal(b b iter+1 count))
//              ((!> (* 2 iter) count) expt-internal((* v v) b (* 2 iter) count))
//              (else (if (> (- (* 2 iter) count) (- count iter)) (* v (fast-expt b (- count iter))))
//                      (/ (expt-internal (* v v) b (* 2 iter) count) (fast-expt b (- (* 2 iter) count)))))
//(define (fast-expt b n)
//          (expt-internal 1 b 0 n))
#include <iostream>
namespace LPQ {
    double FastExptInst(double b, int n);
    double ExptInternal(double v, double b, int iter, int count)
    {
        if (iter >= count) {
            return v;
        }
        else if (iter < 1) {
            return ExptInternal(b, b, ++iter, count);
        }
        else if (2 * iter <= count) {
            return ExptInternal(v*v, b, 2 * iter, count);
        }
        else {
            int mult_remain = count - iter;
            int div_remin = 2 * iter - count;
            return mult_remain <= div_remin ? v * FastExptInst(b, mult_remain)
                : ExptInternal(v*v, b, 2 * iter, count) / FastExptInst(b, div_remin);
        }
    }
    double FastExptInst(double b, int n)
    {
        return ExptInternal(1, b, 0, n);
    }

    int FastExpt(std::istream& in, std::ostream& out)
    {
        double b;
        int n;
        in >> b >> n;
        out << FastExptInst(b, n);
        return 0;
    }
}