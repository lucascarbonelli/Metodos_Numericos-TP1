#include "Eigen/Dense"
#include <cmath> 

using Eigen::MatrixXd;
using Eigen::VectorXd;

#define UMBRAL_CERO 1.0e-10

void eliminacionGaussiana(MatrixXd &m, VectorXd &b);
void triangularSuperior(MatrixXd &m, VectorXd &b);
void triangularInferior(MatrixXd &m, VectorXd &b);
int buscarFilaPivotInferior(MatrixXd &m, int fila, int col);
int buscarFilaPivotSuperior(MatrixXd &m, int fila, int col);

// Resolucion con el algoritmo de eliminacion de Gauss para sistemas de ecuaciones de nxn que tienen solucion y es unica
void eliminacionGaussiana(MatrixXd &m, VectorXd &b)
{
    triangularSuperior(m, b);
    triangularInferior(m, b);

    for(int i = 0; i < b.size(); ++i)
    {
        b(i) /= m(i,i);
        m(i,i) = 1;
    }
}

void triangularSuperior(MatrixXd &m, VectorXd &b)
{
    for(int j = 0; j < m.cols(); ++j)
    {
        int filaDelPivot = j;

        // Se analiza el caso en el que el pivot "es cero"
        while(std::abs(m(filaDelPivot, j)) < UMBRAL_CERO && filaDelPivot < m.rows())
        {
            int filaSwap = buscarFilaPivotInferior(m, filaDelPivot+1, j);
            if(filaSwap < m.rows())
            {
                m.row(filaDelPivot).swap(m.row(filaSwap));
            }
            // Si para toda fila menor que filaDelPivot, la posicion j vale 0, se avanza a la siguiente columna
            else if(j < m.cols())
            {
                ++j;
            }
        }

        double pivot = m(filaDelPivot, j);

        // Establecido el pivot, comenzamos el algoritmo en la siguiente fila

        for(int i = filaDelPivot+1 ; i < m.rows(); ++i)
        {
            double factorDeEscalaEntreFilas = m(i, j) / pivot;

            for(int c = j; c < m.cols(); ++c)
            {
                m(i, c) -= factorDeEscalaEntreFilas * m(j, c);
            }

            b(i) -= factorDeEscalaEntreFilas * b(j);
        }
    }
}

void triangularInferior(MatrixXd &m, VectorXd &b)
{
    for(int j = m.cols()-1; j >= 0; --j)
    {
        int filaDelPivot = j;

        // Se analiza el caso en el que el pivot "es cero"
        while(std::abs(m(filaDelPivot, j)) < UMBRAL_CERO && filaDelPivot >= 0)
        {
            int filaSwap = buscarFilaPivotSuperior(m, filaDelPivot+1, j);
            if(filaSwap >= 0)
            {
                m.row(filaDelPivot).swap(m.row(filaSwap));
            }
            // Si para toda fila mayor que la filaDelPivot, la posicion j vale 0, se avanza a la siguiente columna
            else if(j > 0)
            {
                --j;
            }
        }

        double pivot = m(filaDelPivot, j);

        // Establecido el pivot, comenzamos el algoritmo en la fila anterior

        for(int i = filaDelPivot-1; i >= 0; --i)
        {


            double factorDeEscalaEntreFilas = m(i, j) / m(j, j);

            for(int c = j; c >= 0; --c)
            {
                m(i, c) -= factorDeEscalaEntreFilas * m(j, c);
            }

            b(i) -= factorDeEscalaEntreFilas * b(j);
        }
    }
}

int buscarFilaPivotInferior(MatrixXd &m, int fila, int col)
{
    while(fila < m.rows() && m(fila, col) < UMBRAL_CERO)
    {
        ++fila;
    }

    return fila;
}

int buscarFilaPivotSuperior(MatrixXd &m, int fila, int col)
{
    while(fila >= 0 && m(fila, col) < UMBRAL_CERO)
    {
        --fila;
    }

    return fila;
}