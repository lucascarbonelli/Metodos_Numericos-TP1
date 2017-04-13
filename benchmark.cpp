#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "sdp.cpp"
#include "metodos.cpp"
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

//Benchmark devuelve el promedio del metodo pasado ejecutado sobre una cantidad cant de matrices de dimensión dimension
double benchmark(int dimension, int cant, int metodo) {
	vector<vector<double> > matrices [cant];
	vector<double> b(dimension, 1.0);

	for (int i = 0; i < cant; ++i)
	{
		matrices[i] = generarSDP(dimension);
	}

	double tiempos = 0.0;

	for (int i = 0; i < cant; ++i)
	{
		double t = 0.0;
		clock_t start;
		clock_t end;
		if (metodo == 0) {
			start = clock();
			eliminacionGaussiana(matrices[i], b);
			end = clock();
			t = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000; //dejo todo en milisegundos, para que no salte notación cientifica
		}
		if (metodo == 1) {
			start = clock();
			cholesky(matrices[i], dimension);
			end = clock();
			t = (((double)(end - start)) / CLOCKS_PER_SEC) *  1000;
		}
		tiempos += t;
	}
	tiempos = tiempos;
	double promedio = tiempos/cant; //calculo el promedio

	return promedio;
}

//vectorTiempos sirve para utilizar benchmark sobre muchas matrices de distintas dimensiones, y devolver en un vector los promedios
vector<double > vectorTiempos(int total, int cant, int metodo, int opcion, int base) {
	vector< double > tiempos(total, 0.0);
	for (int i = 0; i < total; ++i)
	{
		int dimension;
		if (opcion == 0) {dimension = pow(i+2, base);}
		if (opcion == 1) {dimension = i + 2;}
		tiempos[i] = benchmark(dimension, cant, metodo);
	}
	return tiempos;
}


int main (int argc, char** argv) {
	if (argc != 8)
	{
		cout << "El programa necesita 7 argumentos:" << endl;
		cout << "main [path_salida] [nombre_del_output] [cantidad_total_de_matrices] [cantidad_por_dimensión] [número_de_método] [base_o_corrido] [base]" << endl;
		cout << "Métodos disponibles:" << endl;
		cout << "0 Gauss" << endl;
		cout << "1 Cholesky" << endl;
		cout << "Opciones:" << endl;
		cout << "0 matrices con dimension base^i, con 2<i<cantidad_total_de_matrices+2" << endl;
		cout << "1 matrices con dimension i, con 2<i<cantidad_total_de_matrices+2" << endl;
		cout << endl;
	}

	cout << "AVISO: si elegiste base, tenes en cuenta que si cantidad_total_de_matrices = 10, va a calcular matrices de base^10xbase^10, es decir" << endl;
	cout << "si elegiste cantidad_total_de_matrices = 1000, va a calcular matrices de base^1000xbase^1000, no va a terminar NUNCA." << endl;

	const char* outputPath = argv[1];
	const char* nombreTxt = argv[2];
	const char* totalMatStr = argv[3];
	const char* cantidadXDimStr = argv[4];
	const char* numMetodoStr = argv[5];
	const char* opcionStr = argv[6];
	const char* baseStr = argv[7];

	int totalMat;
	stringstream ssTotalMat(totalMatStr);
	ssTotalMat >> totalMat;

	int cantidadXDim;
	stringstream ssCantidadXDim(cantidadXDimStr);
	ssCantidadXDim >> cantidadXDim;

	int numMetodo;
	stringstream ssNumMetodo(numMetodoStr);
	ssNumMetodo >> numMetodo;

	int opcion;
	stringstream ssOpcionStr(opcionStr);
	ssOpcionStr >> opcion;

	int base;
	stringstream ssBaseStr(baseStr);
	ssBaseStr >> base;

	vector< double > tiempos = vectorTiempos(totalMat, cantidadXDim, numMetodo, opcion, base);


	ofstream tiemposTexto(outputPath);
	tiemposTexto.open(nombreTxt);

	for (int i = 0; i < totalMat - 1; ++i)
	{
		tiemposTexto << tiempos[i] << endl;
	}
	tiemposTexto << tiempos[totalMat - 1]; //así no hay un endl de mas...

	tiemposTexto.close();

	return 0;

}