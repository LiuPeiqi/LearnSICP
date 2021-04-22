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

template <typename Ret, typename... Args>
std::function<Ret(Args...)> timeof(const std::string& token,
                                   Ret (*func)(Args...)) {
    return [=](Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        Ret result = func(args...);
        auto finish = std::chrono::high_resolution_clock::now();
        Cost(token, finish - start);
        return result;
    };
}

template <typename Ret, typename... Args>
std::function<Ret(Args...)> timeof(const std::string& token,
                                   const std::function<Ret(Args...)>& func) {
    return [=](Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        Ret result = func(args...);
        auto finish = std::chrono::high_resolution_clock::now();
        Cost(token, finish - start);
        return result;
    };
}

}  // namespace LPQ

