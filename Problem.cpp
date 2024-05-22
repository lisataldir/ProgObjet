#include "Problem.h"
#include "Variable.h"
#include <iostream>
#include <utility>
#include <thread>
#include <future>
#include <exception>
#include "Equation.h"
#include "Timer.h"

Problem::Problem(Equation eq,  IMesh* mesh) : equation(eq),imesh(mesh){}

void Problem::solve(){
    try {
        if (!imesh) {
            throw std::invalid_argument("In Problem::solve : IMesh cannot be nullptr.");
        }

        Variable u_n{imesh, "u_n_"};
        Variable u_np1{imesh, "u_np1_"};
        Variable u_ref{imesh, "u_ref_"};

        std::cout << "--- Solve problem with Upwind ---" << std::endl;
        double t0 = imesh->getInitialTime();
        double tfinal = imesh->getFinalTime();
        double dt = imesh->getStepTime();
        double xmin = imesh->getInitialSpace();
        double xmax = imesh->getFinalSpace();
        double dx = imesh->getStepSpace();

        double sigma = 10*dx;
        double mu = (xmax-xmin)/2;
        auto gauss = [&sigma, &mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};
        u_n = equation.compute_initial_condition(u_n, imesh, gauss);
        u_n.print(0);

        int iter = 0;
        for (double t = t0; t < tfinal + dt; t += dt) {
            std::cout << "--- Compute equation at time : " << t << " ---" << std::endl;
            u_ref = equation.compute_exact_solution(u_ref, imesh, t, gauss);
            u_n = equation.compute_for_scheme<Upwind>(t,imesh,u_n,u_np1);
            u_n.print(iter);
            u_ref.print(iter);
            iter++;
        }

        std::cout << "--- End problem ---" << std::endl;

        // Lax-Wendroff solution
        std::cout << "--- Solve problem with Lax-Wendroff ---" << std::endl;
        Variable u_n_2nd_order{imesh, "u_n_2nd_order_"};
        Variable u_np1_2nd_order{imesh, "u_np1_2nd_order_"};

        u_n_2nd_order = equation.compute_initial_condition(u_n_2nd_order, imesh, gauss);
   
        iter = 0;
        for (double t = t0; t < tfinal + dt; t += dt){
            std::cout << "--- Compute equation at time : " << t << " ---" << std::endl;
            u_n_2nd_order = equation.compute_for_scheme<LaxWendroff>(t, imesh, u_n_2nd_order, u_np1_2nd_order);
            u_n_2nd_order.print(iter);
            iter++;
        }
        std::cout << "--- End problem ---" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Invalid argument : " << e.what() << std::endl;
    }
}

// Séquentiel
void Problem::solve_without_print(){
    try {
        if (!imesh) {
            throw std::invalid_argument("In Problem::solve : IMesh cannot be nullptr.");
        }

        Variable u_n{imesh, "u_n_"};
        Variable u_np1{imesh, "u_np1_"};
        Variable u_ref{imesh, "u_ref_"};

        std::cout << "--- Solve problem with Upwind ---" << std::endl;
        double t0 = imesh->getInitialTime();
        double tfinal = imesh->getFinalTime();
        double dt = imesh->getStepTime();
        double xmin = imesh->getInitialSpace();
        double xmax = imesh->getFinalSpace();
        double dx = imesh->getStepSpace();

        double sigma = 10*dx;
        double mu = (xmax-xmin)/2;
        auto gauss = [&sigma, &mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};
        u_n = equation.compute_initial_condition(u_n, imesh, gauss);
    
        Timer t_boucle;
        t_boucle.start();
        for (double t = t0; t < tfinal + dt; t += dt) {
            u_ref = equation.compute_exact_solution(u_ref, imesh, t, gauss);
            u_n = equation.compute_for_scheme<Upwind>(t,imesh,u_n,u_np1);
        }
        t_boucle.stop();
        std::cout << "Temps d'exécution boucle : ";
        t_boucle.print();

        std::cout << "--- End problem ---" << std::endl;

        // Lax-Wendroff solution
        std::cout << "--- Solve problem with Lax-Wendroff ---" << std::endl;
        Variable u_n_2nd_order{imesh, "u_n_2nd_order_"};
        Variable u_np1_2nd_order{imesh, "u_np1_2nd_order_"};

        u_n_2nd_order = equation.compute_initial_condition(u_n_2nd_order, imesh, gauss);
   
        Timer t_boucle2;
        t_boucle2.start();
        for (double t = t0; t < tfinal + dt; t += dt){
            u_n_2nd_order = equation.compute_for_scheme<LaxWendroff>(t, imesh, u_n_2nd_order, u_np1_2nd_order);
        }
        t_boucle2.stop();
        std::cout << "Temps d'exécution boucle : ";
        t_boucle2.print();

        std::cout << "--- End problem ---" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Invalid argument : " << e.what() << std::endl;
    }

}

// Parallèle
void Problem::solve_parallel(){
   try {
        if (!imesh) {
            throw std::invalid_argument("In Problem::solve : IMesh cannot be nullptr.");
        }

        Variable u_n{imesh, "u_n_"};
        Variable u_np1{imesh, "u_np1_"};
        Variable u_ref{imesh, "u_ref_"};
        Variable u_n_2nd_order{imesh, "u_n_2nd_order_"};
        Variable u_np1_2nd_order{imesh, "u_np1_2nd_order_"};

        std::cout << "--- Solve problem ---" << std::endl;
        double t0 = imesh->getInitialTime();
        double tfinal = imesh->getFinalTime();
        double dt = imesh->getStepTime();
        double xmin = imesh->getInitialSpace();
        double xmax = imesh->getFinalSpace();
        double dx = imesh->getStepSpace();

        double sigma = 10*dx;
        double mu = (xmax-xmin)/2;
        auto gauss = [&sigma, &mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};
    
        std::thread first_thread([&](){

            Timer t_boucle;

            t_boucle.start();
            for (double t = t0; t < tfinal + dt; t += dt){
                u_ref = equation.compute_exact_solution(u_ref, imesh, t, gauss);
            }
            t_boucle.stop();

            std::cout << "Temps d'exécution exact_solution : ";
            t_boucle.print();

        });

        std::thread second_thread([&](){

             u_n = equation.compute_initial_condition(u_n, imesh, gauss);
    
            Timer t_boucle;
            t_boucle.start();
            for (double t = t0; t < tfinal + dt; t += dt) {
                u_ref = equation.compute_exact_solution(u_ref, imesh, t, gauss);
                u_n = equation.compute_for_scheme<Upwind>(t,imesh,u_n,u_np1);
            }
            t_boucle.stop();
            std::cout << "Temps d'exécution Upwind : ";
            t_boucle.print();

        });

        std::thread third_thread([&](){

            u_n_2nd_order = equation.compute_initial_condition(u_n_2nd_order, imesh, gauss);
   
            Timer t_boucle;
            t_boucle.start();
            for (double t = t0; t < tfinal + dt; t += dt){
                u_n_2nd_order = equation.compute_for_scheme<LaxWendroff>(t, imesh, u_n_2nd_order, u_np1_2nd_order);
            }
            t_boucle.stop();
            std::cout << "Temps d'exécution Lax-Wendroff : ";
            t_boucle.print();

        });

        first_thread.join();
        second_thread.join();
        third_thread.join();
      
        std::cout << "--- End problem ---" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Invalid argument : " << e.what() << std::endl;
    }
}

void Problem::solve_with_task(){
   try {
        if (!imesh) {
            throw std::invalid_argument("In Problem::solve : IMesh cannot be nullptr.");
        }

        Variable u_n{imesh, "u_n_"};
        Variable u_np1{imesh, "u_np1_"};
        Variable u_ref{imesh, "u_ref_"};
        Variable u_n_2nd_order{imesh, "u_n_2nd_order_"};
        Variable u_np1_2nd_order{imesh, "u_np1_2nd_order_"};

        std::cout << "--- Solve problem ---" << std::endl;
        double t0 = imesh->getInitialTime();
        double tfinal = imesh->getFinalTime();
        double dt = imesh->getStepTime();
        double xmin = imesh->getInitialSpace();
        double xmax = imesh->getFinalSpace();
        double dx = imesh->getStepSpace();

        double sigma = 10*dx;
        double mu = (xmax-xmin)/2;
        auto gauss = [&sigma, &mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};

        std::future first_task = std::async(std::launch::async,[&](){
            Timer t_boucle;

            t_boucle.start();
            for (double t = t0; t < tfinal + dt; t += dt){
                u_ref = equation.compute_exact_solution(u_ref, imesh, t, gauss);
            }
            t_boucle.stop();

            std::cout << "Temps d'exécution exact_solution : ";
            t_boucle.print();
        });

        std::future second_task = std::async(std::launch::async,[&](){
             u_n = equation.compute_initial_condition(u_n, imesh, gauss);
    
            Timer t_boucle;
            t_boucle.start();
            for (double t = t0; t < tfinal + dt; t += dt) {
                u_ref = equation.compute_exact_solution(u_ref, imesh, t, gauss);
                u_n = equation.compute_for_scheme<Upwind>(t,imesh,u_n,u_np1);
            }
            t_boucle.stop();
            std::cout << "Temps d'exécution Upwind : ";
            t_boucle.print();
        });

        std::future third_task = std::async(std::launch::async,[&](){
             u_n_2nd_order = equation.compute_initial_condition(u_n_2nd_order, imesh, gauss);
   
            Timer t_boucle;
            t_boucle.start();
            for (double t = t0; t < tfinal + dt; t += dt){
                u_n_2nd_order = equation.compute_for_scheme<LaxWendroff>(t, imesh, u_n_2nd_order, u_np1_2nd_order);
            }
            t_boucle.stop();
            std::cout << "Temps d'exécution Lax-Wendroff : ";
            t_boucle.print();
        });

        first_task.wait();
        second_task.wait(); 
        third_task.wait();
        std::cout << "--- End problem ---" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Invalid argument : " << e.what() << std::endl;
    }
}