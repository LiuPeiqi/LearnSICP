#include <iostream>
#include <iterator>
#include <string>

#include "1Chapter.h"

LPQ::FuncWrapMap& GetMap() {
    static LPQ::FuncWrapMap func_map;
    return func_map;
}

LPQ::RegisterFunc::RegisterFunc(const std::string& name, const FuncWrap& func) {
    auto& func_map = GetMap();
    func_map[name] = func;
}

int main(void) {
    auto& func_map = GetMap();
    while (std::cin) {
        std::cout << ">>";
        std::string func;
        std::cin >> func;
        auto iter = func_map.find(func);
        if (iter != std::end(func_map)) {
            iter->second(std::cin, std::cout);
        } else if (func == "Exit" || func == "exit") {
            break;
        } else if (func == "-l" || func == "--list" || func == "-h" ||
                   func == "--help") {
            std::transform(func_map.begin(), func_map.end(),
                           std::ostream_iterator<std::string>(std::cout, ",\n"),
                           [](const auto& item) { return item.first; });
        } else {
            std::getline(std::cin, func);
            std::cout << "Not have this function!";
        }
        std::cout << std::endl;
    }
    return 0;
}
