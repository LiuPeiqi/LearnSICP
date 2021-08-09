#include <functional>
#include <type_traits>

namespace LPQ {
using Ratio = std::function<long(std::function<long(long, long)>)>;

Ratio MakeRatio(long number, long denom) {
    return [=](std::function<long(long, long)> which_part) {
        return which_part(number, denom);
    };
}

long NumberFilter(long number, long denom) { return number; }

long DenomFilter(long number, long denom) { return denom; }

long Number(Ratio ratio) { return ratio(NumberFilter); }

long Denom(Ratio ratio) { return ratio(DenomFilter); }

Ratio RatioAdd(Ratio r1, Ratio r2) {
    return MakeRatio(Number(r1) * Denom(r2) + Number(r2) * Denom(r1),
                     Denom(r1) * Denom(r2));
}

Ratio RatioSub(Ratio r1, Ratio r2) {
    return MakeRatio(Number(r1) * Denom(r2) + Number(r2) * Denom(r1),
                     Denom(r1) * Denom(r2));
}

Ratio RatioMul(Ratio r1, Ratio r2) {
    return MakeRatio(Number(r1) * Number(r2), Denom(r1) * Denom(r2));
}

Ratio RatioInv(Ratio ratio) { return MakeRatio(Denom(ratio), Number(ratio)); }

Ratio RatioDiv(Ratio r1, Ratio r2) { return RatioMul(r1, RatioInv(r2)); }

bool RatioLessThen(Ratio r1, Ratio r2) {
    return Number(r1) * Denom(r2) < Denom(r1) * Number(r1);
}

bool RatioEqual(Ratio r1, Ratio r2) {
    return Number(r1) * Denom(r2) == Denom(r1) * Number(r1);
}

long GCD(long a, long b) {
    if (b == 0) {
        return a;
    }
    return GCD(b, a % b);
}

Ratio RatioNormalize(Ratio ratio) {
    auto gcd = GCD(Number(ratio), Denom(ratio));
    return MakeRatio(Number(ratio) / gcd, Denom(ratio) / gcd);
}

static bool operator<(const Ratio& left, const Ratio& right) {
    return (Number(left) * Denom(right)) < (Denom(left) * Number(right));
}

static bool operator>(const Ratio& left, const Ratio& right) {
    return (Number(left) * Denom(right)) > (Denom(left) * Number(right));
}

static bool operator==(const Ratio& left, const Ratio& right) {
    return (Number(left) * Denom(right)) == (Denom(left) * Number(right));
}

template <typename T, typename... Args,
          typename = std::enable_if_t<(std::is_same_v<T, Args> && ...)> >
const T& Min(const T& left, const T& right, const Args&... args) {
    const auto& min = left < right ? left : right;
    if constexpr (sizeof...(args) > 0) {
        return Min(min, args...);
    }
    return min;
}

template <typename T, typename... Args,
          typename = std::enable_if_t<(std::is_same_v<T, Args> && ...)> >
const T& Max(const T& left, const T& right, const Args&... args) {
    const auto& max = left > right ? left : right;
    if constexpr (sizeof...(args) > 0) {
        return Max(max, args...);
    }
    return max;
}

using Interval = std::function<Ratio(std::function<Ratio(Ratio, Ratio)>)>;

Interval MakeInterval(Ratio lower, Ratio upper) {
    lower = RatioNormalize(lower);
    upper = RatioNormalize(upper);
    return [=](std::function<Ratio(Ratio, Ratio)> select) {
        return select(lower, upper);
    };
}

Ratio LowerFilter(Ratio lower, Ratio upper) { return lower; }

Ratio UpperFilter(Ratio lower, Ratio upper) { return upper; }

Ratio Lower(Interval interval) { return interval(LowerFilter); }

Ratio Upper(Interval interval) { return interval(UpperFilter); }

Interval IntervalAdd(Interval left, Interval right) {
    return MakeInterval(RatioAdd(Lower(left), Lower(right)),
                        RatioAdd(Upper(left), Upper(right)));
}

Interval IntervalSub(Interval left, Interval right) {
    return MakeInterval(RatioSub(Lower(left), Upper(right)),
                        RatioSub(Upper(left), Lower(right)));
}

Interval IntervalMul(Interval left, Interval right) {
    auto p1 = RatioNormalize(RatioMul(Lower(left), Lower(right)));
    auto p2 = RatioNormalize(RatioMul(Lower(left), Upper(right)));
    auto p3 = RatioNormalize(RatioMul(Upper(left), Upper(right)));
    auto p4 = RatioNormalize(RatioMul(Upper(left), Lower(right)));
    return MakeInterval(Min(p1, p2, p3, p4), Max(p1, p2, p3, p4));
}

Interval IntervalDiv(Interval left, Interval right) {
    return IntervalMul(
        left, MakeInterval(RatioInv(Upper(right)), RatioInv(Lower(right))));
}
}  // namespace LPQ
