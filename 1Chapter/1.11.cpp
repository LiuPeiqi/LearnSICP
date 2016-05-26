//(define (f_recursion n)
//  (cond ((< 4 n) n)
//          (else (+ f_recursion(n-3) f_recursion(n-2) f_recursion(n-1) ))))

//(define (inter_iter a b c count max)
//  (if (>= count max)
//      (+ a b c)
//      (iter_iter b c (+ a b c) (+ 1 count) max ) ) )
//
//(define (f_iteration n)
//  (if (< 4 n) 
//      n
//      (else (inter_iter(1 2 3 4 n) ) ) ))
#include <Windows.h>

#include <iostream>
namespace LPQ {
    unsigned int f_recursion(unsigned int n)
    {
        if (n <= 3) {
            return n;
        }
        else {
            return f_recursion(n - 1) + f_recursion(n - 2) + f_recursion(n - 3);
        }
    }
    unsigned int inter_iter(unsigned int a, unsigned int b, unsigned int c, unsigned int count, unsigned int max) {
        if (count >= max) {
            return a + b + c;
        }
        return inter_iter(b, c, a + b + c, count + 1, max);
    }
    unsigned int f_iteration(unsigned int n)
    {
        if (n <= 3) {
            return n;
        }
        else {
            return inter_iter(1, 2, 3, 4, n);
        }
    }
    int FRecursion(std::istream &in, std::ostream &out) 
    {
        unsigned int n;
        in >> n;
        LARGE_INTEGER start;
        QueryPerformanceCounter(&start);
        unsigned int result = f_recursion(n);
        LARGE_INTEGER finish;
        QueryPerformanceCounter(&finish);
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        out << result<<"(cost:"<<(finish.QuadPart-start.QuadPart)*1.0/freq.QuadPart<<")";
        return 0;
    }

    int FIteration(std::istream& in, std::ostream& out)
    {
        unsigned int n;
        in >> n;
        LARGE_INTEGER start;
        QueryPerformanceCounter(&start);
        unsigned int result = f_iteration(n);
        LARGE_INTEGER finish;
        QueryPerformanceCounter(&finish);
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        out << result << "(cost:" << (finish.QuadPart - start.QuadPart)*1.0 / freq.QuadPart << ")";
        return 0;
    }

}
