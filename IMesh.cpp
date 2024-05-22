#include "IMesh.h"

double IMesh::getInitialTime() const {return 0;}
double IMesh::getFinalTime() const {return 0;}
double IMesh::getStepTime() const {return 0;}
double IMesh::getInitialSpace() const {return 0;}
double IMesh::getFinalSpace() const {return 0;}
double IMesh::getStepSpace() const {return 0;}
int IMesh::x_size() const {return 0;}
double IMesh::x_i(int i) {return 0;}


UniformMesh::UniformMesh(): t_init(0), t_final(2), dt(0.1), x_min(0), x_max(10), dx(0.1) {}
UniformMesh::UniformMesh(double InitialTime, double FinalTime, double StepTime, double InitialSpace, double FinalSpace, double StepSpace)
    : t_init(InitialTime), t_final(FinalTime), dt(StepTime), x_min(InitialSpace), x_max(FinalSpace), dx(StepSpace) {}

double UniformMesh::getInitialTime() const {return t_init;}
double UniformMesh::getFinalTime() const {return t_final;}
double UniformMesh::getStepTime() const {return dt;}
double UniformMesh::getInitialSpace() const {return x_min;}
double UniformMesh::getFinalSpace() const {return x_max;}
double UniformMesh::getStepSpace() const {return dx;}
int UniformMesh::x_size() const { return int((x_max-x_min)/dx) + 1;}
double UniformMesh::x_i(int i){ return x_min + dx*i;}


double NonUniformMesh::getInitialTime() const {return 0;}
double NonUniformMesh::getFinalTime() const {return 0;}
double NonUniformMesh::getStepTime() const {return 0;}
double NonUniformMesh::getInitialSpace() const {return 0;}
double NonUniformMesh::getFinalSpace() const {return 0;}
double NonUniformMesh::getStepSpace() const {return 0;}
int NonUniformMesh::x_size() const {return 0;}
double NonUniformMesh::x_i(int i) {return 0;}