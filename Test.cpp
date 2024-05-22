#include "gtest/gtest.h"
#include "Problem.h"
#include "Variable.h"
#include <tbb/tbb.h>

TEST(UnitaryTest,MeshTest){
  // construction et test d'une instance de UniformMesh
  IMesh* imesh = new UniformMesh{};
  UniformMesh mesh{};
  EXPECT_EQ(imesh->getInitialTime(), mesh.getInitialTime());
  EXPECT_EQ(imesh->getFinalTime(), mesh.getFinalTime());
  EXPECT_EQ(imesh->getStepTime(), mesh.getStepTime());
  EXPECT_EQ(imesh->getInitialSpace(), mesh.getInitialSpace());
  EXPECT_EQ(imesh->getFinalSpace(), mesh.getFinalSpace());
  EXPECT_EQ(imesh->getStepSpace(), mesh.getStepSpace());
  EXPECT_EQ(mesh.x_size(), int( (imesh->getFinalSpace() - imesh->getInitialSpace()) / imesh->getStepSpace() ) + 1);
}

TEST(UnitaryTest,ProblemTest){
  // construction et test d'une instance de Problem
  Equation equation{};
  IMesh* mesh = nullptr;
  Problem p{equation, mesh};
  p.solve(); 
}


TEST(MainFunctionTest,EquationTest){
  // construction et test d'une instance de Equation
  Equation equation{};
  IMesh* mesh = nullptr;
  Variable u_n{mesh, "u_n"};
  Variable u_np1{mesh, "u_np1"};
  equation.compute(mesh, u_n, u_np1);
}


