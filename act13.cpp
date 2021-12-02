// Adrian Valdes Zavala
// A01720439
// Algoritmo de Godbole
#include <iostream>
#include <stdio.h>
#include <climits>

using namespace std;

#define MAX 52
#define MIN(x,y) ( (x) >= (y) ? (y) : (x) ) 

// Complejidad: O(n^3)
void calcula(int D[MAX][MAX], int P[MAX][MAX], int d[MAX], int n) {
	// Aquí va tu código
	//Vamos a despreciar la columna 0 y renglon 0
	for (int i = 1; i <= n; i++) { //llenamos con ceros la primer diagonal
		D[i][i+1] = P[i][i+1] = 0;
	}
	int j, aux, men, menk;
	for (int j = 2; j <= n + 1; j++) {
		for (int i = j-2; i>=0; i--) {// Renglon Correcto 
			//j = i + j;	//Representa la columna
			men = INT_MAX;
			menk = -1;
			for (int k = i+1; k < j; k++) {
				aux = D[i][k] + D[k + 1][j] + d[i - 1] * d[k] * d[j];
				men = MIN(men, D[i][k] + D[k][j] + d[j] - d[i]);
				/*if (aux < men) {
					men = aux;
					menk = k;
				}*/
			}
			D[i][j] = men;
			P[i][j] = menk;
		}
	}
}

int main() {
	int t;
	while (cin >> t && t != 0) {
		int d[MAX]; // Las dimenciones de las matrices
		// D guarda las múltipicaciones minimas escalares desde la matriz i hasta la matriz j
		// P guarda la k que minimiza las MEM Mi...Mj
		int D[MAX][MAX], P[MAX][MAX];
		int n; // cantidad de matrices a mult.
		cin >> n;
		d[0] = 0;
		d[n + 1] = t;
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				D[i][j] = P[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; i++) {
			cin >> d[i];
		}


		calcula(D, P, d, n);
		cout << "The minimum cutting is " << D[0][n + 1] << "." << endl;
	}
	return 0;
}

/*

Casos de prueba:
100
3
25 50 75
==>200

10
4
1 5 7 8
==> 22

10
3
4 8 9
==> 18

6
2 4 6 8 10 12
==> 8

*/

/*
4
20 2 30 12 8

RESP = 1232
(A)x(((B)x(C))x(D))
*/

// A  8 x 2
// B  2 x 5
// C  5 x 4
// n = 3
// d  8 2 5 4


/*

100
3
25 50 75
10
4
1 5 7 8
0

Para la tarea 13:
Cortamos madera en secciones:
p1 p2 p3 p4
--|--|--|--
0 10 8	6

p1 p2 p3 p4 p5
--|--|--|--|--
0 4  5  7  8

  _1___2___3___4___5_
1| 0 | 5 | 10| 15| 22|
2| - | 0 | 3 | 7 | 12|
3| - | - | 0 | 3 | 8 |
4| - | - | - | 0 | 3 |
5| - | - | - | - | 0 |

*/