#include <vector>
#include <iostream>
#include "parseador.cpp"
#include "metodos.cpp"

using namespace std;

int main (int argc, char** argv) {
	if(argc != 4){
		cout << "El programa necesita 3 argumentos:" << endl;
		cout << "main [path_datos_de_entrada] [path_salida] [numero_de_metodo]" << endl;
		cout << "Metodos disponibles:" << endl;
		cout << "0 CMM-EG" << endl;
		cout << "1 CMM-CL" << endl;
		cout << "2 WP o alternativo" << endl;
		cout << "3 CMM" << endl;
		cout << "default Enfrentamientos" << endl;
	}

	const char* inputPath = argv[1];
	const char* outputPath = argv[2];
	const char* numMetodoStr = argv[3];

	int numMetodo;
	stringstream ssNumMetodo(numMetodoStr);
	ssNumMetodo >> numMetodo;

	vector<vector<int> > victoriasDerrotas;
	vector<vector<double> > matrizEnfrentamientos;

    parseador(inputPath, matrizEnfrentamientos, victoriasDerrotas);
	
	unsigned int n = matrizEnfrentamientos.size();

	vector<vector<double> > A(n, vector<double>(n, 0.0));
	vector<double> b(n, 0.0);

	switch(numMetodo){
		case 0:
			A = cmm_A(matrizEnfrentamientos);
			b = cmm_b(victoriasDerrotas);
			eliminacionGaussiana(A, b);
			break;
		case 1:
			A = cmm_A(matrizEnfrentamientos);
			b = cmm_b(victoriasDerrotas);
			A = cholesky(A, n, n);
			break;
		case 3:
			A = cmm_A(matrizEnfrentamientos);
			b = cmm_b(victoriasDerrotas);
			break;
		default:
			A = matrizEnfrentamientos;
			break;
	}

	ofstream matrizSalida(outputPath);

    // Mostrar matriz A y vector b
	for(unsigned int i = 0; i < n; ++i){
		for(unsigned int j = 0; j < n; ++j){
			matrizSalida << A[i][j] << "\t";
		}
		matrizSalida << "\t" << b[i] << endl;
	}

	matrizSalida.close();

	return 0;
}