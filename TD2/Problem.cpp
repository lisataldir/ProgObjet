#include "Problem.h"

void Problem::solve_with_print(){

    if (imesh == nullptr) return;

    // Upwind solution
    Variable u_n{"u_n_"};
    Variable u_np1{"u_np1_"};
    Variable u_ref {};

    std::cout << "--- Solve problem ---" << std::endl;
    double t0 = imesh->getInitialTime();
    double tfinal = imesh->getFinalTime();
    double dt = imesh->getStepTime();

    double sigma = imesh->getSigma();
    double mu = imesh->getMu();
    auto gauss = [sigma, mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};

    u_n = equation.compute_initial_condition_stl(u_n, imesh, gauss);
    u_n.print(0);

    int iter=0;
    for (double t = t0; t < tfinal + dt; t += dt){

        std::cout << "--- Compute equation at time : " << t << " ---" << std::endl;
        u_ref = equation.compute_exact_solution_stl(imesh, t, gauss);
        u_n = equation.compute_for_scheme<Upwind>(t,imesh,u_n,u_np1);
        u_n.print(iter);
        u_ref.print(iter);
        iter++;

    }

    std::cout << "--- End problem ---" << std::endl;

    // Lax-Wendroff solution

    Variable u_n_2nd_order{"u_n_2nd_order_"};
    Variable u_np1_2nd_order{"u_np1_2nd_order_"};

    u_n_2nd_order = equation.compute_initial_condition_stl(u_n, imesh, gauss);
    u_n_2nd_order.print(0);

    iter=0;
    for (double t = t0; t < tfinal + dt; t += dt){

        std::cout << "--- Compute equation at time : " << t << " ---" << std::endl;
        u_n_2nd_order = equation.compute_for_scheme<LaxWendroff>(t, imesh, u_n_2nd_order, u_np1_2nd_order);
        u_n_2nd_order.print(iter);
        iter++;
    }

}

void Problem::solve_without_print(){

    if (imesh == nullptr) return;

    Variable u_n{"u_n_"};
    Variable u_np1{"u_np1_"};
    Variable u_ref {};

    std::cout << "--- Solve problem ---" << std::endl;
    double t0 = imesh->getInitialTime();
    double tfinal = imesh->getFinalTime();
    double dt = imesh->getStepTime();

    double sigma = imesh->getSigma();
    double mu = imesh->getMu();
    auto gauss = [sigma, mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};

    u_n = equation.compute_initial_condition(u_n, imesh, gauss);
  
    Timer t_boucle;
    t_boucle.start();
    for (double t = t0; t < tfinal + dt; t += dt){

        u_ref = equation.compute_exact_solution(imesh, t, gauss);
        u_n = equation.compute(imesh, u_n, u_np1);

    }

    t_boucle.stop();
    std::cout << "Temps d'exécution boucle : ";
    t_boucle.print();

    std::cout << "--- End problem ---" << std::endl;

}

void Problem::solve_parallel(){
    if (imesh == nullptr) return;

    Variable u_n{"u_n_"};
    Variable u_ref {};
    Variable u_np1{"u_np1_"};

    double t0 = imesh->getInitialTime();
    double tfinal = imesh->getFinalTime();
    double dt = imesh->getStepTime();

    double sigma = imesh->getSigma();
    double mu = imesh->getMu();
    auto gauss = [sigma, mu](double x){return exp( - pow(x-mu, 2)/(2*pow(sigma, 2)) ) / (sigma*sqrt(2*M_PI));};

    std::cout << "--- Solve problem ---" << std::endl;
    u_n = equation.compute_initial_condition(u_n, imesh, gauss);

    std::thread first_thread([&](){

        Timer t_boucle;

        t_boucle.start();
        for (double t = t0; t < tfinal + dt; t += dt){
            u_ref = equation.compute_exact_solution(imesh, t, gauss);
        }
        t_boucle.stop();

        std::cout << "Temps d'exécution exact_solution : ";
        t_boucle.print();

    });

    std::thread second_thread([&](){

        Timer t_boucle;

        t_boucle.start();
        for (double t = t0; t < tfinal + dt; t += dt){
            u_n = equation.compute(imesh, u_n, u_np1);
        }
        t_boucle.stop();

        std::cout << "Temps d'exécution appr_solution : ";
        t_boucle.print();

    });

    first_thread.join();
    second_thread.join();

    std::cout << "--- End problem ---" << std::endl;

}