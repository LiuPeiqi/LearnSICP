#ifndef LEARN_SICP_1CHAPTER_H
#define LEARN_SICP_1CHAPTER_H

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
namespace LPQ {
    int SumOf2Max(std::istream &in, std::ostream &out);
    int CubeRoot(std::istream& in, std::ostream& out);

    int FRecursion(std::istream &in, std::ostream &out);
    int FIteration(std::istream& in, std::ostream& out);

    int PascalTriangle(std::istream& in, std::ostream& out);
    int PascalTriangleIterate(std::istream& in, std::ostream& out);

    int Sine(std::istream& in, std::ostream& out);

    int FastExpt(std::istream& in, std::ostream& out);

    int SmallestDivisor(std::istream& in, std::ostream& out);
    int IsPrime(std::istream&in, std::ostream& out);

    int SearchForPrimes(std::istream&in, std::ostream&out);
        
    int IntegralCube(std::istream& in, std::ostream& out);
    int SimpsonIntegralCube(std::istream& in, std::ostream& out);
    
    int PI(std::istream&, std::ostream&);

    int PrimeSum(std::istream& in, std::ostream& out);
    int CoPrimeProduct(std::istream& in, std::ostream& out);
    
	int ContFrac(std::istream& in, std::ostream&out);
	
	typedef std::function<double(double)> NextFuc;
	inline double NoOperate(double x) {
		return x;
	}
	double ComContFrac(NextFuc next_n, double n, NextFuc next_d, double d, size_t k);
	int eContFrac(std::istream&in, std::ostream&out);
	int TanCf(std::istream &in, std::ostream &out);
	template<typename T,typename CompareFunctionType>
    void MakeOrder(T& l, T& r,CompareFunctionType&CompareOp)
    {
        if (CompareOp(r,l)) {
            std::swap(l, r);
        }
    }
	int RepeatedSquare(std::istream& in, std::ostream& out);
	int RepeatedSmooth(std::istream& in, std::ostream& out);

    template<typename Container,typename OrderFunctionType>
    void BuildHeap(Container& v, OrderFunctionType Order)
    {
        for (auto iter = std::begin(v); iter<(std::end(v) - 1);++iter) {
            Order(*iter, *(iter + 1));
        }
    }
    template<unsigned int TOP_N>
    int SumOfMax(std::istream& in, std::ostream& out)
    {
        auto MaxOrder = [](auto&l,auto&r) {//must is array or vector;
            MakeOrder(l, r, std::greater<decltype(l)>());
        };
        auto MinHeap = [&](auto&v) {
            BuildHeap(v, MaxOrder);
        };
        auto Sum = [](auto b,auto e) {
            typedef decltype(b)::value_type T;
            T sum=T();
            for (; b < e; ++b) {
                sum += *b;
            }
            return sum;
        };
        const size_t length = TOP_N + 1;
        std::array<int,length> a;
        for (size_t i = 0; i < length; ++i) {
            in >> a[i];
        }
        do {
            MinHeap(a);
            if (in.peek() != '\n') {
                in >> a[TOP_N];
            }
            else {
                break;
            }
        } while (true);
        out << Sum(std::begin(a),std::end(a)-1);
        return 0;
    }
}
#endif // !LEARN_SICP_1CHAPTER_H
