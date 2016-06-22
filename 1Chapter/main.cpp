#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

#include "1Chapter.h"

typedef std::function<int(std::istream&, std::ostream&)> TestFunc;
typedef std::unordered_map<std::string, TestFunc> TestFuncMap;

TestFuncMap InitFunctionalMap(void)
{
    TestFuncMap map;
    map[std::string("SumOf2Max")] = LPQ::SumOf2Max;
    map[std::string("SumOfMax_2")] = LPQ::SumOfMax<2>;
    map[std::string("SumOfMax_10")] = LPQ::SumOfMax<10>;
    map[std::string("CubeRoot")] = LPQ::CubeRoot;
    map[std::string("FRecursion")] = LPQ::FRecursion;
    map[std::string("FIteration")] = LPQ::FIteration;
    map[std::string("PascalTriangle")] = LPQ::PascalTriangle;
    map[std::string("PascalTriangleIterate")] = LPQ::PascalTriangleIterate;
    map[std::string("Sine")] = LPQ::Sine;
    map[std::string("FastExpt")] = LPQ::FastExpt;
    map[std::string("IsPrime")] = LPQ::IsPrime;
    map[std::string("SmallestDivisor")] = LPQ::SmallestDivisor;
    map[std::string("SearchForPrimes")] = LPQ::SearchForPrimes;
    map[std::string("IntegralCube")] = LPQ::IntegralCube;
    map[std::string("SimpsonIntegralCube")] = LPQ::SimpsonIntegralCube;
    map[std::string("PI")] = LPQ::PI;
    map[std::string("PrimeSum")] = LPQ::PrimeSum;
    map[std::string("CoPrimeProduct")] = LPQ::CoPrimeProduct;
    return map;
}

int main(void)
{
    TestFuncMap map = InitFunctionalMap();
    while (std::cin) {
        std::cout << ">>";
        std::string func;
        std::cin >> func;
        auto iter = map.find(func);
        if (iter != std::end(map)) {
            iter->second(std::cin, std::cout);
        }
        else if (std::string("Exit") == func) {
            break;
        }
        else {
            std::getline(std::cin, func);
            std::cout << "Not have this function!";
        }
        std::cout << std::endl;
    }
    return 0;
}