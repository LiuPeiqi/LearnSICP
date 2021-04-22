#include <chrono>
#include <functional>
#include <iostream>

namespace LPQ {

static double Cost(const std::string& token,
                   std::chrono::duration<double> cost) {
    auto cost_count = cost.count();
    std::cout << token << " cost:" << cost_count << "s" << std::endl;
    return cost_count;
}

template <typename Func, typename... Args>
double timeof(const std::string& token, const Func& func, const Args&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(args...);
    auto finish = std::chrono::high_resolution_clock::now();
    return Cost(token, finish - start);
}

// template <typename Func>
// double timeof(const std::string& token, const Func& func) {
//     auto start = std::chrono::high_resolution_clock::now();
//     func();
//     auto finish = std::chrono::high_resolution_clock::now();
//     return Cost(token, finish - start);
// }

}  // namespace LPQ

