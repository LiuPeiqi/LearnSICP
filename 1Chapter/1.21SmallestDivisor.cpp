//(define (smallest-divisor n)
//  (find-divisor n 2))
//(define (find-divisor n test-divisor)
//  (cond ((> (square test-divisor) n) n)
//      ((divides? test-divisor n) test-divisor)
//      (else (find-divisor n (+ test-divisor 1)))))
//(define (divides? a b)
//  (= (remainder b a) 0))
//(define prime? n)
//  (= n (smallest-divisor n)))
//(define (remainder a b)
//  (- a (*(/ a b) b)))//%
#include <Windows.h>
#include <iostream>
namespace LPQ {
    bool IsDivides(long long a, long long b)
    {
        return 0 == (a%b);
    }

    long long FindDivisor(long long n, long long test_divisor)
    {
        if (test_divisor*test_divisor > n) {
            return n;
        }
        else if (IsDivides(n, test_divisor)) {
            return test_divisor;
        }
        else {
            return FindDivisor(n, test_divisor + 1);
        }
    }

    long long SmallestDivisor(long long n)
    {
        return FindDivisor(n, 2ll);
    }

    bool IsPrime(long long n)
    {
        return n == SmallestDivisor(n);
    }
    
    int SmallestDivisor(std::istream& in, std::ostream& out)
    {
        int n;
        in >> n;
        out <<"Smallest divisor is: "<< SmallestDivisor(n);
        return 0;
    }
    int IsPrime(std::istream&in, std::ostream& out)
    {
        int n;
        in >> n;
        LARGE_INTEGER start;
        QueryPerformanceCounter(&start);
        auto res = IsPrime(n);
        LARGE_INTEGER finish;
        QueryPerformanceCounter(&finish);
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        out << "Is prime? "<<std::boolalpha<< res<<". cost: "<<(0.0+(finish.QuadPart-start.QuadPart))/freq.QuadPart<<"s";
        return 0;
    }
}
