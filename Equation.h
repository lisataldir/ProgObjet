#ifndef EQUATION_H_
#define EQUATION_H_

#include "IMesh.h"
#include "Variable.h"
#include <math.h>
#include <execution>
#include <tbb/tbb.h>
#include <concepts>

template <typename S>
concept Schema = requires (S s, Variable& u_n, Variable& u_np1, double t, IMesh* imesh) {
    {s.update(u_n, u_np1, t, imesh) } -> std::same_as<Variable>;
};

template<typename F>
concept Fonction = requires (F fonction, double x){ fonction(x); };


class Equation{
private:
    double a;
public:
    Variable compute(IMesh* imesh, Variable& u_n, Variable& u_np1);

    template <Fonction F>
    Variable compute_initial_condition(Variable& var, IMesh* imesh, F f){

        try {
            if (!imesh) throw std::invalid_argument("In Equation::compute_initial_condition : IMesh cannot be nullptr.");

            double xmin = imesh->getInitialSpace();
            double xmax = imesh->getFinalSpace();
            double dx = imesh->getStepSpace();
            double mu = (xmax-xmin)/2;
            double sigma = 10*dx;

            int i = 0;
            // Ici mettre std::execution::seq pour exécution séquentielle et std::execution::par pour exécution parallèle
            std::for_each(std::execution::seq, var.u.begin(), var.u.end(), [&](auto& current_element){
                current_element = f(imesh->x_i(i));
                i++;
            });
        } catch (const std::exception& e) {
            std::cout << "Invalid argument : " << e.what() << std::endl;
        }
        return var;
    }

    template <Schema schema>
    Variable compute_for_scheme(double t,IMesh* imesh, Variable& u_n, Variable& u_np1){
        return schema::update(u_n, u_np1, t, imesh);
    }


    template <Fonction F>
    Variable compute_exact_solution(Variable& u_ref, IMesh* imesh, double t, F f){
        try {
            if (!imesh) throw std::invalid_argument("In Equation::compute_initial_condition : IMesh cannot be nullptr.");
            int n = imesh->x_size();
            double xmin = imesh->getInitialSpace();
            double xmax = imesh->getFinalSpace();
            double dx = imesh->getStepSpace();
            double dt = imesh->getStepTime();
            double mu = (xmax-xmin)/2;
            double sigma = 10*dx;
            double a = 0.5*dx/dt;
   
            int i = 0;
            // Ici mettre std::execution::seq pour exécution séquentielle et std::execution::par pour exécution parallèle
            std::for_each(std::execution::seq, u_ref.u.begin(), u_ref.u.end(), [&](auto& current_element){
                current_element = f(imesh->x_i(i) - a*t);
                i++;
            });
        } catch (const std::exception& e){
            std::cout << "Invalid argument : " << e.what() << std::endl;
        }
        return u_ref;
    }
    
};

#endif