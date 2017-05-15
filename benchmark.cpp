#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "sdp.cpp"
#include "src/metodos.cpp"
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

//Benchmark devuelve el promedio del metodo pasado ejecutado sobre una cantidad cant de matrices de dimensión dimension
double benchmark(int dimension, int cant, int metodo, int cantVecb) {
	vector<vector<double> > matrices [cant];
	vector<double> b[cant][cantVecb];
	//vector<double> b(dimension, 1.0);

	for (int i = 0; i < cant; ++i)
	{
		matrices[i] = generarSDP(dimension);

		for (int j = 0; j < cantVecb; ++j)
		{
			b[i][j] = vector<double>(dimension);
			for(int k = 0; k < cantVecb; ++k){
				b[i][j][k] = (double) rand() / (RAND_MAX);
			}
		}
	}

	double tiempos = 0.0;

	for (int i = 0; i < cant; ++i)
	{
		double t = 0.0;
		clock_t start;
		clock_t end;
		if (metodo == 0) {
			start = clock();
			for(int j = 0; j < cantVecb; ++j){
				eliminacionGaussiana(matrices[i], b[i][j]);
			}
			end = clock();
			t = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000; //dejo todo en milisegundos, para que no salte notación cientifica
		}
		if (metodo == 1) {
			start = clock();
			vector<vector<double> > resCholesky = cholesky(matrices[i], dimension);
			for(int j = 0; j < cantVecb; ++j){
				resolverTriangularInferior(resCholesky, b[i][j]);
			}
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
vector<double > vectorTiempos(int metodo, int dimMin, int dimMax, int dimStep, int cant, int cantVecb) {
	int total = 1 + (dimMax - dimMin) / dimStep;
	vector< double > tiempos(total, 0.0);
	for (int i = 0; i < total; ++i)
	{
		int dimension = dimMin + i * dimStep;
		tiempos[i] = benchmark(dimension, cant, metodo, cantVecb);
	}
	return tiempos;
}


int main (int argc, char** argv) {
	if (argc != 9)
	{
		cout << "El programa necesita 8 argumentos:" << endl;
		cout << "main [path_salida] [nombre_del_output] [número_de_método] [dimension_minima] [dimension_maxima] [dimension_step] [cantidad_por_dimensión] [cantidad_vector_b]" << endl;
		cout << "Métodos disponibles:" << endl;
		cout << "0 Gauss" << endl;
		cout << "1 Cholesky" << endl;
		cout << endl;
	}

	const char* outputPath = argv[1];
	const char* nombreTxt = argv[2];
	const char* numMetodoStr = argv[3];
	const char* dimMinStr = argv[4];
	const char* dimMaxStr = argv[5];
	const char* dimStepStr = argv[6];
	const char* cantidadXDimStr = argv[7];
	const char* cantVecbStr = argv[8];

	int numMetodo;
	stringstream ssNumMetodo(numMetodoStr);
	ssNumMetodo >> numMetodo;

	int dimMin;
	stringstream ssDimMin(dimMinStr);
	ssDimMin >> dimMin;

	int dimMax;
	stringstream ssDimMax(dimMaxStr);
	ssDimMax >> dimMax;

	int dimStep;
	stringstream ssDimStep(dimStepStr);
	ssDimStep >> dimStep;

	int cantidadXDim;
	stringstream ssCantidadXDim(cantidadXDimStr);
	ssCantidadXDim >> cantidadXDim;

	int cantVecb;
	stringstream ssCantVecbStr(cantVecbStr);
	ssCantVecbStr >> cantVecb;

	vector< double > tiempos = vectorTiempos(numMetodo, dimMin, dimMax, dimStep, cantidadXDim, cantVecb);


	ofstream tiemposTexto(outputPath);
	tiemposTexto.open(nombreTxt);

	for (int i = 0; i < tiempos.size() - 1; ++i)
	{
		tiemposTexto << tiempos[i] << endl;
	}
	tiemposTexto << tiempos.back(); //así no hay un endl de mas...

	tiemposTexto.close();

	return 0;

}