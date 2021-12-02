//Adrian Valdes
//A01720439
//Problema de mochila

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAXOBJ 11
#define MAXMOCH 51

struct obj{
	int valor, peso;
	float valpeso;
};

bool my_comp(const obj &a, const obj& b) {
	return a.valpeso > b.valpeso;
}

// complejidad O(np)
int mochDP(vector<obj> &datos, int N, int PESO) {
	int mat[MAXOBJ][MAXMOCH];
	for (int i = 0; i <= N; i++) {
		mat[i][0] = 0;
	}
	for (int j = 0; j <= PESO; j++) {
		mat[0][j] = 0;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= PESO; j++) {
			if (datos[i-1].peso > j) {		// Obj i-1 no cabe en una mochila que soporta j de peso
				mat[i][j] = mat[i-1][j];
			}
			else {							//Obj i-1 si cabe en una mochila que soporta j de peso
				mat[i][j] = max(mat[i - 1][j], // No conviene Meterlo
					datos[i - 1].valor + mat[i - 1][j - datos[i-1].peso]);// si conviene meterlo
			}
		}
	}
	return mat[N][PESO];
}

//Complejidad O(n^2)
int mochDyV(vector<obj> &datos, int N, int PESO) {
	if (N==0 || datos[N-1].peso > PESO) {
		return 0; //No cabe el objN
	}
	return max(datos[N - 1].valor + mochDyV(datos, N - 1, PESO - datos[N - 1].peso), mochDyV(datos, N - 1, PESO)); //Si incluyo al objN
																												   //No incluye al objN
}

void bt(vector<obj>& datos, int i, int va, int vp, int vpAux /*revisar*/, int& valOptimo) {

}

int mochBT(vector<obj>& datos, int N, int PESO) {
	int vpAux = 0; // Valor posible de arranque
	int pesoAux = 0;
	int valOptimo = 0;
	int k = -1;
	while (k<N && pesoAux+datos[k+1].peso <= PESO) {
		k++;
		vpAux += datos[k].valor;
		pesoAux += datos[k].peso;
	}
	if (k < N) {
		vpAux += ((PESO - pesoAux) * datos[k].valpeso);
	}
	bt(datos, -1, 0, 0, vpAux, valOptimo);
	return valOptimo;
}

int main() {
	// N = cantidad de objetos
	// PESO = Peso que soporta la mochila
	int v, p, N, PESO;
	float vp;
	cin >> N >> PESO;
	vector<obj> datos;
	for (int i = 0; i < N; i++) {
		cin >> v >> p;
		vp = v * 1.0 / p;
		obj misDatos;
		misDatos.valor = v;
		misDatos.peso = p;
		misDatos.valpeso = vp;
		datos.push_back(misDatos);
	}
	sort(datos.begin(), datos.end(), my_comp);
	cout << "Objetos Ordenados: " << endl;
	for (int i = 0; i < N; i++) {
		cout << "Obj" << "(i+1)" << ": " << datos[i].valor << " " << datos[i].peso
			<< " " << datos[i].valpeso << endl;
	}
	cout << "La mochila con DyV: " << mochDyV(datos, N, PESO) << endl;
	cout << "La mochila con DP: " << mochDP(datos, N, PESO) << endl;
	cout << "La mochila con BT: " << mochBT(datos, N, PESO) << endl;
}

/*
4 16
10 5
40 2
50 10
30 5
==> 90

3 30
50 5
60 10
140 20
==> 200
*/
