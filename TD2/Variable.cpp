#include "Variable.h"

double& Variable::operator[](int i){
    return u[i];
}

void Variable::print(int iter){

    const char* extension = ".dat";
    char fichier[30];
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
        //std::cout << "-- u_n[" << i << "] = " << u[i] << std::endl;
    }

    ofs.close();
}