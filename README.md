# Programmation orientée object : Simulation équation de transport 

## Résultats séquentiel

Pour obtenir le plot dans le fichier Resultats, suivre les étapes suivantes:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./Main.exe
$ cd ..
$ bash script.sh
# Tranfert de u_n_0.dat, u_np1_20.dat, u_ref_20.dat u_np1_2nd_order_20.dat dans Resultats
# Suppression des autres fichiers .dat 
$ cd Resultats
$ gnuplot plot-resultat.gp
```

Remarque : ./Main.exe exécute par défaut ./Main.exe 0 2 0.1 0 10 0.1 uniform 1, mais l'utilisateur peut choisir d'autres valeurs.

# Résultats parallèle

Pour obtenir les mesures de performances, suivre les étapes suivantes:

Tout d'abord, dans la fonction void print(int iter) du fichier Variable.cpp, remplacer 

std::for_each(std::execution::seq, u.begin(),u.end(),[&](auto current_element) {
      ofs << current_element << "\n";
}); 

par :

std::for_each(std::execution::par, u.begin(),u.end(),[&](auto current_element) {
      ofs << current_element << "\n";
}); 

De même dans le fichier Equation.h, remplacer std::execution::seq par std::execution::par dans les fonctions compute_initial_condition et compute_exact_solution.
Puis dans un terminal faire :

```bash
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make
$ ./Main.exe 0 10 0.1 0 10 0.00001 uniform 0
Compute with UniformMesh
--- Solve problem with Upwind ---
Temps d'exécution boucle : 2338 ms
--- End problem ---
--- Solve problem with Lax-Wendroff ---
Temps d'exécution boucle : 1824 ms
--- End problem ---
Temps d'exécution total sequentiel: 4309 ms
          ---------------- 
--- Solve problem ---
Temps d'exécution exact_solution : 1524 ms
Temps d'exécution Lax-Wendroff : 2657 ms
Temps d'exécution Upwind : 3162 ms
--- End problem ---
Temps d'exécution total parallele (avec thread): 3218 ms
          ---------------- 
--- Solve problem ---
Temps d'exécution exact_solution : 2093 ms
Temps d'exécution Upwind : 2841 ms
Temps d'exécution Lax-Wendroff : 3009 ms
--- End problem ---
Temps d'exécution total parallele (avec async): 3033 ms
```