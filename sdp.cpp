#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

vector<vector<double> > generarSDP(int dimension);

// genera matrices sdp con el metodo ((A+A')/2)+nI con A random de nxn
vector<vector<double> > generarSDP(int dimension){
    vector<vector<double> > matrizSDP(dimension, vector<double>(dimension));

    srand (time(NULL));

    // matriz random
    // matriz simetrica
    for(int i = 1; i < dimension; ++i){
        for(int j = 0; j < i; ++j){
            double sij = ((double) rand() / (RAND_MAX));
            matrizSDP[i][j] = sij;
            matrizSDP[j][i] = sij;
        }
    }

    // matriz simetrica definida positiva
    for(int i = 0; i < dimension; ++i){
        matrizSDP[i][i] = ((double) rand() / (RAND_MAX)) + dimension;
    }

    return matrizSDP;
}