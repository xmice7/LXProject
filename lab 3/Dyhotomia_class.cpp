#include "Dyhotomia_class.h"
#include <iostream>
#include <cmath>

using namespace std;

Dyhotomia_class::Dyhotomia_class() {
    a = 0;
    b = 0;
    eps = 0.001;
}

Dyhotomia_class::~Dyhotomia_class() {}

double Dyhotomia_class::f(double x) {
    return 3 * x - 4 * log(x) - 5;
}

double Dyhotomia_class::df(double x) {
    double dx = 0.000001;
    return 3.0 - 4.0 / x;
}

void Dyhotomia_class::setVolumes(double vol_a, double vol_b) {
    a = vol_a;
    b = vol_b;
}

void Dyhotomia_class::setTolerance(double vol_eps) {
    eps = vol_eps;
}

int Dyhotomia_class::count(double &x) {
    double local_a = a;
    double local_b = b;
    double c;
    int max_iter = 1000;
    int iter = 0;


    if (f(local_a) * f(local_b) > 0) {
        cout << "Error: No root" << endl;
        return -1;
    }

    while (fabs(local_b - local_a) > eps && iter < max_iter) {
        c = (local_a + local_b) / 2.0; 
        
        if (fabs(f(c)) < eps) {
            x = c;
            return 0;
        }
        
        if (f(local_a) * f(c) < 0) { 
            local_b = c;
        } else {
            local_a = c;
        }
        iter++;
    }

    x = (local_a + local_b) / 2.0; 
    return 0; 
}

int Dyhotomia_class::countNewton(double &x) {
    double x_curr = (a + b) / 2.0; 
    double x_next;
    int max_iter = 1000;
    int iter = 0;

    do {
        double derivative = df(x_curr);
        if (fabs(derivative) < 1e-9) {
            cout << "Error: Derivative near zero" << endl;
            return -1; // Зупинка
        }
        
        x_next = x_curr - f(x_curr) / derivative; 

        if (fabs(x_next - x_curr) < eps) { 
            x = x_next;
            return 0;
        }
        x_curr = x_next;
        iter++;
    } while (iter < max_iter);

    cout << "Error: Iteration limit" << endl;
    return -1;
}

void handler() {
    Dyhotomia_class *dyh = new Dyhotomia_class();

    double a, b, eps, root;

    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "eps: ";
    cin >> eps;

    dyh->setVolumes(a, b);
    dyh->setTolerance(eps);

    if (dyh->count(root) == 0) {
        cout << "Dyhotomia root: " << root << endl;
    }

    if (dyh->countNewton(root) == 0) {
        cout << "Newton root: " << root << endl;
    }

    delete dyh;
}