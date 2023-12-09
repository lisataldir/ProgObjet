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

    std::for_each(u.begin(),u.end(),[&](auto current_element) {
      ofs << current_element << "\n";
    });


    ofs.close();
}