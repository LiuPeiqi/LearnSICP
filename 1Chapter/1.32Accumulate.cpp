//(define (accumulate combiner null-value term a next b)
//  (if (> a b)
//      null-value
//      (combiner (term a)
//          (accumulate combiner null-value term (next a) b))))

//(define (accumulate combiner null-value term a next b)
//  (define (inter a result)
//      (if (> a b)
//          result
//          (inter (next a) (combiner term(a) result))))
//  (inter a null-value)

#include <functional>

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {
using namespace std;

typedef function<bool(double)> FILTER;
typedef function<double(double, double)> COMBINER;
typedef function<double(double)> UNIQUE_OP;

double Accumulate(COMBINER combiner, double null_value, UNIQUE_OP term,
                  double a, UNIQUE_OP next, double b) {
    if (a > b) {
        return null_value;
    }
    return combiner(term(a),
                    Accumulate(combiner, null_value, term, next(a), next, b));
}

double AccumulateIter(COMBINER combiner, double null_value, UNIQUE_OP term,
                      double a, UNIQUE_OP next, double b) {
    double result = null_value;
    for (; a > b; a = next(a)) {
        result = combiner(term(a), result);
    }
    return result;
}

static double Sum(UNIQUE_OP term, double a, UNIQUE_OP next, double b) {
    return AccumulateIter([](auto a, auto b) { return a + b; }, 0, term, a,
                          next, b);
}

static double Product(UNIQUE_OP term, double a, UNIQUE_OP next, double b) {
    return AccumulateIter([](auto a, auto b) { return a * b; }, 1, term, a,
                          next, b);
}

double FilteredAccumulate(FILTER filter, COMBINER combiner, double null_value,
                          UNIQUE_OP term, double start, UNIQUE_OP next,
                          double end) {
    double result = null_value;
    for (; start <= end; start = next(start)) {
        if (filter(start)) {
            result = combiner(result, term(start));
        }
    }
    return result;
}

extern bool IsPrime(long long n);

double PrimeSum(double a, double b) {
    return FilteredAccumulate(
        [](double a) { return IsPrime(static_cast<long long>(a)); },
        [](auto a, auto b) { return a + b; }, 0, [](auto a) { return a; }, a,
        [](auto a) { return a + 1; }, b);
}

static RegisterFunc reg_prime_sum("PrimeSum", ParserBind(PrimeSum));

long long GCD(long long a, long long b) {
    if (b <= 0) {
        return a;
    }
    return GCD(b, a % b);
}

double CoPrimeProduct(double a, double b) {
    auto filter = [&](auto item) {
        long long n = static_cast<long long>(b);
        if (GCD(static_cast<long long>(item), b) == 1) {
            return true;
        } else {
            return false;
        }
    };
    return FilteredAccumulate(
        filter, [](auto a, auto b) { return a * b; }, 1,
        [](auto a) { return a; }, a, [](auto a) { return a + 1; }, b);
}

static RegisterFunc reg_co_prime_product("CoPrimeProduct",
                                         ParserBind(CoPrimeProduct));

}  // namespace LPQ
