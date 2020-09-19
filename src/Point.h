#ifndef POINT_H
#define POINT_H

#include <cmath>
class Point {
    public:
        double x_, y_;

        Point() {};
        Point(double x, double y) : x_(x), y_(y) {};

        double operator*(const Point& o) {
            return (*this-o).Length();
        }

        Point operator-(const Point& o) {
            return Point(x_-o.x_,y_-o.y_);
        }

        Point operator+(const Point& o) { // extra implemented
            return Point(x_+o.x_,y_+o.y_);
        }
        

        double operator>>(const Point& o) {
            return x_*o.x_+y_*o.y_;
        }
        
        double Length() {
            return sqrt(x_ * x_ + y_ * y_);
        }

        void Normalize() {
            x_=x_/Length();
            y_=y_/Length();
        }
};

#endif