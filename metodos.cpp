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


// Metodo de Colley
//Toma los datos parseados como la matriz A talque A[i][j] representa la cantidad de partidos jugados entre i y j
vector<vector<double> > cmm_A(const vector<vector<double> >& datos){
	int tam = datos.size();
	vector<vector<double> > cmm(tam,vector<double>(tam,0));
	int i = 0;
	int j = 0;
	while(i < tam ){
		j = 0;
		while(j < tam){
			if (i == j) {
				cmm[i][j] = 2 + datos[i][j];
			}
			else{
				cmm[i][j] = -(datos[i][j]);
			}
			j++;
		}
		i++;
	}	
	return cmm;
}


vector<double> cmm_b(const vector<vector<int> >& victoriasDerrotas){
	vector<double> b(victoriasDerrotas.size());
	for(int i = 0; i < victoriasDerrotas.size(); ++i){
		b[i] = 1 + (victoriasDerrotas[i][0] - victoriasDerrotas[i][1]) / 2;
	}
	return b;
}


// Elimincaion de Gauss
void eliminacionGaussiana(vector<vector<double> > &A, vector<double> &b)
{
    int dimension = A.size();

    for(int j = 0; j < dimension; ++j)
    {
        int filaDelPivot = j;

        // Se analiza el caso en el que el pivot "es cero"
        // Se asume que el sistema tiene solucion y es unica
        // Si para toda fila menor que filaDelPivot, la posicion j vale 0, el algoritmo falla estrepitosamente
        while(abs(A[filaDelPivot][j]) < UMBRAL_CERO && filaDelPivot < dimension)
        {
            int filaSwap = buscarFilaPivotInferior(A, filaDelPivot+1, j);
            if(filaSwap < dimension)
            {
                A[filaDelPivot].swap(A[filaSwap]);
            }
        }

        double pivot = A[filaDelPivot][j];

        // Establecido el pivot, comenzamos el algoritmo en la siguiente fila

        for(int i = filaDelPivot+1 ; i < dimension; ++i)
        {
            double factorDeEscalaEntreFilas = A[i][j] / pivot;

            for(int c = j; c < dimension; ++c)
            {
                A[i][c] -= factorDeEscalaEntreFilas * A[j][c];
            }

            b[i] -= factorDeEscalaEntreFilas * b[j];
        }
    }
    // Piso con cero debajo de la diagonal, por si quedo algun número muy pequeño que debía ser cero
    for (int i = 0; i < dimension; ++i)
    {
    	for (int j = 0; j < dimension; ++j)
    	{
    		if (i>j)
    		{
    			A[i][j] = 0.0;
    		}
    	}
    }
}


int buscarFilaPivotInferior(const vector<vector<double> > &A, int fila, int col)
{
    int dimension = A.size();
    while(fila < dimension && A[fila][col] < UMBRAL_CERO)
    {
        ++fila;
    }
    return fila;
}


// Cholesky
double diagonal(int i, const vector<vector<double> >& A, const vector<vector<double> >& L) {
	double suma = 0;
	for (int k = 0; k <= i - 1; ++k) {
		suma = suma + pow(L[i][k], 2);
	}
	return sqrt(A[i][i] - suma);
}


double alrededorDiagonal(int i, int j, const vector<vector<double> > &A, const vector<vector<double> >& L) {
	double suma = 0;
	for (int k = 0; k <= j - 1; ++k) {
		suma = suma + (L[i][k] * L[j][k]);
	}
	return (A[i][j] - suma) / L[j][j];
}

double ultimoLugar(const vector< vector < double> > &A, const vector< vector < double> > &L) {
	int dimension = A.size();
	double suma = 0;
	for(int k = 0; k < dimension - 1; k++) {
		suma = suma + pow(L[dimension - 1][k], 2);
	}
	return sqrt(A[dimension - 1][dimension - 1] - suma);
}

vector<vector < double > > cholesky(const vector<vector<double> >& A, int dimension/*, int filas, int cols*/) {
	vector<vector<double> > L(dimension, vector<double>(dimension, 0.0));
//	
//	L[0][0] = sqrt(A[0][0]);
//	for(int j = 1; j < dimension; j++) {
//		L[j][0] = A[j][0] / L[0][0];
//	}
//	for(int i = 1; i < dimension - 1; i++) {
//		L[i][i] = diagonal(i, A, L);
//		for(int j = i + 1; j < dimension; j++) {
//			L[j][i] = ultimoLugar(A, L);
//		}
//	}
//	L[dimension - 1][dimension - 1] = alrededorDiagonal(dimension-1, dimension-1, A, L);
//	L.resize(filas);
//	for (int i = 0; i < filas; ++i) {
//		L[i].resize(cols);
//	}

	for (int i = 0; i < dimension; ++i) {
		for (int j = 0; j < dimension; ++j) {
			if (i == j) {
				L[i][i] = diagonal(i, A, L);
			} else {
				if (i < j) {
					L[i][j] = 0;
				} else {
					L[i][j] = alrededorDiagonal(i, j, A, L);
				}
			}
		}
	}
	return L;
}


// Resolucion de matrices triangulares
vector<double> resolverTriangularSuperior(vector<vector<double> >& A, vector<double>& b)
{
    int dimension = A.size();
    vector<double> x(dimension, 0.0);
    // Se resuelve el sistema desde la ultima fila(en la cual todos los coeficientes son cero menos uno) hacia arriba
    for(int i = dimension - 1; i >= 0; --i)
    {
		double resultadoParcial = 0.0;
        for(int j = dimension - 1; j > i; --j)
        {
            resultadoParcial += x[j] * A[i][j];
        }
		x[i] = (b[i] - resultadoParcial) / A[i][i];
    }
    return x;
}


vector<double> resolverTriangularInferior(vector<vector<double> >& A, vector<double>& b)
{
    int dimension = A.size();
    vector<double> x(dimension, 0.0);

    // Se resuelve el sistema desde la primera fila(en la cual todos los coeficientes son cero menos uno) hacia abajo
    for(int i = 0; i >= 0; ++i)
    {
		double resultadoParcial = 0.0;
        for(int j = 0; j < i; ++j)
        {
            resultadoParcial += x[j] * A[i][j];
        }
		x[i] = (b[i] - resultadoParcial) / A[i][i];
    }
    return x;
}

vector< vector<double> > transponer(vector< vector<double> > & A) {
	int dimension = A.size();
	vector<vector<double> > At(dimension, vector<double>(dimension, 0.0));
	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j)
		{
			At[i,j] = A[j,i];
		}
	}
	return At;
}