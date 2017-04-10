#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sdp.cpp"
#include "metodos.cpp"

using namespace std;

int main (int argc, char** argv) {
	if(argc != 4){
		cout << "El programa necesita 3 argumentos:" << endl;
		cout << "main [dimension_matriz] [path_salida] [numero_de_metodo]" << endl;
		cout << "Metodos disponibles:" << endl;
		cout << "0 CMM-EG" << endl;
		cout << "1 CMM-CL" << endl;
		cout << "default Ax=b" << endl;

        return 0;
	}

	const char* dimensionMatriz = argv[1];
	const char* outputPath = argv[2];
	const char* numMetodoStr = argv[3];

	int dimMatriz;
	stringstream ssDimMatriz(dimensionMatriz);
	ssDimMatriz >> dimMatriz;

	int numMetodo;
	stringstream ssNumMetodo(numMetodoStr);
	ssNumMetodo >> numMetodo;

	vector<vector<double> > A(dimMatriz, vector<double>(dimMatriz, 0));
    A = generarSDP(dimMatriz);
	vector<double> b(dimMatriz, 0.0);

	switch(numMetodo){
		case 0:
			eliminacionGaussiana(A, b);
			break;
		case 1:
			A = cholesky(A, dimMatriz);
			break;
		default:
			break;
	}

	ofstream matrizSalida(outputPath);

    // Mostrar matriz A y vector b
	for(unsigned int i = 0; i < dimMatriz; ++i){
		for(unsigned int j = 0; j < dimMatriz; ++j){
			matrizSalida << A[i][j] << "\t";
		}
		matrizSalida << "\t" << b[i] << endl;
	}

	matrizSalida.close();

	return 0;
}