#ifndef DYHOTOMIA_CLASS_H
#define DYHOTOMIA_CLASS_H

class Dyhotomia_class {
private:
    double a;  
    double b;  
    double eps;

    double f(double x);
    double df(double x);

public:
    Dyhotomia_class(); 
    ~Dyhotomia_class();

    void setVolumes(double vol_a, double vol_b);
    void setTolerance(double vol_eps);          

    int count(double &x);       
    int countNewton(double &x); 
};

void handler();

#endif