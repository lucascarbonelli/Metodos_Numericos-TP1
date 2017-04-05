#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "cmm.cpp"
using namespace std;

//mapeo la fila del dat como un array de strings: [fecha ,ganador ,gPuntos ,perdedor,pPuntos]
vector<string> rowToArray(string line){
	vector<string> datos(5);
	int i = 0;
	stringstream ssin(line);
	while(ssin.good() && i < 5){
		ssin >> datos[i];
	
		i++;
	}
	return datos;
}

int busquedaIndice(string datos, vector<string> ids) {
	unsigned int i = 0;
	while(i < ids.size()) {
		if (datos == ids[i]){
			break;
		}
		i++;
	}
	return i;
}



int main () {
	fstream partidos("./data/atp_matches_2015.dat"); //abro el .dat de los partidos de tenis TODO
	string line;
	int lines = 1; //lines empieza con uno pero flechita hacia abajo
	vector<string> ids;
	
	//hago la primera iteracion a manopla para no tener el vector de ids vacio
	getline(partidos,line);
	vector<string> datos = rowToArray(line);
	ids.push_back(datos[1]);
	ids.push_back(datos[3]);
	// consigo las ids
	for(;getline(partidos,line);lines++){
		vector<string> datos = rowToArray(line);
		
		unsigned int i = 0;
		while (i < ids.size()){
			if (datos[1] == ids[i] ){
				break;
			}
			i++;
		}
		if (i == ids.size()){
			ids.push_back(datos[1]);
		}
		
		unsigned int j = 0;

		while(j < ids.size()){
			if (datos[3] == ids[j]){
				break;
			}
			j++;
		}
		if (j == ids.size()){
			ids.push_back(datos[3]);
		}
	}
	partidos.clear();
	partidos.seekg(0,ios::beg);
	vector<vector<int> > victDerrt(ids.size(),vector<int>(2, 0));
	vector<vector<int> > enfrentamientos(ids.size(),vector<int>(ids.size(), 0));

	lines = 0;
	for (;getline(partidos,line);lines++) {
		vector<string> datos = rowToArray(line);
		int i = busquedaIndice(datos[1], ids);
		int j = busquedaIndice(datos[3], ids);

		victDerrt[i][0]++; //victorias
		victDerrt[j][1]++; //derrotas
		enfrentamientos[i][j]++;
	}

	for(unsigned int i = 0;i < ids.size();i++){
		enfrentamientos[i][i] = victDerrt[i][0] + victDerrt[i][1];
	}

	vector<vector<int> > cmm = CMM(enfrentamientos);
        
	return 0;	
}

