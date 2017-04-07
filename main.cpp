#include <vector>
#include "parseador.cpp"
#include "cmm.cpp"

int main () {
    const char* filePath = "./data/atp_matches_2015.dat";

	vector<vector<int> > victoriasDerrotas;
	vector<vector<int> > matrizEnfrentamientos;

    parseador(filePath, matrizEnfrentamientos, victoriasDerrotas);

    // Mostrar matriz de encuentros
	unsigned int n = matrizEnfrentamientos.size();

	for(unsigned int i = 0; i < n; ++i){
		for(unsigned int j = 0; j < n; ++j){
			std::cout << matrizEnfrentamientos[i][j] << "\t";
		}
		std::cout << std::endl;
	}
        
    vector<vector<int> > cmm = CMM(matrizEnfrentamientos);

	return 0;	
}