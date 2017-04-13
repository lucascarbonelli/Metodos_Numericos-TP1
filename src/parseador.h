#ifndef PARSEADOR_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> rowToArray(string line);
int busquedaIndice(string datos, vector<string> ids);
void parseador(const char* f, vector<vector<double> >& enfrentamientos, vector<vector<int> >& victDerrt);

#endif
