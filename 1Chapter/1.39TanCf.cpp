#include <iostream>
#include "1Chapter.h"
using namespace std;
namespace LPQ {
	int TanCf(istream &in, ostream &out)
	{
		size_t k;
		double x;
		in >> x >> k;
		auto next_d = [](double x) {
			return x + 2;
		};
		out << ComContFrac(NoOperate, -x*x, next_d, 1, k) / -x;
		return 0;
	}
}
