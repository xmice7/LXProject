#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    long double x, y;

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
};

struct Triangle {
    Point A, B, C;
  
    long double area() const;

    int contains(const Point &point) const;
    int containsByArea(const Point &point) const;
};

void handler();
#endif