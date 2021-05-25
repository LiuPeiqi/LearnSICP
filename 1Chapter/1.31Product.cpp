//(define (product term a next b)
//  (if (> a b)
//   1
//  (* (term a)
//      (product term (next a) next b))))

//(define (product term a next b)
//  (define (iter a result)
//      (if (> a  b)
//              result
//              (iter next(a) (* result term(a)))))
//  (iter a 1)

#include <functional>

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {

using namespace std;
double Product(function<double(double)> term, double a,
               function<double(double)> next, double b) {
    if (a > b) {
        return 1;
    }
    return term(a) * Product(term, next(a), next, b);
}
double ProductIter(function<double(double)> term, double a,
                   function<double(double)> next, double b) {
    double result = 1;
    for (; a <= b; a = next(a)) {
        result *= term(a);
    }
    return result;
}

double PI(int n) {
    int status = 0;
    auto term = [&status](auto a) {
        if (status++ % 2 == 0) {
            return a / (a + 1);
        } else {
            return (a + 1) / a;
        }
    };
    auto next = [](double factor) { return ++factor; };
    return 4 * ProductIter(term, 2.0, next, static_cast<double>(n));
}

static RegisterFunc reg_func("PI", ParserBind(PI));

}  // namespace LPQ
