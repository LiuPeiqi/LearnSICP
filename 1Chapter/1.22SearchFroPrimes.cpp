#include <Windows.h>

#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include<string>

namespace LPQ {
    extern bool IsPrime(long long n);
    bool IsEven(long long n)
    {
        return n % 2 == 0;
    }

    long long Square(long long x)
    {
        return x*x;
    }

    long long Expmod(long long base, long long exp, long long n)
    {
        if (0 == exp) {
            return 1;
        }
        else if (IsEven(exp)) {
            return Square(Expmod(base, exp >> 1, n)) % n;
        }
        else {
            return (base * Expmod(base, exp - 1, n)) % n;
        }
    }
    
    bool FermatTest(long long n)
    {
        static std::default_random_engine e;
        std::uniform_int_distribution<unsigned long long>u(0,n);
        auto rand = u(e) + 1;
        return Expmod(rand, n, n) == rand;
    }

    bool IsPrimeFast(long long n, long long times)
    {
        if (0 == times) {
            return true;
        }
        else if (FermatTest(n)) {
            return IsPrimeFast(n, times - 1);
        }
        else {
            return false;
        }
    }

    bool IsPrimeFast10Times(long long n) 
    {
        return IsPrimeFast(n, 10);
    }

    typedef std::function<bool(long long)> IsPrimeTemplate;
    class Find1stPrime {
    public:
        Find1stPrime(IsPrimeTemplate IsPrimeT) :
            is_prime(IsPrimeT) {}
        long long operator()(long long n)const
        {
            if (IsEven(n)) {
                return operator()(1 + n);
            }
            else if (is_prime(n)) {
                return n;
            }
            else {
                return operator()(n + 2);
            }
        }
    private:
        IsPrimeTemplate is_prime;
    };

    class FindNPrimes {
    public:
        FindNPrimes(const Find1stPrime& _find_1st_prime) :
            find_1st_prime(_find_1st_prime) {}
        bool operator()(long long n, long long count, long long*result)const
        {
            if (count == 0) {
                return true;
            }
            else {
                *result = find_1st_prime(n);
                return operator()(*result + 1, count - 1, result + 1);
            }
        }
    private:
        const Find1stPrime& find_1st_prime;
    };

    int SearchForPrimes(std::istream&in, std::ostream&out)
    {
        long long number;
        in >> number;
        size_t n;
        in >> n;
        std::string which;
        in >> which;
        Find1stPrime fast(IsPrimeFast10Times);
        Find1stPrime normal(IsPrime);
        const Find1stPrime& real = which == "fast" ? fast : normal;
        const FindNPrimes find_n_primes(real);
        std::unique_ptr<long long[]> result(new long long[n]);
        LARGE_INTEGER start;
        QueryPerformanceCounter(&start);
        auto res = find_n_primes(number,n,result.get());
        LARGE_INTEGER finish;
        QueryPerformanceCounter(&finish);
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        out << "The " << n << "th primes which greate than " << number << " is: ";
        for (size_t i = 0; i < n;++i) {
            out << result[i] << " ";
        }
        out<<std::endl<<"The "<<which<<" method cost times: "<< (0.0 + (finish.QuadPart - start.QuadPart)) / freq.QuadPart << "s";
        return 0;
    }
}
