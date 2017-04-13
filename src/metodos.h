#ifndef METODOS_H_

#include <vector>
#include <cmath>

#define UMBRAL_CERO 1.0e-10

using namespace std;

// Todas los vectores y matrices se pasan por referencia. Execepto en Gauss, se pasan como const.
// eliminacionGaussiana es la unica funcion que modifica la matriz y el vector que le pasan por parametro 

 // Colley
vector<vector<double> > cmm_A(const vector<vector<double> >& datos);
vector<double> cmm_b(const vector<vector<int> >& victoriasDerrotas);
// Gauss
void eliminacionGaussiana(vector<vector<double> > &A, vector<double> &b);
int buscarFilaPivotInferior(const vector<vector<double> > &A, int fila, int col);
// Cholesky
double diagonal(int i, const vector<vector<double> >& A, const vector<vector<double> >& L);
double alrededorDiagonal(int i, int j, const vector<vector<double> > &A, const vector<vector<double> >& L);
vector<vector<double> > cholesky(const vector<vector<double> >& A, int dimension);
// Resolucion de matrices triangulares
vector<double> resolverTriangularSuperior(vector<vector<double> >& A, vector<double>& b);
vector<double> resolverTriangularInferior(vector<vector<double> >& A, vector<double>& b);
vector< vector<double> > transponer(vector< vector<double> > & A);
//Winning Percentage
vector<double> WinningPercentage(vector<vector<int> > victoriasDerrotas);
//Auxiliares
double kahan(vector<double> & sumar);

#endif