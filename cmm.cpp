#include <vector>

//Toma los datos parseados como la matriz A talque A[i][j] representa la cantidad de partidos jugados entre i y j
std::vector<vector<int> > CMM(std::vector<vector<int> > datos){
 std::vector<int> tam = datos.size();
 std::vector<vector<int> > cmm = cmm(tam,std::vector<int>(tam));
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
}


