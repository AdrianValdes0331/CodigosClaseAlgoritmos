//Adrian Valdes Zavala A01720439
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

//Complejidad O (m*n)
int encuentraCamino(vector<vector<int> > camino, int m, int n) {
	//Nueva "matriz" encargada de retener los valores minimos
	vector<vector<int> > caminoEF(m, vector<int>(n));
	//doble for loop para ir formando nuestra nueva "matriz"
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			caminoEF[i][j] = camino[i][j];

			if (i == 0 && j > 0) {
				caminoEF[0][j] += caminoEF[0][j-1];
			}

			else if (j == 0 && i > 0) {
				caminoEF[i][0] += caminoEF[i - 1][0];
			}

			else if (i > 0 && j > 0) {
				caminoEF[i][j] += min(caminoEF[i - 1][j], caminoEF[i][j - 1]);
			}

		}
	}
	//Regresamos el ultimo valor de nuestra nueva "matriz" que seria la suma
	//del camino mas eficiente.
	return caminoEF[m-1][n-1];
}

int main() {
	int m, n;
	cin >> m;
	cin >> n;

	/*
	Usamos vectores en lugar de matriz para poder
	modificar valores
	*/
	vector<vector<int> > matriz(m, vector<int>(n));
	//int matriz[M][N];
	
	//Rellenamos la "matriz"(vector) con datos de usuario
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matriz[i][j];
		}
	}
	//mandamos la "matriz junto con los valores de columnas (n) y renglones (m)"
	cout << "Gasolina usada: " << encuentraCamino(matriz, m, n) << endl;
}

/*
Casos de Prueba:

5 4
2  2 15  1
5  1 15  1
5  3 10  1
5  2  1  1
8 13  2 15

==>27

3 5
1 2 1 1 3
2 10 2 2 3
1 1 0 1 3

==> 9

4 2
2 1
3 1
1 5
2 9

==> 17

4 4
2 1 5 4
4 5 6 9
7 4 1 2
9 8 1 1 

==> 15
*/