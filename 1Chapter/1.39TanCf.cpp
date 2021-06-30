#include <functional>

#include "SICP.h"
#include "Brick/parser_bind.h"

using namespace std;
namespace LPQ {

using NextFunc = std::function<double(size_t)>;
double ComContFrac(NextFunc next_n, size_t n, NextFunc next_d, size_t d,
                   size_t k);

double TanCf(double x, size_t n) {
    auto x_2 = -x * x;
    auto next_n = [=](size_t n) {
        if (n == 1) {
            return x;
        }
        return x_2;
    };
    auto next_d = [=](size_t d) { return d * 2 - 1; };
    return ComContFrac(next_n, 1, next_d, 1, n);
}

static RegisterFunc reg_func("TanCf", ParserBind(TanCf));
}  // namespace LPQ
