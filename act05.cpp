//Adrian Valdes Zavala  
//A01720439

#include <iostream>
#include <stdio.h>
#include <string>

//Variables
const int MAX = 1002;
bool tablero[MAX][MAX];
int t1[MAX], t2[MAX], sal[2 * MAX];
int n1, n2;


using namespace std;
//Complejidad O(n1*n2)
bool solve(int i, int j) {
	//Revisamos si la suma de nuestras variables es igual 
	//Al tamaño de ambos trenes -1
	if ((i+j) == n1 + n2 - 1) return true;
	//Casilla actual la convertimos a true 
	//Al principio por default siempre 0/0
	tablero[i][j] = true;
	//Comparamos la salida con el tren 1 o 2
	//Y llamamos a la funcion de manera recursiva con los valores actualizados
	if (sal[i+j] == t1[i] && solve(i+1,j)
		|| sal[i+j] == t2[j] && solve(i,j+1)) {
		return true;
	}
	else {
		return false;
	}
}


int main() {

	//Tamaño de Trenes 
	//Salir con 0 0
	while (cin >> n1 >> n2 && n1 != 0 && n2 != 0) {
		//le damos los valores a los trenes y a la salida
		for (int i = 0; i < n1; i++) {
			cin >> t1[i];
		}
		for (int i = 0; i < n2; i++) {
			cin >> t2[i];
		}
		for (int i = 0; i < n1 + n2; i++) {
			cin >> sal[i];
		}

		//Como trabajamos con booleanos, vamos a darle todos los valores de la matriz como falsos
		memset(tablero, false, sizeof(tablero));

		//mandamos a llamar la funcion solve
		//Si es posible regresamos true
		if (solve(0, 0) == true) {
			cout << "possible" << endl;
		}
		else {
			cout << "not possible" << endl;
		}
	}
	return 0;
}


/*
Caso de Prueba:

3 3
1 2 1
2 1 1
1 2 1 1 2 1
0 0
==> possible

3 3
1 2 1
2 1 2
1 1 1 2 2 2
0 0
==> not Possible

0 0
==> "Nada"

4 3
1 1 2
2 2 1 1
1 2 1 2 2 1 1
0 0
==> Possible

*/