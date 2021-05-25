//(define (sum term a next b)
//  (if (> a b)
//   0
//  (+ (term a)
//      (sum term (next a) next b))))
//(define (cube x)
//  (* x x x)
//(define (integral f a b dx)
//  (define (add-dx x) (+ x dx))
//  (* (sum f (+ a (/ dx 2)) add-dx b)
//      dx))
//(define (simpson-integral f a b n)
//  (define (calc-h a b n) (/ (- b a) n)))
//  (define (simpson-integral-internal f a b h)
//      (define (add-2h x h) (+ x h h)))
//      (sum f a add-2h b)
//  (* (/ (calc-h a b n) 3)
//      (   -
//          (+ (*   2
//                  (simpson-integral-internal f a b (calc-h a b n)))
//              (*  4
//                  (simpson-integral-internal f (+ a (calc-h a b n)) b (calc-h
//                  a b n))))
//          a b)))
//

#include <functional>

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {
using namespace std;
double Sum(function<double(double)> term, double a,
           function<double(double)> next, double b) {
    if (a > b) {
        return double();
    }
    return term(a) + Sum(term, next(a), next, b);
}

double Cube(double x) { return x * x * x; }

double Integral(function<double(double)> f, double a, double b, double dx) {
    auto next = [&dx](double x) { return x + dx; };
    return Sum(f, a + dx / 2, next, b) * dx;
}

double SimpsonIntegral(function<double(double)> f, double a, double b,
                       size_t n) {
    double h = (b - a) / n;
    auto add2h = [&h](double x) { return x + h + h; };
    double result = Sum(f, a, add2h, b) * 2 - a + b;
    result += Sum(f, a + h, add2h, b) * 4;
    result *= h / 3;
    return result;
}

double IntegralCube(double a, double b, double dx) {
    return Integral(Cube, a, b, dx);
}

double SimpsonIntegralCube(double a, double b, size_t n) {
    return SimpsonIntegral(Cube, a, b, n);
}

static RegisterFunc reg_cub("IntegralCube", ParserBind(IntegralCube));

static RegisterFunc reg_cub2("SimpsonIntegralCube",
                             ParserBind(SimpsonIntegralCube));

}  // namespace LPQ
