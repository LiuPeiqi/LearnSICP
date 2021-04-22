// (define (Pascal_internal row,col)
//      (cond ((== row col) 1)
//            ((== col 1) 1)
//            (else (+ (Pascal_internal (- row 1) col) pascal_internal (- row 1)
//            (- col 1))))

#include <iostream>
#include <vector>

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {
unsigned int PascalInternal(unsigned int row, unsigned int col) {
    if (row == col || col == 1) {
        return 1;
    }
    return PascalInternal(row - 1, col - 1) + PascalInternal(row - 1, col);
}

int PascalTriangle(unsigned int n) {
    for (size_t i = 1; i <= n; ++i) {
        size_t white_count = n - i;
        for (size_t j = 0; j < white_count; ++j) {
            std::cout << " ";
        }
        for (size_t j = 1; j <= i; ++j) {
            std::cout << PascalInternal(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

void PascalInternalIterate(std::vector<unsigned int>& result,
                           unsigned int count) {
    result[0] = 1;
    if (2 < count) {
        unsigned int pre = result[0];
        for (size_t i = 2; i < count; ++i) {
            auto temp = pre + result[i - 1];
            pre = result[i - 1];
            result[i - 1] = temp;
        }
    }
    result[count - 1] = 1;
}

int PascalTriangleIterate(unsigned int n) {
    auto result = std::vector<unsigned int>(n);
    for (size_t i = 1; i <= n; ++i) {
        size_t white_count = n - i;
        for (size_t j = 0; j < white_count; ++j) {
            std::cout << " ";
        }
        PascalInternalIterate(result, i);
        for (size_t j = 0; j < i; ++j) {
            std::cout << result[j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

RegisterFunc reg_fun1("PascalTriangle", ParserBind(PascalTriangle));
RegisterFunc reg_fun2("PascalTriangleIterate",
                      ParserBind(PascalTriangleIterate));

}  // namespace LPQ
