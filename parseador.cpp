#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

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

std::vector<vector<int> > parseadorParaTenis(){
	fstream partidos("LOSPARTIDOSDETENIS");
	std::string line;
	int lines = 1;
	std::vector<int> ids = ids();

	//hago la primera iteracion a manopla para no tener el vector de ids vacio
	getline(partidos,line);
	string[5] datos = rowToArray(line);
	id.push_back(datos[1]);
	id.push_back(datos[3]);
	
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
	partidos.sekkg(0,ios::beg);
	std::vector<vector<int> > victorias = victorias(lines,vector<int>(3));
	std::vector<vector<int> > enfrentamientos = enfrentamientos(lines,vector<int>lines);
 	//TODO: llenar las victorias y enfrentamientos
	//while()

}