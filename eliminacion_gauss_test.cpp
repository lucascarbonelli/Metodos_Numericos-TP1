#include <vector>
#include <iostream>
#include "eliminacion_gauss.cpp"

void printMatrix(const std::vector<std::vector<double> > &matrix);
void printVector(const std::vector<double> &vec);

int main()
{
  std::vector<std::vector<double> > m2(2, std::vector<double>(2));
  std::vector<double> b2(2);

  m2[0][0] = 3;
  m2[1][0] = 2.5;
  m2[0][1] = -1;
  m2[1][1] = 1.5;

  b2[0] = 5;
  b2[1] = 13.5;

  std::cout << "matriz de 2x2:" << std::endl;
  printMatrix(m2);
  std::cout << std::endl;
  std::cout << "b:" << std::endl;
  printVector(b2);
  std::cout << std::endl;

  resolverConEliminacionGauss(m2, b2);

  std::cout << "matriz de 2x2:" << std::endl;
  printMatrix(m2);
  std::cout << std::endl;
  std::cout << "b:" << std::endl;
  printVector(b2);
  std::cout << std::endl;

  std::vector<std::vector<double> > m3(3, std::vector<double>(3));
  std::vector<double> b3(3);

  m3[0][0] = 3;
  m3[1][0] = 0;
  m3[2][0] = 7;
  m3[0][1] = -1;
  m3[1][1] = 2;
  m3[2][1] = 1;
  m3[0][2] = 1;
  m3[1][2] = 2;
  m3[2][2] = 1;

  b3[0] = 4;
  b3[1] = 10;
  b3[2] = 12;

  std::cout << "matriz de 3x3:" << std::endl;
  printMatrix(m3);
  std::cout << std::endl;
  std::cout << "b:" << std::endl;
  printVector(b3);
  std::cout << std::endl;

  resolverConEliminacionGauss(m3, b3);

  std::cout << "matriz de 3x3:" << std::endl;
  printMatrix(m3);
  std::cout << std::endl;
  std::cout << "b:" << std::endl;
  printVector(b3);
  std::cout << std::endl;
}


void printMatrix(const std::vector<std::vector<double> > &matrix)
{
  int dim = matrix.size();
  for(int i = 0; i < dim; ++i )
  {
    for(int j = 0; j < dim; ++j)
    {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}


void printVector(const std::vector<double> &vec)
{
  int dim = vec.size();
  for(int i = 0; i < dim; ++i )
  {
      std::cout << vec[i] << std::endl;
  }
}