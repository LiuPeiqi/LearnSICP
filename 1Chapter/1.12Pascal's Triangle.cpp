
// (define (Pascal_internal row,col)
//      (cond ((== row col) 1)
//            ((== col 1) 1)
//            (else (+ (Pascal_internal (- row 1) col) pascal_internal (- row 1) (- col 1))))

#include <iostream>
#include <vector>
namespace LPQ {
    unsigned int PascalInternal(unsigned int row, unsigned int col)
    {
        if (row == col || col == 1) {
            return 1;
        }
        return PascalInternal(row - 1, col - 1) + PascalInternal(row - 1, col);
    }
    int PascalTriangle(std::istream& in, std::ostream& out)
    {
        unsigned int n;
        in >> n;
        for (size_t i = 1; i <= n; ++i) {
            size_t white_count = n - i;
            for (size_t j = 0; j < white_count; ++j) {
                out << " ";
            }
            for (size_t j = 1; j <= i; ++j) {
                out << PascalInternal(i, j) << " ";
            }
            out << std::endl;
        }
        return 0;
    }
    void PascalInternalIterate(std::vector<unsigned int>& result, unsigned int count)
    {
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
    int PascalTriangleIterate(std::istream& in, std::ostream& out)
    {
        unsigned int n;
        in >> n;
        auto result = std::vector<unsigned int>(n);
        for (size_t i = 1; i <= n; ++i) {
            size_t white_count = n - i;
            for (size_t j = 0; j < white_count; ++j) {
                out << " ";
            }
            PascalInternalIterate(result, i);
            for (size_t j = 0; j < i;++j) {
                out << result[j] << " ";
            }
            out << std::endl;
        }
    return 0;
    }
}
