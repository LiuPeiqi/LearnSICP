#include <functional>

#include "1Chapter.h"
#include "Brick/parser_bind.h"

using namespace std;
namespace LPQ {
using FuncType = function<double(double)>;
template <typename T, typename G>
G Compose(T f, G g) {
    return f(g);
}

template <typename T, typename G>
G Repeated(T func, G g, size_t times) {
    if (times > 1) {
        return Compose<T, G>(func, Repeated<T, G>(func, g, times - 1));
    }
    return g;
}

FuncType Smooth(FuncType func) {
    double dx = 1;
    return [func, dx](double x) -> double {
        return (func(x - dx) + func(x) + func(x + dx)) / 3.0;
    };
}

double RepeatedSmooth(size_t n, double x) {
    FuncType f = ([](double x) -> double { return 3 * x * x + 4 * x - 1; });
    return Repeated<decltype(Smooth), FuncType>(Smooth, f, n)(x);
}

static RegisterFunc reg_func(
    "RepeatedSmooth", ParserBind<double, size_t, double>(RepeatedSmooth));

}  // namespace LPQ
