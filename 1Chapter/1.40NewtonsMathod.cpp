#include <functional>

#include "SICP.h"
#include "Brick/parser_bind.h"

namespace LPQ {
using Func = std::function<double(double)>;
Func Deriv(Func g, double dx) {
    return [=](double x) { return (g(x + dx) - g(x)) / dx; };
}

Func NewtonTrans(Func f) {
    auto deriv = Deriv(f, 0.000001);
    return [=](double x) { return x - f(x) / deriv(x); };
}

extern double FixedPoint(Func f, double first_guess);

double NewtonMethod(Func f, double guess) {
    return FixedPoint(NewtonTrans(f), guess);
}

Func Cubic(double a, double b, double c) {
    return [=](double x) {
        auto x_2 = x * x;
        return x_2 * x + a * x_2 + b * x + c;
    };
}

double CubicRoot(double a, double b, double c) {
    return NewtonMethod(Cubic(a, b, c), 2);
}

static RegisterFunc reg_func("CubicRoot", ParserBind(CubicRoot));

}  // namespace LPQ
