// (define (count-change amount)
//  (cc amount 5))
//
// (define (cc amount kinds-of-coins)
//  (cond ((= amount 0) 1)
//      ((or (< amount 0) (= kinds-of-coins 0)) 0)
//          (else (+ (cc amount (- kinds-of-coins 1))
//              (cc (- amount (first-denomination kinds-of-coins))
//                  kinds-of-coins)))))
//
// (define (first-denomination kinds-of-coins)
//  (cond ((= kinds-of-coins 1) 1)
//      ((= kinds-of-coins 2) 5)
//      ((= kinds-of-coins 3) 10)
//      ((= kinds-of-coins 4) 25)
//      ((= kinds-of-coins 5) 50)))
//

#include <array>
#include <functional>

#include "1Chapter.h"
#include "Brick/parser_bind.h"

namespace LPQ {
size_t CountChange(size_t amount) {
    auto first_denomination = [](int kinds_of_coins) -> int {
        static std::array<size_t, 5> kinds = {1, 5, 10, 25, 50};
        return kinds[kinds_of_coins - 1];
    };

    std::function<int(int, int)> cc;
    cc = [&](int amount, int kinds_of_coins) {
        if (amount == 0) {
            return 1;
        } else if (amount < 0 || kinds_of_coins == 0) {
            return 0;
        }
        return cc(amount, kinds_of_coins - 1) +
               cc(amount - first_denomination(kinds_of_coins), kinds_of_coins);
    };
    return cc(amount, 5);
}

static RegisterFunc reg_func("CountChange", ParserBind(CountChange));

}  // namespace LPQ
