// (define (perimeter rect)
//  (+ (* 2 (height rect))
//      (* 2 (width rect))))
//
// (define (area rect)
//  (* (height rect) (width rect)))
//
// (define (add-point p1 p2)
//  (make-point
//      (+ (x-point p1) (x-point p2))
//      (+ (y-point p1) (y-point p2)))
//
// (define (sub-point p1 p2)
//  (make-point
//      (- (x-point p1) (x-point p2))
//      (- (y-point p1) (y-point p2)))
//
// (define (distance p1 p2)
//  ((lambda (p)
//      (sqrt
//          (sqr (x-point p))
//          (sqr (y-point p))))
//   (sub-point p1 p2))
//
// (define (dot-point p1 p2)
//  (+ (* (x-point p1) (y-point p2))
//      (* (x-point p2) (y-point p1))))
//
// (define (slop p1 p2)
//  ((lambda (p)
//      (/ (y-point p) (x-point)))
//  (sub-point p2 p1)))
//
// (define (height rect)
//  (distance (p2-rect rect) (p3-rect rect)))
//
// (define (width rect)
//  (distance (p1-rect rect) (p2-rect rect)))
//
// (define (make-rect-1 p1 p2 p3)
//  (cons
//      (cons p1 p2)
//      p3))
//
// (define (p1-rect rect)
//  (car (car rect)))
//
// (define (p2-rect rect)
//  (cdr (car rect)))
//
// (define (p3-rect rect)
//  (cdr rect))
//
// (define (p4-rect rect)
//  ((lambda (p1 p2 p3)
//      (cond ((= (- (x-point p3) (x-point p2)) 0)
//          (make-point
//              (x-point p1)
//              (+ (y-point p1) (height rect))))
//      (else
//          (lambda (cos-angle h)
//              (lambda (delta-y)
//                  (make-point
//                      (+ (x-point p1) (slop p1 p2))
//                      (+ (y-point p1) delta-y)))
//              (* cos-angle h))
//          (/ (dot-point p1 p2) (distance p1 p2))
//          (height rect)))
//  (p1-rect rect) (p2-rect rect) (p3-rect rect)))

#include <cmath>
#include <functional>

namespace LPQ {
using Point = std::function<double(size_t)>;
double XPoint(Point point) { return point(0); }

double YPoint(Point point) { return point(1); }

Point MakePoint(double x, double y) {
    return [=](size_t index) { return index == 0 ? x : y; };
}

using Rect = std::function<Point(size_t)>;

Rect MakeRect(Point p0, Point p1, Point p2) {
    return [=](size_t index) {
        switch (index) {
            case 0:
                return p0;
            case 1:
                return p1;
            case 2:
            default:
                return p2;
        }
    };
}

Point RectP0(Rect rect) { return rect(0); }

Point RectP1(Rect rect) { return rect(1); }

Point RectP2(Rect rect) { return rect(2); }

Point Sub(Point p1, Point p2) {
    return MakePoint(XPoint(p1) - XPoint(p2), YPoint(p1) - YPoint(p2));
}

double Dot(Point p1, Point p2) {
    return XPoint(p1) * YPoint(p2) + YPoint(p1) * XPoint(p2);
}

double Magnitude(Point p) {
    return std::sqrt(std::pow(XPoint(p), 2) + std::pow(YPoint(p), 2));
}

double Distance(Point p1, Point p2) { return Magnitude(Sub(p1, p2)); }

double Height(Rect rect) { return Distance(RectP0(rect), RectP1(rect)); }

double Width(Rect rect) { return Distance(RectP1(rect), RectP2(rect)); }

Point RectP3(Rect rect) {
    if (XPoint(RectP1(rect)) == XPoint(RectP2(rect))) {
        return MakePoint(XPoint(RectP0(rect)),
                         YPoint(RectP0(rect)) + Height(rect));
    }

    auto delta_y = (XPoint(RectP1(rect)) - XPoint(RectP0(rect))) *
                   Height(rect) / Width(rect);
    auto sub = Sub(RectP1(rect), RectP0(rect));
    auto delta_x = YPoint(sub) / XPoint(sub) * delta_y;
    return MakePoint(XPoint(RectP0(rect)) + delta_x,
                     YPoint(RectP0(rect)) + delta_y);
}

double Perimeter(Rect rect) { return 2 * Height(rect) + 2 * Width(rect); }

double Area(Rect rect) { return Height(rect) * Width(rect); }

Rect MakeRect2(Point p0, double width, double height, double alpha) {
    return [=](size_t index) {
        switch (index) {
            case 0:
                return p0;
            case 1:
                return MakePoint(XPoint(p0) + std::cos(alpha) * width,
                                 YPoint(p0) - std::sin(alpha) * height);
            case 2:
                return MakePoint(XPoint(p0) + std::cos(alpha) * width +
                                     std::sin(alpha) * height,
                                 YPoint(p0) - std::sin(alpha) * height +
                                     std::cos(alpha) * height);
            case 3:
            default:
                return MakePoint(XPoint(p0) + std::sin(alpha) * width,
                                 YPoint(p0) + std::cos(alpha) * height);
        }
    };
}

Point RectP3New(Rect rect) { return rect(3); }

}  // namespace LPQ
