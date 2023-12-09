#ifndef EQUATION_H_
#define EQUATION_H_

#include <math.h>
#include "Variable.h"

class Equation{
public :
    template <typename Fonction>
    Variable compute_initial_condition(Variable var, IMesh* imesh, Fonction f){

        if (imesh == nullptr) return var;

        double mu = imesh->getMu();
        double sigma = imesh->getSigma();
        int n = imesh->x_size();
        var.u.resize(n);

        int i = 0;
        std::for_each(var.u.begin(), var.u.end(), [&](auto& current_element){
            current_element = f(imesh->x_i(i));
            i++;
        });

        return var;
    }

    Variable compute(IMesh* imesh, Variable u_n, Variable u_np1);

    template <typename Fonction>
    Variable compute_exact_solution(IMesh* imesh, double t, Fonction f){
        Variable u_ref{"u_ref_"};
        if (imesh == nullptr) return u_ref;

        int n = imesh->x_size();
        double mu = imesh->getMu();
        double sigma = imesh->getSigma();
        double a = imesh->getA();

        u_ref.u.resize(n);

        int i = 0;
        std::for_each(u_ref.u.begin(), u_ref.u.end(), [&](auto& current_element){
            current_element = f(imesh->x_i(i) - a*t);
            i++;
        });

        return u_ref;
    }

    template<typename Schema>
    Variable compute_for_scheme(double t,IMesh* imesh, Variable u_n, Variable u_np1){
        return Schema::update(u_n, u_np1, t, imesh);
    }
};

#endif