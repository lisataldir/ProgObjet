# Object oriented programming : Transport equation simulation

## Sequential results

To obtain the plot in the Resultats file, follow these steps:

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

Note : './Main.exe' runs by default './Main.exe 0 2 0.1 0 10 0.1 uniform 1', but the user can choose different values.

## Parallel results

To obtain measure of performance, follow these steps:

First, in function void print(int iter) of 'Variable.cpp' file, replace

std::for_each(std::execution::seq, u.begin(),u.end(),[&](auto current_element) {
      ofs << current_element << "\n";
}); 

by :

std::for_each(std::execution::par, u.begin(),u.end(),[&](auto current_element) {
      ofs << current_element << "\n";
}); 

Same in 'Equation.h', replace std::execution::seq par std::execution::par inside compute_initial_condition() and compute_exact_solution().
Then do :

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
