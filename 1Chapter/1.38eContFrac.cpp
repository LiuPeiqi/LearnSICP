//(define (com-cont-frac next-n n next-d d k)
//	(if (> 0 k)
//		(/ n (+ d (com-cont-frac next-n (next-n n) next-d (next-d d) (-
// 1 k)))) 		0))
//

#include <functional>

#include "SICP.h"
#include "Brick/parser_bind.h"

namespace LPQ {

using NextFunc = std::function<double(size_t)>;

double ComContFrac(NextFunc next_n, size_t n, NextFunc next_d, size_t d,
                   size_t k) {
    if (k > 0) {
        return next_n(n) /
               (next_d(d) + ComContFrac(next_n, n + 1, next_d, d + 1, k - 1));
    } else {
        return 0;
    }
}

double oneSequence(size_t n) { return 1; }

double eSequence(size_t n) {
    if (0 == n % 3) {
        return n / 3 * 2;
    } else {
        return 1;
    }
}

double eContFrac(size_t n) {
    return ComContFrac(oneSequence, 1, eSequence, 2, n) + 2.0;
}

static RegisterFunc reg_runc("eContFrac", ParserBind(eContFrac));

}  // namespace LPQ
