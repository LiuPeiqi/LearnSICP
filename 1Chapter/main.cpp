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