#include "Problem.h"

int main(int argc, char ** argv){

    if (argc < 8){
        std::cout << "Usage : " << argv[0] << " [t_0], [t_final], [dt], [x_min], [x_max], [dx], [cond]" << std::endl;
        std::cout << "Mettre cond = 0 pour comparer Upwin et Lax-Wendroff et cond = 1 pour le test de performance" << std::endl;
        return 1;
    } 
        
    double t_init = std::stof(argv[1]);
    double t_final = std::stof(argv[2]);
    double dt = std::stof(argv[3]);
    double x_min = std::stof(argv[4]);
    double x_max = std::stof(argv[5]);
    double dx = std::stof(argv[6]);
    int cond = std::stof(argv[7]);

    Equation eq{};
    IMesh* imesh = new UniformMesh{t_init, t_final, dt, x_min, x_max, dx};

    Problem p{eq, imesh};

    // pour la comparaison entre Upwind et Lax-Wendroff
    if (cond){
        p.solve_with_print();
    } else {
        // pour le test de performance
        Timer t_total_seq, t_total_para;

        t_total_seq.start();
        p.solve_without_print();
        t_total_seq.stop();
        std::cout << "Temps d'exécution total sequentiel: ";
        t_total_seq.print();

        std::cout << "          ---------------- " << std::endl;

        t_total_para.start();
        p.solve_parallel();
        t_total_para.stop();
        std::cout << "Temps d'exécution total parallele: ";
        t_total_para.print();
    }

    return 0;
}