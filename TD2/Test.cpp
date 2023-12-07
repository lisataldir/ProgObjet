#include "gtest/gtest.h"
#include "Problem.h"

TEST(UnitaryTest,MeshTest){
  // construction et test d'une instance de UniformMesh
  UniformMesh mesh(0, 2, 0.1, 0, 10, 0.1);
}

TEST(UnitaryTest,ProblemTest){
  // construction et test d'une instance de Problem
  Problem p{};
  p.imesh = nullptr;
  p.solve_with_print();
}

TEST(MainFunctionTest,EquationTest){
  // construction et test d'une instance de Equation
  Equation eq{};
  Variable u_n{};
  Variable u_np1{};
  Variable tcmp = eq.compute(nullptr, u_n, u_np1);
}

TEST(UnitaryTest,VariableTest){
  // construction et test d'une instance de Variable
  Variable var{};
}