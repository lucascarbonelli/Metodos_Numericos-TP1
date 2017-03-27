#include <iostream>
#include "Eigen/Dense"
#include "eliminacion_gauss.cpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main()
{
// Test 2x2
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);

  VectorXd b(2);
  b(0) = 5;
  b(1) = 13.5;
  std::cout << "matriz de 2x2:" << std::endl << m << std::endl << std::endl << "b:" << std::endl << b << std::endl << std::endl;

  eliminacionGaussiana(m, b);

/*
  triangularSuperior(m, b);

  std::cout << m << std::endl << std::endl << b << std::endl;

  triangularInferior(m, b);
*/
  std::cout << "matriz de 2x2 resolucion:" << std::endl << m << std::endl << std::endl << "b:" << std::endl << b << std::endl << std::endl;

// Test 3x3
  MatrixXd m3(3,3);
  m3(0,0) = 3;
  m3(1,0) = 0;
  m3(2,0) = 7;
  m3(0,1) = -1;
  m3(1,1) = 2;
  m3(2,1) = 1;
  m3(0,2) = 1;
  m3(1,2) = 2;
  m3(2,2) = 1;

  VectorXd b3(3);
  b3(0) = 4;
  b3(1) = 10;
  b3(2) = 12;

  std::cout << "matriz de 3x3:" << std::endl << m3 << std::endl << std::endl << "b:" << std::endl << b3 << std::endl << std::endl;

  eliminacionGaussiana(m3, b3);
/*
  triangularSuperior(m3, b3);

  std::cout << m3 << std::endl << std::endl << b3 << std::endl;

  triangularInferior(m3, b3);
*/
  std::cout << "matriz de 3x3 resolucion:" << std::endl << m3 << std::endl << std::endl << "b:" << std::endl << b3 << std::endl << std::endl;

}
