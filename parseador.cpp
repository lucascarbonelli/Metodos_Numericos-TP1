#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
//mapeo la fila de el dat como un array de strings: fecha ganador gPuntos perdedor pPuntos
std::string[] rowToArray(string line){
	std::string[5] datos;
	int i = 0;
	sstringstream ssin(line);
	while(ssin.good() && i < 4){
		ssin >> datos[i];
		i++;
	}
	return datos;
}

int i busquedaIndice(std::string datos, std::vector<int> ids) {
	int i = 0;
	while(i < ids.size()) {
		if (datos == ids[i]){
			break;
		}
		i++;
	}
	return i;
}

std::vector<vector<int> > parseadorParaTenis(){
	fstream partidos("LOSPARTIDOSDETENIS"); //abro el .dat de los partidos de tenis TODO
	std::string line;
	int lines = 1; //lines empieza con uno pero flechita hacia abajo
	std::vector<int> ids = ids();

	//hago la primera iteracion a manopla para no tener el vector de ids vacio
	getline(partidos,line);
	string[5] datos = rowToArray(line);
	ids.push_back(datos[1]);
	ids.push_back(datos[3]);
	
	// consigo las ids
	for(lines;std::getline(partidos,line);lines++){
		string[5] datos = rowToArray(line);
		
		int i = 0;

		while (i < ids.size()){
			if (datos[1] == ids[i]){
				break;
				i++;
			}
		}
		if (i == ids.size()){
			ids.push_back(datos[1]);
		}

		int j = 0;

		while(j < ids.size()){
			if (datos[3] == ids[j]){
				break;
				j++;
			}
		}
		if (j == ids.size()){
			ids.push_back(datos[3]);
		}
	}
	partidos.clear();
	partidos.seekg(0,ios::beg);
	std::vector<vector<int> > victDerrt = victDerrt(ids.size(),vector<int>(2, 0));
	std::vector<vector<int> > enfrentamientos = enfrentamientos(ids.size(),vector<int>(ids.size()), 0);

	lines = 0;
	for (lines;std::getline(partidos,line);lines++) {
		string[5] datos = rowToArray(line);
		
		int i = busquedaIndice(datos[1], ids);
		int j = busquedaIndice(datos[3], ids);

		victDerrt[i][0]++; //victorias
		victDerrt[j][1]++; //derrotas
		enfrentamientos[i][j]++;
	}
}