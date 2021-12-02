//Adrian Valdes
//A01720439
//Camino Hamilteonano mas eficiente

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

#define MAX 21

struct Nodo {
	int niv;
	int costoAcum;
	int costoPos;
	int verticeAnterior;
	int verticeActual;
	bool visitados[MAX];
	bool operator<(const Nodo& otro) const {
		return costoPos >= otro.costoPos;
	}
};

void iniciaMatriz(int matAdj[MAX][MAX]) {
	for (int i = 0; i < MAX; i++) {
		matAdj[i][i] = 0;
		for (int j = i + 1; j < MAX; j++) {
			matAdj[i][j] = matAdj[j][i] = INT_MAX;
		}
	}
}

void calculaCostoPosible(Nodo& nodoActual, int matAdj[MAX][MAX], int n) {
    nodoActual.costoPos = nodoActual.costoAcum;
    int costoObtenido;
    for (int i = 1; i <= n; i++) {
        costoObtenido = INT_MAX;
        if (!nodoActual.visitados[i] || i == nodoActual.verticeActual) {
            if (!nodoActual.visitados[i]) { //no ha sido visitado
                for (int j = 0; j <= n; j++) {
                    if (i != j && (!nodoActual.visitados[j])) {
                        costoObtenido = min(costoObtenido, matAdj[i - 1][j - 1]);
                    }
                }
                //Buscar el menor entre ellos o el nodo de origen 1
            }
            else { //nodo actual
                for (int j = 1; i <= n; j++) {
                    if (!nodoActual.visitados[j]) {
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
                //Buscar en el Renglon i (o i-1) en las columnas de los nodos visitados.
            }
        }
        nodoActual.costoPos += costoObtenido;
    }
}

int main() {
	// n = cantidad de nodos;
	// m = cantidad de arcos;
	int n, m, c;
	int a, b;
	cin >> n >> m;
	int matAdj[MAX][MAX];
	iniciaMatriz(matAdj);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		matAdj[a - 'A'][b - 'A'] = matAdj[b - 'A'][a - 'A'] = c;
	}
    Nodo primero;
    primero.niv = 0;
    primero.costoAcum = 0;
    primero.verticeActual = 1;
    primero.visitados[1] = true;
    calculaCostoPosible(primero, matAdj, n);
    int costoOptimo;
    int branchAndBounds(primero, matAdj);
}

/*
45
A B 5
A C 10
A D 8
B C 23
C D 1
*/

//Cpos = cAcum + 
//3 -> {2,4,5,6}min
//2 -> {4,5,6,0}min etc