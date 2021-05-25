//(define (cont-frac n d k)
//	(if (= 0 k)
//		(/ n d)
//		(/ n (+ d cont-frac(n d (- k 1))))))

//(define (cont-frac n d k)
//	(define (inter result count)
//		(if (< count k)
//			(inter (/ n (+ d result)) (+ 1 count))
//			(result)))
//	(inter 0 0)

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {
static double InterContFrac(double n, double d, size_t count, size_t k,
                            double result) {
    if (count < k) {
        return InterContFrac(n, d, count + 1, k, n / (d + result));
    } else {
        return result;
    }
}

double ContFrac(double n, double d, size_t k) {
    return InterContFrac(n, d, 0, k, 0);
}

static RegisterFunc reg_func("ContFrac", ParserBind(ContFrac));

}  // namespace LPQ
