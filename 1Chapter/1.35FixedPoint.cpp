// (define tolerance 0.000001)
//
// (define (fixed-point f first-guess)
//  (define (close-enough? v1 v2)
//      (< (abs (- v1 v2)) tolerance))
//  (define (try guess)
//      (let ((next (f guess)))
//          (if (close-enough? guess next)
//              next
//              (try next))))
//  (try first-guess))

#include <cmath>
#include <functional>

#include "SICP.h"
#include "Brick/parser_bind.h"

using Func = std::function<double(double)>;
namespace LPQ {
const double tolerance = 0.00001;

double FixedPoint(Func f, double first_guess) {
    auto close_enough = [&](auto v1, auto v2) {
        return std::abs(v1 - v2) < tolerance;
    };
    Func try_guess = [&](auto guess) {
        auto next = f(guess);
        if (close_enough(guess, next)) {
            return next;
        } else {
            return try_guess(next);
        }
    };
    return try_guess(first_guess);
}

double CosFixedPoint(double first_guess) {
    return FixedPoint([](double x) { return std::cos(x); }, first_guess);
}

double SinPlusCosFixedPoint(double first_guess) {
    return FixedPoint([](double x) { return std::sin(x) + std::cos(x); },
                      first_guess);
}

double SqrtFixedPoint(double x) {
    return FixedPoint([=](double y) { return (x / y + y) / 2; }, 2);
}

double GoldenSection() {
    return FixedPoint([](double x) { return 1 + 1 / x; }, 1);
}

static RegisterFunc reg_cos_fixed_point("CosFixedPoint",
                                        ParserBind(CosFixedPoint));

static RegisterFunc reg_sin_cos_fixed_point("SinPlusCosFixedPoint",
                                            ParserBind(SinPlusCosFixedPoint));

static RegisterFunc reg_sqrt_fixed_point("SqrtFixedPoint",
                                         ParserBind(SqrtFixedPoint));

static RegisterFunc reg_gloden_section("GoldenSection",
                                       ParserBind(GoldenSection));

}  // namespace LPQ

