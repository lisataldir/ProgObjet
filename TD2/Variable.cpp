#include "Variable.h"

double& Variable::operator[](int i){
    return u[i];
}

void Variable::print(int iter){

    const char* extension = ".dat";
    char fichier[20];
    std::strcpy(fichier, m_name);
    char temp[15];  
    std::snprintf(temp, sizeof(temp), "%d", iter);
    std::strcat(fichier, temp);
    std::strcat(fichier, extension);

    std::ofstream ofs (fichier, std::ofstream::out);
    for (int i=0; i < u.size(); ++i){
        // stockage des données dans un fichier
        ofs << u[i] << "\n";
        // affichage
        std::cout << "-- u_n[" << i << "] = " << u[i] << std::endl;
    }

    ofs.close();
}

//  schéma décentré amont
Variable Upwind::update(Variable&& u_n, Variable&& u_np1, double t, IMesh* imesh){
    if (imesh == nullptr) return u_n;

    int n = imesh->x_size();
    u_np1.u.resize(n);
    u_np1[0] = u_n[0];

    for (int i = 1; i < n; ++i){
        u_np1[i] = u_n[i] - 0.5*(u_n[i] - u_n[i-1]);
    } 
    return u_np1;
}

// schéma centré
Variable LaxWendroff::update(Variable&& u_n, Variable&& u_np1, double t, IMesh* imesh){
    if (imesh == nullptr) return u_n;

    int n = imesh->x_size();
    u_np1.u.resize(n);
    u_np1[0] = u_n[0];

    double a = imesh->getA();
    double dt = imesh->getStepTime();
    double dx = imesh->getStepSpace();

    for (int i = 1; i < n - 1; ++i){
        u_np1[i] = u_n[i] - a*dt/(2*dx) *( u_n[i+1] - u_n[i-1]) + a*a*dt*dt/(2*dx*dx) * (u_n[i+1] - 2*u_n[i] + u_n[i-1]);
    } 

    u_np1[n-1]= u_n[n-1];

    return u_np1;
}