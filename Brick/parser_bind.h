#include <functional>
#include <iostream>
#include <memory>
#include <tuple>
#include <utility>

namespace LPQ {

template <typename Ret, typename Func, typename Tuple, size_t... Indexes>
Ret ParserBindCallWrap(Func func, std::shared_ptr<Tuple> package,
                       std::index_sequence<Indexes...>) {
    return func(std::get<Indexes>(*package)...);
}

template <typename Ret, typename Func, typename Tuple, std::size_t N>
std::function<void(std::istream&, std::ostream&)> ParserBindIMP(
    Func func, std::shared_ptr<Tuple> package) {
    return [=](std::istream& in, std::ostream& out) {
        Ret ret = ParserBindCallWrap<Ret, Func, Tuple>(
            func, package, std::make_index_sequence<N>{});
        out << "return:" << ret << std::endl;
    };
}

template <typename Ret, typename Func, typename Tuple, std::size_t index,
          typename Args0, typename... Args>
std::function<void(std::istream&, std::ostream&)> ParserBindIMP(
    Func func, std::shared_ptr<Tuple> package) {
    return [=](std::istream& in, std::ostream& out) {
        in >> std::get<index>(*package);
        auto Next =
            ParserBindIMP<Ret, Func, Tuple, index + 1, Args...>(func, package);
        Next(in, out);
    };
}

template <typename Ret, typename... Args>
std::function<void(std::istream&, std::ostream&)> ParserBind(
    Ret (*func)(Args...)) {
    auto args = std::make_shared<std::tuple<Args...>>();
    return ParserBindIMP<Ret, Ret(Args...), std::tuple<Args...>, 0, Args...>(
        func, args);
}

template <typename Ret, typename... Args>
std::function<void(std::istream&, std::ostream&)> ParserBind(
    std::function<Ret(Args...)> func) {
    auto args = std::make_shared<std::tuple<Args...>>();
    return ParserBindIMP<Ret, std::function<Ret(Args...)>, std::tuple<Args...>,
                         0, Args...>(func, args);
}

}  // namespace LPQ
