//Adrian Valdes A01720439
//Sebastian Frenandez A01720716

//Actividad Integradora 1

#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<fstream>
#include<sstream>
#include<streambuf>
#include <time.h>

using namespace std;
const int M = 16002;
const int N = 16002;
int LCS[M][N];
ofstream salida("checking.txt");

//Complejidad O(n*m)
pair<string, int> Lsubstring(string st1, string st2) {
	string maxSubstring = "";
	vector<vector <string>> accBuffer(st1.length(), vector<string>(st2.length(), ""));
	int max = 0;
	for (int i = 1; i < st1.length(); i++) {
		if (st1[i] == st2[0]) {
			LCS[i][0] = 1;
			accBuffer[i][0] = st1[i];
			max = 1;
		}
		else {
			LCS[i][0] = 0;
		}
	}
	for (int j = 1; j < st2.length(); j++) {
		if (st1[0] == st2[j]) {
			LCS[0][j] = 1;
			accBuffer[0][j] = st2[j];
			max = 1;
		}
		else {
			LCS[0][j] = 0;
		}
	}
	for (int i = 1; i < st1.length(); i++) {
		for (int j = 1; j < st2.length(); j++) {
			if (st1[i] == st2[j]) {
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
				accBuffer[i][j] = accBuffer[i-1][j-1]+st1[i];
				if (LCS[i][j] > max) {
					maxSubstring = accBuffer[i][j];
					max = LCS[i][j];
				}

			}
			else {
				LCS[i][j] = 0;
				accBuffer[i][j] = "";
			}
		}
	}
	return make_pair(maxSubstring, max);
}

//LongestPalindrome
//Complejidad: O(n^2)
string LongestPalindrome(string str) {
	int m, max = 0;
	int n, min = 0;
	for (int i = 0; i < str.length(); i++) {
		m = i + 1, n = i;
		for (int j = -1; j < 2; j++) {
			n = i - j+1;
			for (n, m; n >= 0 && m < str.length() && str[n] == str[m]; m++, n--) {
				NULL;
			}
			if ((max - min) < (m - n - 2)) {
				min = n + 1, max = m - 1;
			}
			
		}
	}
	return str.substr(min, max - min + 1);
}

//Complejidad O(n)
//Funcion KMP y lps Vista en Clase para traer la posicion por cada archivo
vector<int> lps(string patron) {
	int n = patron.length();
	vector<int> lpsv(n, 0);
	int j = 0, i = 1;
	while (i < n) {
		if (patron[i] == patron[j]) {
			lpsv[i] = j + 1;
			j++;
			i++;
		}
		else {
			if (j == 0) {
				lpsv[i] = 0;
				i++;
			}
			else {
				j = lpsv[i - 1];
				i++;
			}
		}
	}
	return lpsv;
}

//Complejidad O(n)
vector<int> kmp(string texto, string patron) {
	vector<int> posMatch;
	vector<int> lpsv = lps(patron);
	int j = 0; //Indice donde voy en el patron
	int	i = 0; //Indice donde voy en el texto
	int n = texto.length();
	int m = patron.length();
	while (i < n) {
		if (texto[i] == patron[j]) {
			i++;
			j++;
			if (j == m) {
				posMatch.push_back(i - m);
				j = lpsv[j - 1];
			}
		}
		else {
			if (j == 0) {
				i++;
			}
			else {
				j = lpsv[j - 1];
			}
		}

	}
	return posMatch;
}

//Leer la posicion de cada mcode en todos los textos
int main() {
	clock_t tStart = clock();

	ifstream ptr("mcode.txt");
	string patron = "";
	vector<string> arrpatron;

	vector<string> Archivos{ "transmission1.txt" , "transmission2.txt" , "transmission3.txt" };
	vector<string> leerArchivos;
	for (int a = 0; a < Archivos.size(); a++) {
		ifstream str(Archivos[a]);
		string texto((istreambuf_iterator<char>(str)), istreambuf_iterator<char>());
		leerArchivos.push_back(texto);
	}

	while (getline(ptr, patron)) {
		if (patron.size() > 0) {
			arrpatron.push_back(patron);
		}
	}
	salida << "=========================\n";
	for (int i = 0; i < arrpatron.size(); i++) {
		//Primera Parte
		salida << "-------------\n";
		salida << "Codigo: " << arrpatron.at(i) << endl;
		for (int j = 0; j < Archivos.size(); j++) {
			vector<int> posMatch = kmp(leerArchivos.at(j), arrpatron.at(i));
			if (posMatch.size() == 0) {
				salida << Archivos[j] << " ==> " << " Not Found" << endl;
			}
			else {
				salida << Archivos[j] << " ==> " << posMatch.size() << " veces" << endl;
				for (int k = 0; k < posMatch.size(); k++) {
					salida << posMatch[k] + 1 << ", ";
				}
				salida << endl;
			}
		}
	}
	//Segunda Parte
	salida << "\n=========================\n";
	salida << "Palindromos mas grandes :" << endl;
	for (int j = 0; j < Archivos.size(); j++) {
		salida << "-------------\n";
		string str = LongestPalindrome(leerArchivos.at(j));
		vector<int> LPposMatch = kmp(leerArchivos.at(j), str);
		for (int k = 0; k < LPposMatch.size(); k++) {
			salida << Archivos[j] << " ==> Posicion: " << LPposMatch[k] + 1 << endl;
		}
		salida << LongestPalindrome(leerArchivos.at(j)) << endl;
	}
	//Tercera parte
	salida << "\n=========================\n";
	pair<string, int> str1 = Lsubstring(leerArchivos.at(0), leerArchivos.at(1));
	pair<string, int> str2 = Lsubstring(leerArchivos.at(0), leerArchivos.at(2));
	pair<string, int> str3 = Lsubstring(leerArchivos.at(1), leerArchivos.at(2));
	
		salida << "Las longitudes de los maximos substrings son:" << endl;
		salida << "Archivo 1 y 2: " << str1.second << endl;
		salida << "Archivo 1 y 3: " << str2.second << endl;
		salida << "Archivo 2 y 3: " << str3.second << endl;

		salida << "El contenido de los maximos substrings es:" << endl;
		salida << "Archivo 1 y 2: " << str1.first << endl;
		salida << "Archivo 1 y 3: " << str2.first << endl;
		salida << "Archivo 2 y 3: " << str3.first << endl;

	printf_s("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}

//Time taken: 47s Archivos cortos
//Time taken: 361.18s Archivos largos

/*
Instrucciones:

Leer 4 archivos de entrada
con numeros del 1-9 y caracteres de a-z
Codigo malicioso siempre son: Palindromos de Chars
-> Sacar palindromo de chars y su posicion mas largo de cada archivo
-> Sacar el substring mas largo entre todos los archivos
*/