#include <iostream>
#include <climits>
#include <queue>

#define MAX 21

using namespace std;

struct Nodo{
	int niv;
	int costoAcum;
	int costoPos;
	int verticeAnterior;
	int verticeActual;
	bool visitados[MAX];
	bool operator<(const Nodo &otro) const{ //Para que la fila priorizada tenga la prioridad de 
		return costoPos >= otro.costoPos; 	// menor costo posible.
	}
};

void iniciaMat(int matAdj[MAX][MAX]){
	for (int i=0; i<MAX; i++){
		matAdj[i][i] = 0;
		for (int j=i+1; j<MAX; j++){
			matAdj[i][j] = matAdj[j][i] = INT_MAX;
		}
	}
}

void leeArcos(int matAdj[MAX][MAX], int m){
	int c;
	char a, b;
	for (int i=0; i<m; i++){
		cin >> a >> b >> c;
		matAdj[a-'A'+1][b-'A'+1] = matAdj[b-'A'+1][a-'A'+1] = c;
	}
}

void calculaCostoPosible(Nodo &nodoActual, int matAdj[MAX][MAX], int n){
	nodoActual.costoPos = nodoActual.costoAcum;
	int costoObtenido;
	for (int i=1; i<=n; i++){
		costoObtenido = INT_MAX;
		// No he visitado al nodo i o soy el ultimo visitado
		if (!nodoActual.visitados[i] || i == nodoActual.verticeActual){
			if(!nodoActual.visitados[i]){// No lo he visitado
				for (int j=1; j<=n; j++){
					if (i != j && (!nodoActual.visitados[j] || j == 1)){
						costoObtenido = min(costoObtenido, matAdj[i][j]);
					}
				}
			}
			else{ // Soy el último visitado
				for (int j=1; j<=n; j++){
					if (!nodoActual.visitados[j]){
						costoObtenido = min(costoObtenido, matAdj[i][j]);
					}
				}
			}
			nodoActual.costoPos += costoObtenido;
		}
	}
}

int tsp(int matAdj[MAX][MAX], int n){
	int costoOptimo = INT_MAX;
	Nodo raiz;
	raiz.niv = 0;
	raiz.costoAcum = 0;
	raiz.verticeActual = 1;
	raiz.verticeAnterior = 0;
	raiz.visitados[1] = true; // garantizar que todos los demás tengan false.
	calculaCostoPosible(raiz, matAdj, n);
	priority_queue<Nodo> pq;
	pq.push(raiz);
	while (!pq.empty()) {
		// Aquí va tu implementación.
		pq.pop();
		if (raiz.costoPos < costoOptimo) {
			for (int i = 0; i < pq.size(); i++) {
				if (matAdj[1][i]) {
					if (!raiz.visitados[i]) {
						calculaCostoPosible(raiz, matAdj, n);
						// if (last connection){
						//		Real Acumulated Value
						//		if(costoreal < costoopt){
						//			costoopt = costoReal
						//		}
						//		else{
						//			pq.push(costoReal)
						//		}
						// }
					}
				}
			}
		}
	}
	return costoOptimo;
}

int main(){
	// n = cantidad de nodos
	// m = cantidad de arcos
	int n, m;
	cin >> n >> m;
	int matAdj[MAX][MAX];  // Asumimos que ocupamos en base1 A=1, B=2, C=3....
	iniciaMat(matAdj);
	leeArcos(matAdj, m);
	cout << tsp(matAdj,n) << endl;
}

/*
4 5
A B 5
A C 10
A D 8
B C 2
C D 1
*/
