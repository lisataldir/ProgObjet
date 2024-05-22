#include "Variable.h"
#include <execution>
#include <tbb/tbb.h>

double& Variable::operator[](int i){
    return u[i];
}

Variable::Variable(IMesh* mesh, char const* name) : imesh(mesh), m_name(name){ 
    try {
        if (!imesh) throw std::invalid_argument("In Variable : IMesh cannot be nullptr.");
        u.resize(imesh->x_size());
    } catch (const std::exception& e) {
        std::cout << "Invalid argument : " << e.what() << std::endl;
    }   
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

    std::for_each(std::execution::seq, u.begin(),u.end(),[&](auto current_element) {
      ofs << current_element << "\n";
    });

    ofs.close();
}