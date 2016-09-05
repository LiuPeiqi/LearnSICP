#include <iostream>
#include <functional>
#include "1Chapter.h"

using namespace std;
namespace LPQ {
	using FuncType = function<double(double)>;
	template< typename T, typename G>
	G Compose(T f, G g)
	{
		return f(g);
	}

	template <typename T, typename G>
	G Repeated(T func, G g, size_t times)
	{
		if (times > 1) {
			return Compose<T,G>(func, Repeated<T,G>(func, g, times - 1));
		}
		return g;
	}
	int RepeatedSquare(istream& in, ostream& out)
	{
		double x;
		size_t n;
		in >> n >> x;
		auto square = [](double x)->double {return x*x; };
		auto for_square = [square](FuncType f)->FuncType {return [f](double x)->double {return f(x)*f(x); }; };
		out << Repeated<decltype(for_square),FuncType>(for_square, square, n)(x);
		return 0;
	}

	FuncType Smooth(FuncType func)
	{
		double dx = 1;
		return [func,dx](double x)->double {return(func(x - dx) + func(x) + func(x + dx)) / 3.0; };
	}


	int RepeatedSmooth(istream& in, ostream& out)
	{
		double x;
		size_t n;
		in >> n >> x;
		FuncType f = ([](double x)->double {return 3 * x*x + 4 * x - 1; });
		out << Repeated<decltype(Smooth),FuncType>(Smooth, f, n) (x);
		return 0;
	}
}