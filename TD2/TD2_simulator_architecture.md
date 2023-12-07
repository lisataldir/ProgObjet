# TD 2 à 5 simulation équation de transport : résolution d'équation d'advection linéaire

Contexte et objectifs du TD : voir [Intro TD simulation équation d'advection](TD2-5_intro.md)

# TD 2 Mise en place de l'infrastructure

## 2.1 Structure du simulateur

Le but de cette première partie est de créer le programme principal et l'architecture objet de notre simulateur.

Le simulateur sera constitué de deux classes principales :

- Une classe `Problem` permettant de résoudre nos équations,
- une classe `Equation`, contenant les paramètres de notre équation à résoudre.

Vous créerez des fichiers .cpp et .h pour chacune de ces classes.
La classe `Problem` contiendra un membre de type `Equation`.

Le programme principal se limitera pour l'instant à créer une instance de la classe `Problem` et à appeler sa méthode `solve`. Cette méthode lancera la méthode `compute` de l'`Equation` contenue dans le `Problem`.

Le programme sera configuré par un projet CMake, voir partie 2.3.

## 2.2 Discrétisation en espace et en temps

Nous allons maintenant créer l'outillage pour la discrétisation en espace et en temps. Afin de permettre de la souplesse dans le choix de cette discrétisation (uniforme ou non par exemple), nous allons avoir recours au polymorphisme. Nous utiliserons une classe de base `IMesh` qui proposera des méthodes pour accéder aux informations de discrétisations nécessaires :

- temps initial, final et pas de temps ;
- position initiale, position finale et pas d'espace.

Vous créerez cette classe de base ainsi qu'une classe dérivée `UniformMesh` qui implémentera les méthodes de la classe parent pour un pas de temps et d'espace constant. Vous donnerez à la construction de cette classe les valeurs `t_ini`, `t_final`, `dt`, `x_min`, `x_max`, `dx`. On choisira les valeurs :

- `t_ini` = 0
- `t_final` = 1
- `dt` = 0.5
- `x_min` = 0
- `x_max` = 5
- `dx` = 2

Une fois ces deux classes crées, vous stockerez un pointeur de `IMesh` dans `Problem` et vous l'utiliserez pour mettre au point une boucle en temps dans la méthode `solve` qui appellera la méthode `compute` d'`Equation` à chaque pas de temps. Pour l'instant, la méthode `solve` se contentera d'afficher le temps courant et de boucler sur tous les points d'espace. L'exécution du programme devrait donc donner l'affichage suivant :

```shell
--- Solve problem ---
--- compute equation at time : 0 ---
-- at x_i = 0
-- at x_i = 2
-- at x_i = 4
--- compute equation at time : 0.5 ---
-- at x_i = 0
-- at x_i = 2
-- at x_i = 4
```

Pour créer notre `Problem` dans le programme principal, nous lui passerons à la construction une instance de la classe équation et un pointeur de `UniformMesh` qu'il stockera dans son pointeur de `IMesh`. Il sera responsable de la mémoire de ce pointeur, ce sera donc à lui d'appeler le `delete`. Vous veillerez à ce que le pointeur ne puisse pas être nul, en bloquant les constructions ou affectations par copie.

## 2.3 Compiler avec CMake

La compilation du projet utilisera un projet CMake qui créera une cible de type exécutable qui compilera votre programme principal en utilisant toutes les classes que vous aurez définies. Pour compiler votre projet depuis vos sources, il faudra simplement exécuter les commandes suivantes :

```shell
mkdir build
cd build
cmake .. 
make
```

Vous référer au TD1 pour cette partie.

## 2.4 Tester avec CTest

Grâce à la commande `add_test(test_name target_name)`, vous ajouterez votre exécutable à la base de test. Vous n'oublierez pas la commande `enable_testing` avant d'ajouter `add_test` dans le CMakeLists.txt.

Vous pouvez maintenant lancer votre exécutable via la commande `ctest` :

```shell
$ ctest
    Start 1: structure_test
1/1 Test #1: structure_test ...................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1
```

### Bonus : créez des tests unitaires avec GTest

Vous avez créé un test d'intégration (qui utilise tous les éléments de votre projet), il est également nécessaire de créer des test unitaires pour chaque brique (classe) du projet. GTest est un bon outil pour les réaliser.

- Vous créerez un nouvel exécutable de test, utilisant GTest (revoir TD1), qui vous permettra, à l'aide de la macro `TEST`, de tester vos différentes classes.
- Grâce à la commande CMake `gtest_discover_tests`, prenant en argument le nom de la target exécutable que vous venez de créer, ces tests seront lancés également via la commande `ctest`.

```c++
TEST(UnitaryTest,MeshTest){
  // construction et test d'une instance de UniformMesh
}

TEST(UnitaryTest,ProblemTest){
  // construction et test d'une instance de Problem
}

TEST(MainFunctionTest,EquationTest){
  // construction et test d'une instance de Equation
}
...
```

Pour le test de `Problem` vous pourrez tester le comportement de la classe si on lui fournit un pointeur nul pour le maillage. L'appel de `Problem::solve` ne devra pas planter. Vous pourrez de la même façon tester pour `Equation` le comportement lorsque la méthode `Equation::solve` est appelée avec un `IMesh*=nullptr` et faire en sorte que ce test passe.

## 2.5 Bonus : choix dynamique de la configuration de calcul

- Pour l'instant la configuration du problème était réalisée statiquement dans votre programme, à la création de la classe `UniformMesh`. Vous allez maintenant permettre à l'utilisateur de préciser les paramètres de temps (initial, final, pas de temps) et d'espace (`x_min`, `x_max` et pas d'espace) dans la ligne de commande. Votre programme prendra donc en paramètres six arguments, que vous récupérerez grâce aux arguments `(int argc, char** argv)` de la fonction `main`. Vous pourrez utiliser `std::stof` pour convertir une chaîne de caractère en flottant.  
- Finalement afin de pouvoir choisir le type de maillage au runtime, vous prendrez en argument d'entrée supplémentaire le type de maillage (via une chaîne de caractère : "uniform" ou "non-uniform"). Vous utiliserez ensuite une fabrique, qui en prenant cette argument d'entrée sera capable de créer l'instance souhaitée de la classe `Problem`. Cette fabrique utilisera une `enum class` définissant les types de maillage possibles ```Uniform, NonUniform```. Pour pouvoir prévoir le cas ```NonUniform``` vous créerez une classe ```NonUniformMesh``` qui héritera de ```IMesh``` mais avec des méthodes vides. Votre fabrique assurera, grâce à un dictionnaire la conversion entre la chaîne de caractère donnée en entrée et l'enum.

Le livrable de ce TD doit être configurable via CMake, compilable et avoir une base de tests ok.
