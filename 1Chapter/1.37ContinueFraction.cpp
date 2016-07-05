//(define (cont-frac n d k)
//	(if (= 0 k)
//		(/ n d)
//		(/ n (+ d cont-frac(n d (- k 1))))))

//(define (cont-frac n d k)
//	(define (inter result count)
//		(if (< count k)
//			(inter (/ n (+ d result)) (+ 1 count))
//			(result)))
//	(inter 0 0)
#include <iostream>
namespace LPQ {
	static double InterContFrac(double n, double d, size_t count, size_t k, double result)
	{
		if (count < k) {
			return InterContFrac(n, d, count + 1, k, n / (d + result));
		}
		else {
			return result;
		}
	}

	int ContFrac(std::istream& in,std::ostream&out)
	{
		double n, d;
		size_t k;
		in >> n >> d >> k;
		out << InterContFrac(n, d, 0, k, 0);
		return 0;
	}
}