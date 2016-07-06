//(define (com-cont-frac next-n n next-d d k)
//	(if (> 0 k)
//		(/ n (+ d (com-cont-frac next-n (next-n n) next-d (next-d d) (- 1 k))))
//		0))
//
#include <cmath>
#include<iostream>
#include<functional>

#include "1Chapter.h"
using namespace std;
namespace LPQ {
	double ComContFrac(NextFuc next_n, double n, NextFuc next_d, double d, size_t k)
	{
		if (k > 0) {
			return n / (d + ComContFrac(next_n, next_n(n), next_d, next_d(d), k - 1));
		}else{
			return 0;
		}
	}

	int eContFrac(istream&in, ostream&out)
	{
		size_t k = 0;
		in >> k;
		size_t n=2;
		auto next_d = [&](double x) {
			++n;
			if (0 == n % 3) {
				return floor(n / 3) * 2.0;
			}
			else {
				return 1.0;
			}
		};
		out << ComContFrac(NoOperate, 1, next_d, 1, k) + 2.0;
		return 0;
	}
}
