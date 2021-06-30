#include <functional>

#include "SICP.h"
#include "Brick/parser_bind.h"

namespace LPQ {
double CubeRoot(double x) {
    auto square = [](auto x) { return x * x; };
    auto cube = [](auto x) { return x * x * x; };
    auto abs = [](auto x) { return x < 0 ? -x : x; };
    auto good_enough = [&](auto x, auto guass) {
        return abs(x / guass - 1) < 1e-5;
    };
    auto improve = [&](auto x, auto guass) {
        return (x / square(guass) + 2 * guass) / 3;
    };
    std::function<double(double, double)> cube_root_iter;
    cube_root_iter = [&](auto x, auto guass) {
        return good_enough(x, cube(guass))
                   ? guass
                   : cube_root_iter(x, improve(x, guass));
    };
    return cube_root_iter(x, x / 2);
}

static RegisterFunc reg_func("CubeRoot", ParserBind(CubeRoot));

}  // namespace LPQ
