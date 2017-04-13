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
			t = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000;
		}
		if (metodo == 1) {
			start = clock();
			cholesky(matrices[i], dimension);
			end = clock();
			t = (((double)(end - start)) / CLOCKS_PER_SEC) *  1000;
		}
		tiempos += t;
	}
	tiempos = tiempos; //paso los milisegundos a segundos
	double promedio = tiempos/cant; //calculo el promedio

	return promedio;
}

//vectorTiempos sirve para utilizar benchmark sobre muchas matrices de distintas dimensiones, y devolver en un vector los promedios
vector<double > vectorTiempos(int total, int cant, int metodo) {
	vector< double > tiempos(total, 0.0);
	for (int i = 0; i < total; ++i)
	{
		int dimension = i + 2;
		tiempos[i] = benchmark(dimension, cant, metodo);
	}
	return tiempos;
}


int main (int argc, char** argv) {
	if (argc != 6)
	{
		cout << "El programa necesita 5 argumentos:" << endl;
		cout << "main [path_salida] [nombre_del_output] [cantidad_total_de_matrices] [cantidad_por_dimensión] [número_de_método]" << endl;
		cout << "Métodos disponibles:" << endl;
		cout << "0 Gauss" << endl;
		cout << "1 Cholesky" << endl;
	}

	const char* outputPath = argv[1];
	const char* nombreTxt = argv[2];
	const char* totalMatStr = argv[3];
	const char* cantidadXDimStr = argv[4];
	const char* numMetodoStr = argv[5];

	int totalMat;
	stringstream ssTotalMat(totalMatStr);
	ssTotalMat >> totalMat;

	int cantidadXDim;
	stringstream ssCantidadXDim(cantidadXDimStr);
	ssCantidadXDim >> cantidadXDim;

	int numMetodo;
	stringstream ssNumMetodo(numMetodoStr);
	ssNumMetodo >> numMetodo;

	vector< double > tiempos = vectorTiempos(totalMat, cantidadXDim, numMetodo);


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