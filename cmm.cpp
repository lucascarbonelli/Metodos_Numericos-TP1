#include <vector>

using namespace std;

//Toma los datos parseados como la matriz A talque A[i][j] representa la cantidad de partidos jugados entre i y j
vector<vector<int> > CMM(vector<vector<int> > datos){
 int tam = datos.size();
 vector<vector<int> > cmm(tam,vector<int>(tam));
 int i = 0;
 int j = 0;
 while(i < tam ){
  j = 0;
  while(j < tam){
   if (i == j) {
    cmm[i][j] = 2 + datos[i][j];
   }
   else{
    cmm[i][j] = -datos[i][j];
   }
   j++;
  }
  i++;
 }
 return cmm;
}


