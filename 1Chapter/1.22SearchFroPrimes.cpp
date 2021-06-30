#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "SICP.h"
#include "Brick/parser_bind.h"

namespace LPQ {
bool IsEven(long long n) { return n % 2 == 0; }

long long Square(long long x) { return x * x; }

long long Expmod(long long base, long long exp, long long n) {
    if (0 == exp) {
        return 1;
    } else if (IsEven(exp)) {
        return Square(Expmod(base, exp >> 1, n)) % n;
    } else {
        return (base * Expmod(base, exp - 1, n)) % n;
    }
}

bool FermatTest(long long n) {
    static std::default_random_engine e;
    std::uniform_int_distribution<unsigned long long> u(0, n);
    auto rand = static_cast<long long>(u(e) + 1);
    return Expmod(rand, n, n) == rand;
}

bool IsPrimeFast(long long n, long long times) {
    if (0 == times) {
        return true;
    } else if (FermatTest(n)) {
        return IsPrimeFast(n, times - 1);
    } else {
        return false;
    }
}

template <size_t times>
bool IsPrimeFast(long long n) {
    return IsPrimeFast(n, times);
}

typedef std::function<bool(long long)> IsPrimeTemplate;

class Find1stPrime {
   public:
    Find1stPrime(IsPrimeTemplate IsPrimeT) : is_prime(IsPrimeT) {}
    long long operator()(long long n) const {
        if (IsEven(n)) {
            return operator()(1 + n);
        } else if (is_prime(n)) {
            return n;
        } else {
            return operator()(n + 2);
        }
    }

   private:
    IsPrimeTemplate is_prime;
};

class FindNPrimes {
   public:
    FindNPrimes(const Find1stPrime& _find_1st_prime)
        : find_1st_prime(_find_1st_prime) {}
    bool operator()(long long n, long long count, long long* result) const {
        if (count == 0) {
            return true;
        } else {
            *result = find_1st_prime(n);
            return operator()(*result + 1, count - 1, result + 1);
        }
    }

   private:
    const Find1stPrime& find_1st_prime;
};

extern bool IsPrime(long long number);

bool SearchForPrimes(long long number, size_t n, std::string which) {
    Find1stPrime fast(IsPrimeFast<10>);
    Find1stPrime normal(IsPrime);
    const Find1stPrime& real = which == "fast" ? fast : normal;
    const FindNPrimes find_n_primes(real);
    std::unique_ptr<long long[]> result(new long long[n]);
    auto res = find_n_primes(number, n, result.get());
    std::cout << "The " << n << "th primes which greate than " << number
              << " is: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << result[i] << " ";
    }
    return res;
}

static RegisterFunc reg_func("SearchForPrimes", ParserBind(SearchForPrimes));

}  // namespace LPQ
