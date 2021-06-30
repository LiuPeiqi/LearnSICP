// (define Min(x,y) (if (< x y) (x) (y)))
// (define (SumOfMax (x,y,z) (- (+ x y z) (Min x y z))))

#include <string>

#include "SICP.h"
#include "Brick/parser_bind.h"

namespace LPQ {

double Min(double x, double y) { return x < y ? x : y; }

double SumOf2Max(double x, double y, double z) {
    return (x + y + z) - Min(Min(x, y), z);
}

static RegisterFunc reg_func("SumOf2Max", ParserBind(SumOf2Max));

}  // namespace LPQ
