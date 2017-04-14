


void perdidos(const char* fin, const char* fout, const char* jugador){
	vector< vector<double> > meGanaron(dimension, (2, 0.0));

    ifstream partidos(f);
    string line;
    vector<string> ids;

	// la primera linea del archivo no es un enfrentamiento
    getline(partidos, line);

	while(getline(partidos, line)){
		vector<string> datos = rowToArray(line);

		int i, j;
		string jugadorPerdedor;
		string jugadorGanador;

		stringstream ssPuntajeJugadorIzq(datos[2]);
		ssPuntajeJugadorIzq >> i;

		stringstream ssPuntajeJugadorDer(datos[4]);
		ssPuntajeJugadorDer >> j;

		if(i > j){
			jugadorPerdedor = datos[3];
			jugadorGanador = datos[1];
		}
		else{
			jugadorPerdedor = datos[1];
			jugadorGanador = datos[3];
		}

		if(jugadorPerdedor == jugador){
			ids.push_back(jugadorGanador);
		}
	}
}

