#include <iostream>
#include <math.h>
#include <vector> 

using namespace std;

double diagonal(int i, vector< vector < double > > A, int filas, int cols, vector < vector < double > > L) {
	double suma = 0;
	for (int k = 0; k <= i - 1; ++k) {
		suma = suma + pow(L[i][k], 2);
	}
	return sqrt(A[i][i] - suma);
}


double alrededorDiagonal(int i, int j, vector< vector < double > > A, int filas, int cols, vector < vector < double > > L) {
	double suma = 0;
	for (int k = 0; k <= j - 1; ++k) {
		suma = suma + (L[i][k] * L[j][k]);
	}
	return (A[i][j] - suma) / L[j][j];
}

vector< vector < double > > cholesky(vector< vector< double > > A, int filas, int cols) {
	vector< vector<double> > L;
	L.resize(filas);
	for (int i = 0; i < filas; ++i) {
		L[i].resize(cols);
	}

	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (i == j) {
				L[i][i] = diagonal(i, A, filas, cols, L);
			} else {
				if (i < j) {
					L[i][j] = 0;
				} else {
					L[i][j] = alrededorDiagonal(i, j, A, filas, cols, L);
				}
			}
		}
	}
	return L;
}

int main() {
vector < vector < double > > m;
m.resize(3);
for (int i = 0; i < 3; ++i)
{
	m[i].resize(3);
}
m[0][1] = -1; m[0][2] = 0; m[1][0] = -1; m[1][2] = -1; m[2][0] = 0; m[2][1] = -1;
m[0][0] = 2; m[1][1] = 2; m[2][2] = 2;
/*vector < vector < double > > m;
m.resize(2);
for (int i = 0; i < 2; ++i)
{
	m[i].resize(2);
}
m[0][0] = 2; m[0][1] = 3; m[1][0] = 3; m[1][1] = 5;
*/
vector< vector < double > > L = cholesky(m, 3, 3);
for (int i = 0; i < 3; ++i)
{
	//cout << "i " << i << endl;
	for (int j = 0; j < 3; ++j)
	{
		//cout << "j " << j << endl;
		cout << L[i][j] << " ";
	}
	cout << endl;
}

}