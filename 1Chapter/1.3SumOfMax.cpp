// (define Min(x,y) (if (< x y) (x) (y)))
// (define (SumOfMax (x,y,z) (- (+ x y z) (Min x y z))))

#include <iostream>
namespace LPQ {
    int SumOf2Max(std::istream &in, std::ostream &out)
    {
        auto Min = [](auto x, auto y) {return x < y ? x : y; };
        auto SumOf2max = [&Min](auto x, auto y, auto z) {return (x + y + z) - Min(Min(x, y), z); };
        int x, y, z;
        in >> x;
        do {
            in >> y >> z;
            x = SumOf2max(x, y, z);
            while (in.peek() == ' ') {
                in.get();
            }
        } while (in.peek() != '\n');
        out << x;
        return 0;
    }
}