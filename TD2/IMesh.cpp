#include "IMesh.h"

double IMesh::getInitialTime() const {return 0;}
double IMesh::getFinalTime() const {return 0;}
double IMesh::getStepTime() const {return 0;}
double IMesh::getInitialSpace() const {return 0;}
double IMesh::getFinalSpace() const {return 0;}
double IMesh::getStepSpace() const {return 0;}
int IMesh::x_size() const {return 0;}
double IMesh::x_i(int i) {return 0;}
double IMesh::getMu() const {return 0;}
double IMesh::getSigma() const {return 0;}
double IMesh:: getA() const {return 0;}

UniformMesh::UniformMesh(double t_init, double t_final, double dt, double x_min, double x_max, double dx)
    : t_init(t_init), t_final(t_final), dt(dt), x_min(x_min), x_max(x_max), dx(dx) {}

double UniformMesh::getInitialTime() const {return t_init;}
double UniformMesh::getFinalTime() const {return t_final;}
double UniformMesh::getStepTime() const {return dt;}
double UniformMesh::getInitialSpace() const {return x_min;}
double UniformMesh::getFinalSpace() const {return x_max;}
double UniformMesh::getStepSpace() const {return dx;}

int UniformMesh::x_size() const {
    double x_max = getFinalSpace();
    double x_min = getInitialSpace();
    double dx = getStepSpace();
    return int((x_max-x_min)/dx) + 1;
}

double UniformMesh::x_i(int i){
    double x_min = getInitialSpace();
    double dx = getStepSpace();
    return x_min + dx*i;
}

double UniformMesh::getMu() const {return mu;}
double UniformMesh::getSigma() const  {return sigma;}
double UniformMesh::getA() const {return a;}