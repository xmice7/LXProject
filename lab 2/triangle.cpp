#include "triangle.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

#define IN 1
#define OUT 0
#define BORDER 2

using namespace std;

const long double EPS = 1e-18L;

long double determinant(Point A, Point B){
    return A.x * B.y - A.y * B.x;
}

long double Triangle::area() const {
    return 0.5L * fabsl(determinant(A, B) + determinant(B, C) + determinant(C, A));
}

long double distance(const Point &p1, const Point &p2){
    return sqrtl(powl(p1.x - p2.x, 2) + powl(p1.y - p2.y, 2));
}

bool between(long double a, long double b, long double x) {
    return x + EPS >= min(a, b) && x <= max(a, b) + EPS;
}

bool onSegment(const Point &p, const Point &a, const Point &b) {
    return fabsl(determinant(p - a, b - a)) < EPS
        && between(a.x, b.x, p.x)
        && between(a.y, b.y, p.y);
}

int containsOnDegenerate(const Triangle &triangle, const Point &point){ 
    long double AB = distance(triangle.A, triangle.B); 
    long double BC = distance(triangle.B, triangle.C);
    long double AC = distance(triangle.A, triangle.C);

    long double maxDist = max({AB, BC, AC});
    Point p1, p2;

    if (fabsl(maxDist - AB) < EPS) { p1 = triangle.A; p2 = triangle.B; }
    else if (fabsl(maxDist - BC) < EPS) { p1 = triangle.B; p2 = triangle.C; }
    else { p1 = triangle.A; p2 = triangle.C; }

    return onSegment(point, p1, p2) ? BORDER : OUT;
}

int Triangle::containsByArea(const Point &point) const {
    long double totalArea = area();
    if(totalArea < EPS){
        return containsOnDegenerate(*this, point);
    }

    long double a1 = Triangle{A, B, point}.area(); 
    long double a2 = Triangle{B, C, point}.area();
    long double a3 = Triangle{A, C, point}.area();

    if(fabsl(totalArea - (a1 + a2 + a3)) < EPS){ 
        if((a1 < EPS && onSegment(point, A, B)) 
           || (a2 < EPS && onSegment(point, B, C))
           || (a3 < EPS && onSegment(point, A, C))) {
            return BORDER;
        }
        return IN;
    }

    return OUT;
}

int Triangle::contains(const Point &point) const {
    if(area() < EPS){
        return containsOnDegenerate(*this, point);
    }

    long double s1 = determinant(point - A, B - A);
    long double s2 = determinant(point - B, C - B);
    long double s3 = determinant(point - C, A - C);

    bool onAB = fabsl(s1) < EPS && onSegment(point, A, B);
    bool onBC = fabsl(s2) < EPS && onSegment(point, B, C);
    bool onCA = fabsl(s3) < EPS && onSegment(point, C, A);

    if(onAB || onBC || onCA) {
        return BORDER;
    }

    bool has_pos = (s1 > EPS || s2 > EPS || s3 > EPS);
    bool has_neg = (s1 < -EPS || s2 < -EPS || s3 < -EPS);

    if (has_pos && has_neg) {
        return OUT;
    }

    return IN;
}

void handler(){
    Triangle triangle;

    cout << "Введіть координати вершини A (x y): ";
    cin >> triangle.A.x >> triangle.A.y;

    cout << "Введіть координати вершини B (x y): ";
    cin >> triangle.B.x >> triangle.B.y;

    cout << "Введіть координати вершини C (x y): ";
    cin >> triangle.C.x >> triangle.C.y;

    if(triangle.area() < EPS){
        cout << "Трикутник вироджений" << endl;
    }
    else {
        cout << "Трикутник не вироджений" << endl;
    }

    int n;
    cout << "Скільки точок перевірити? ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        Point p;
        cout << "Точка " << i << " (x y): ";
        cin >> p.x >> p.y;

        int result = triangle.contains(p);
        cout << "За методом векторного добутку: ";
        if(result == IN) cout << "Точка належить трикутнику\n";
        else if(result == BORDER) cout << "Точка належить границі трикутника\n";
        else cout << "Точка не належить трикутнику\n";

        result = triangle.containsByArea(p);
        cout << "За методом площ: ";
        if(result == IN) cout << "Точка належить трикутнику\n";
        else if(result == BORDER) cout << "Точка належить границі трикутника\n";
        else cout << "Точка не належить трикутнику\n";

        cout << endl;
    }
}