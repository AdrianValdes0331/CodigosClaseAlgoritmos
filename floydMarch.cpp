//Algoritmo de Floyd-Warshall
#include <iostream>
#include <stdio.h>
#include <string>
#include <climits>

#define MAX 100
using namespace std;

void leeArcos(int mat[MAX][MAX], int p[MAX][MAX], int m) {
	int a, b, c;
	for (int i = 0; i < MAX; i++) {
		mat[i][i] = p[i][i] = 0;
		for (int j = i + 1; j < MAX; j++) {
			mat[i][j] = mat[j][i] = INT_MAX;
			p[i][j] = p[j][i] = -1;
		}
	}
	//Lectura
	for (int i = 1; i <= m; i++) {
		cin >> a >> b >> c;
		mat[a-1][b-1] = mat[b-1][a-1] = c;
	}
}

// Complejidad: O(n^3)
void floyd(int mat[MAX][MAX], int p[MAX][MAX], int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (mat[i][k] != INT_MAX && mat[k][j] != INT_MAX && mat[i][k] + mat[k][j] < mat[i][j]) {
					mat[i][j] = mat[i][k] + mat[k][j];
					p[i][j] = k;
				}
			}
		}
	}
}

void print(int mat[MAX][MAX], int p[MAX][MAX], int n) {
	cout << "La matriz de costos" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "La matriz de Trayectoria" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << p[i][j] << "\t";
		}
		cout << endl;
	}
}

void checarTrayectoria(int p[MAX][MAX], int a, int b) {
	if (p[a][b] != -1) {
		checarTrayectoria(p, a, p[a][b]);
		cout << (p[a][b] + 1) << "-";
		checarTrayectoria(p, p[a][b], b);
	}
}

void consultas(int mat[MAX][MAX], int p[MAX][MAX], int q) {
	int a, b;
	for (int i = 1; i <= q; i++) {
		cin >> a >> b;
		if (mat[a - 1][b - 1] == INT_MAX) {
			cout << "no path" << endl;
		}
		else {
			cout << "Costo: " << mat[a-1][b-1] << " Path: " << a << "-";
			checarTrayectoria(p, a - 1, b - 1);
			cout << b << endl;
		}
	}
}

int main() {
	// mat es el costo de ir del nodo i al j
	// p es el nodo intermedio con nombre mayor para ir de i a j
	int mat[MAX][MAX];
	int p[MAX][MAX];
	int n, m, q, t;
	// t = cantidad de casos
	// n = cantidad de nodos
	// m = cantidad de arcos
	// q = cantidad de consulta
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n >> m >> q;
		leeArcos(mat, p, m);
		floyd(mat, p, n);
		consultas(mat, p, q);
		print(mat, p, n);
	}
}

/*
1
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
1 7
2 6
6 2


1
5 8 2
1 2 48
1 4 17
2 3 40
2 4 50
2 5 80
3 4 55
3 5 15
4 5 18
1 3
Costo: 50 Path: 1-4-5-3
3 1
Costo: 50 Path: 3-5-4-1
*/
