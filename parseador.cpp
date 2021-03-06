#include "parseador.h" 
#include <algorithm>

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

void parseador(const char* f, vector<vector<double> >& enfrentamientos, vector<vector<int> >& victDerrt){
    ifstream partidos(f);
    string line;
    vector<string> ids;

	// la primera linea del archivo no es un enfrentamiento
    getline(partidos, line);

	while(getline(partidos, line)){
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

	// el parceador de la catedra ordena los ids
	sort(ids.begin(), ids.end());

	// volver al principio del archivo
    partidos.clear();
    partidos.seekg(0);
    getline(partidos, line);
    
    // La matriz enfren es de N*N, simetrica, la posicion i,j es la cantidad de
    // que hubo entre el jugador i y el jugador j
    // vicDer es una matriz de N*2, (i,1) es la cantidad de victorias del jugador i
    // (i,2) es la cantidad de derrotas del jugador i
	vector<vector<int> > vicDer(ids.size(),vector<int>(2, 0));
	vector<vector<double> > enfren(ids.size(),vector<double>(ids.size(), 0.0));

	while(getline(partidos,line)) {
		vector<string> datos = rowToArray(line);
		int i, j;

		stringstream ssPuntajeJugadorIzq(datos[2]);
		ssPuntajeJugadorIzq >> i;

		stringstream ssPuntajeJugadorDer(datos[4]);
		ssPuntajeJugadorDer >> j;

		if(i > j){
			i = busquedaIndice(datos[1], ids);
			j = busquedaIndice(datos[3], ids);
		}
		else{
			i = busquedaIndice(datos[3], ids);
			j = busquedaIndice(datos[1], ids);
		}

		vicDer[i][0]++; //victorias
		vicDer[j][1]++; //derrotas
		enfren[i][j]++;
        enfren[j][i]++;
	}

	for(int i = 0; i < ids.size(); ++i){
		enfren[i][i] = vicDer[i][0] + vicDer[i][1];
	}

    enfrentamientos = enfren;
    victDerrt = vicDer;

    partidos.close();
}
