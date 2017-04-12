#include <iostream>
#include <vector>


// Toma la matriz VictoriasDerrotas y devuelve una vector con el WPercentage de cada equipo/jugador
// indexado por posicion en la matriz
std::vector<double> WP(std::vector<std::vector<int> > victoriasDerrotas) {
  std::vector<double> b(victoriasDerrotas.size());
  for(int i = 0; i < int(victoriasDerrotas.size()); ++i){
    b[i] = (float(victoriasDerrotas[i][0])/(victoriasDerrotas[i][0]+victoriasDerrotas[i][1]));
  }
  return b;
}

int main(void){
  std::vector< std::vector<int> > quemiras(4, std::vector<int> (2, 0));

  quemiras[0][0] = 4;
  quemiras[0][1] = 10;
  quemiras[1][0] = 7;
  quemiras[1][1] = 34;
  quemiras[2][0] = 42;
  quemiras[2][1] = 10;
  quemiras[3][0] = 42;
  quemiras[3][1] = 4;

  std::vector<double> fiesta = WP(quemiras);
  std::cout << fiesta[0] << " " << fiesta[1] << " " << fiesta[2] << " " << fiesta[3] << '\n';
  return 0;
}