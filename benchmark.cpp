#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "sdp.cpp"
#include "metodos.cpp"
#include <math.h>

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
			t = ((double)(end - start)) / CLOCKS_PER_SEC;
		}
		if (metodo == 1) {
			start = clock();
			cholesky(matrices[i], dimension);
			end = clock();
			t = ((double)(end - start)) / CLOCKS_PER_SEC;
		}
		tiempos += t;
	}
	tiempos = tiempos/1000; //paso los milisegundos a segundos
	double promedio = tiempos/cant; //calculo el promedio

	return promedio;
}

//vectorTiempos sirve para utilizar benchmark sobre muchas matrices de distintas dimensiones, y devolver en un vector los promedios
vector<double > vectorTiempos(int total, int base, int cant, int metodo) {
	vector< double > tiempos(total, 0.0);
	for (int i = 0; i < total; ++i)
	{
		int dimension = pow(base,i+1);
		tiempos[i] = benchmark(dimension, cant, metodo);
	}
	return tiempos;
}


int main () {
	cout << "Ingrese el total de matrices: " << endl; //es decir, si pongo 6, va a haber una de dim base, una de dim base^2, una de dim base^3, y asi...
	int total;
	cin >> total; cout << endl;
	cout << "Ingrese la base deseada: " << endl; //la base que voy a elevar para conseguir cada dimensión
	int base;
	cin >> base; cout << endl;
	cout << "Ingrese cantidad de matrices por base:" << endl; //la cantidad de matrices por dimensión, para hacer un promedio por dimensión
	int cant;
	cin >> cant; cout << endl;
	cout << "Ingrese el tipo de método (1 gauss, 2 cholesky):" << endl;
	int metodo;
	cin >> metodo; cout << endl;

	vector< double > tiempos = vectorTiempos(total, base, cant, metodo);

	for (int i = 0; i < total; ++i)
	{
		cout << tiempos[i] << " ";
	}

	return 0;

}