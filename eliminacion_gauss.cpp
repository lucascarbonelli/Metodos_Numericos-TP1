#include <vector>
#include <cmath>

#define UMBRAL_CERO 1.0e-10

void resolverConEliminacionGauss(std::vector<std::vector<double> > &m, std::vector<double> &b);
void eliminacionGaussiana(std::vector<std::vector<double> > &m, std::vector<double> &b);
int buscarFilaPivotInferior(const std::vector<std::vector<double> > &m, int fila, int col);


// Resolucion con el algoritmo de eliminacion de Gauss para sistemas de ecuaciones de nxn que tienen solucion y es unica
void resolverConEliminacionGauss(std::vector<std::vector<double> > &m, std::vector<double> &b)
{
    int dimension = m.size();
    eliminacionGaussiana(m, b);

    // Se resuelve el sistema desde la ultima fila(en la cual todos los coeficientes son cero menos uno) hacia arriba
    for(int i = dimension - 1; i >= 0; --i)
    {
        for(int j = dimension - 1; j > i; --j)
        {
            b[i] -= b[j] * m[i][j];
            m[i][j] = 0;
        }

        b[i] /= m[i][i];
        m[i][i] = 1;
        
    }
}


void eliminacionGaussiana(std::vector<std::vector<double> > &m, std::vector<double> &b)
{
    int dimension = m.size();

    for(int j = 0; j < dimension; ++j)
    {
        int filaDelPivot = j;

        // Se analiza el caso en el que el pivot "es cero"
        // Se asume que el sistema tiene solucion y es unica
        // Si para toda fila menor que filaDelPivot, la posicion j vale 0, el algoritmo falla estrepitosamente
        while(std::abs(m[filaDelPivot][j]) < UMBRAL_CERO && filaDelPivot < dimension)
        {
            int filaSwap = buscarFilaPivotInferior(m, filaDelPivot+1, j);
            if(filaSwap < dimension)
            {
                m[filaDelPivot].swap(m[filaSwap]);
            }
        }

        double pivot = m[filaDelPivot][j];

        // Establecido el pivot, comenzamos el algoritmo en la siguiente fila

        for(int i = filaDelPivot+1 ; i < dimension; ++i)
        {
            double factorDeEscalaEntreFilas = m[i][j] / pivot;

            for(int c = j; c < dimension; ++c)
            {
                m[i][c] -= factorDeEscalaEntreFilas * m[j][c];
            }

            b[i] -= factorDeEscalaEntreFilas * b[j];
        }
    }
}


int buscarFilaPivotInferior(const std::vector<std::vector<double> > &m, int fila, int col)
{
    int dimension = m.size();

    while(fila < dimension && m[fila][col] < UMBRAL_CERO)
    {
        ++fila;
    }

    return fila;
}