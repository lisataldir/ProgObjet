#include "Problem.h"
#include "Timer.h"
#include <exception>
#include <iostream>
#include <cstring>
#include <map>

// Soit l'utilisateur entre des valeurs et un type de maillage, soit les valeurs, le maillage et le mode (séquentiel, parallèle) 
// choisis par défaut sont utilisés.

int main(int argc, char** argv){  

    if (argc < 9){
        Equation eq{};
        IMesh* imesh = new UniformMesh{};
        Problem p{eq, imesh};
        p.solve();
    
    } else {
        double t_init = std::atof(argv[1]);
        double t_final = std::atof(argv[2]);
        double dt = std::atof(argv[3]);
        double x_min = std::atof(argv[4]);
        double x_max = std::atof(argv[5]);
        double dx = std::atof(argv[6]);

        enum class Maillage { Uniform, NonUniform };
        std::map<std::string, Maillage> maillageMap = {{"uniform", Maillage::Uniform}, {"non-uniform", Maillage::NonUniform}};
        Maillage resolution_method = maillageMap[argv[7]];
        IMesh* imesh;
        switch (resolution_method) {
            case Maillage::Uniform:
                std::cout << "Compute with UniformMesh" << std::endl;
                imesh = new UniformMesh{t_init, t_final, dt, x_min, x_max, dx};
                break;
            case Maillage::NonUniform:
                std::cout << "Compute with NonUniformMesh" << std::endl;
                imesh = new NonUniformMesh{};
                break;
        }

        int cond = std::stof(argv[8]);

        if(cond){
            Equation eq{};
            Problem p{eq, imesh};
            p.solve();
        } else {
            // Mesures de performances :
            Equation eq{};
            Problem p{eq, imesh};
        
            Timer t_total_seq, t_total_para, t_total_async;

            t_total_seq.start();
            p.solve_without_print();
            t_total_seq.stop();
            std::cout << "Temps d'exécution total sequentiel: ";
            t_total_seq.print();

            std::cout << "          ---------------- " << std::endl;

            t_total_para.start();
            p.solve_parallel();
            t_total_para.stop();
            std::cout << "Temps d'exécution total parallele (avec thread): ";
            t_total_para.print();

            std::cout << "          ---------------- " << std::endl;

            t_total_async.start();
            p.solve_with_task();
            t_total_async.stop();
            std::cout << "Temps d'exécution total parallele (avec async): ";
            t_total_async.print();
        }

    }   
    return 0;
}