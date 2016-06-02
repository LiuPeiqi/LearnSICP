//(define (cube x) (* x x x))
//(define (p x) (- (* 3 x) (* 4 (cube x) ) ) )
//(define (sine angle)
//      (if (not (> (abs angle) 0.1))
//      angle
//      (p (sine (/ angle 3)))))
// log(10x)/log(3);
#include <iostream>
namespace LPQ {
    static double Cube(double x)
    {
        return x*x*x;
    }

    static double p(double x)
    {
        return 3 * x - 4 * Cube(x);
    }
    static double ABS(double x)
    {
        return x > 0 ? x : -x;
    }
    static double Sin(double angle)
    {
        if (ABS(angle) <= 0.1) {
            return angle;
        }
        return p(Sin(angle / 3.0));
    }

    int Sine(std::istream& in, std::ostream& out)
    {
        double angle;
        in >> angle;
        out << Sin(angle);
        return 0;
    }
}