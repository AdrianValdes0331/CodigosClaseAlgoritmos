//Adrian Valdes Zavala A01720439
#include <iostream>
#include <stdio.h>

using namespace std;
//El limite es 64*64, no creo que necesitemos un tablero mas grande
int tablero[64][64];
int	cont = 0;

//Funcion para ir llenando el tablero
//Con tilomios alrededor de la posicion seleccionada
void posicionSelect(int x1, int y1, int x2, int y2, int x3, int y3) {
	cont++;
	tablero[x1][y1] = cont;
	tablero[x2][y2] = cont;
	tablero[x3][y3] = cont;
}

//Complejidad O(n^2)
/*
Dado a que tenemos estar haciendo muchos proccesos por cada subcuadrante que se detecta
Tenemos 4 cuadrantes iniciales que se dividen por 2 y si todavia es divisible se
vuelve a dividir etc. creando un programa con complejidad quadratica. Es decir, 
El tiempo es afectado directamente por el tamaño del input.
*/
int tilomio(int Tsize, int corx, int cory) {
	
	int M, N;

	//caso base, si el espacio tiene caracter default (-1 en este caso)
	//aumentar el contador
	if (Tsize == 2) {
		cont++;
		for (int i = 0; i < Tsize; i++) {
			for (int j = 0; j < Tsize; j++) {
				if (tablero[corx + i][cory + j] == -1) {
					tablero[corx + i][cory + j] = cont;
				}
			}
		}
		return 0;
	}

	//buscamos la posicion, buscando el espacio que no sea 0.
	for (int i = corx; i < corx + Tsize; i++) {
		for (int j = cory; j < cory + Tsize; j++) {
			if (tablero[i][j] != -1) {
				M = i, N = j;
			}
		}
	}
	//dividir por quadrantes, por eso tiene que ser potencia de 2
	
	//cuadrante 1
	if (M < corx + Tsize / 2 && N < cory + Tsize / 2) {
		posicionSelect(
			corx + Tsize / 2, 
			cory + (Tsize / 2) - 1,
			corx + Tsize / 2, 
			cory + Tsize / 2, 
			corx + Tsize / 2 - 1, 
			cory + Tsize / 2);
	}
	//cuadrante 2
	else if (M < corx + Tsize / 2 && N >= cory + Tsize / 2)
	{
		posicionSelect(
			corx + Tsize / 2, 
			cory + (Tsize / 2) - 1, 
			corx + Tsize / 2,
			cory + Tsize / 2, 
			corx + Tsize / 2 - 1, 
			cory + Tsize / 2 - 1);
	}
	//cuadrante 3
	else if (M >= corx + Tsize / 2 && N < cory + Tsize / 2)
	{
		posicionSelect(
			corx + (Tsize / 2) - 1, 
			cory + (Tsize / 2), 
			corx + (Tsize / 2),
			cory + Tsize / 2, 
			corx + (Tsize / 2) - 1, 
			cory + (Tsize / 2) - 1);
			
	}
	//cuadrante 4
	else if (M >= corx + Tsize / 2 && N >= cory + Tsize / 2)
	{
		posicionSelect(
			corx + (Tsize / 2) - 1, 
			cory + (Tsize / 2), 
			corx + (Tsize / 2),
			cory + (Tsize / 2) - 1, 
			corx + (Tsize / 2) - 1,
			cory + (Tsize / 2) - 1);
	}
	//repetir para subcuadrantes 
	tilomio(Tsize / 2, corx, cory + Tsize / 2);
	tilomio(Tsize / 2, corx, cory);
	tilomio(Tsize / 2, corx + Tsize / 2, cory);
	tilomio(Tsize / 2, corx + Tsize / 2, cory + Tsize / 2);

	return 0;
}

int main() {
	//Memset, llena todos los valores del tablero con -1.
	memset(tablero, -1, sizeof(tablero));
	int Tsize, corX, corY;
	cin >> Tsize;
	cin >> corX;
	cin >> corY;

	tablero[corX][corY] = 0;
	tilomio(Tsize, 0, 0);

	//Tablero
	for (int i = 0; i < Tsize; i++) {
		for (int j = 0; j < Tsize; j++) {
			cout << tablero[i][j] << " \t";
		}
		cout << endl;
	}

}

/*
Casos de Prueba:

2
1 1
==> 1 1
	1 0 

4
2 2
==> 3 3 2 2
    3 1 1 2
	4 1 0 5
	4 4 5 5

8
2 6
==> 9  9  8  8  4  4  3  3
	9  7  7  8  4  2  2  3
	10 7  11 11 5  2  0  6
	10 10 11 1  5  5  6  6
	14 14 13 1  1  19 18 18
	14 12 13 13 19 19 17 18
	15 12 12 16 20 17 17 21
	15 15 16 16 20 20 21 21

16 
8 3
==>	31 31 30 30 26 26 25 25 10 10 9  9  5  5  4  4
	31 29 29 30 26 24 24 25 10 8  8  9  5  3  3  4
	32 29 33 33 27 27 24 28 11 8  12 12 6  6  3  7
	32 32 33 23 23 27 28 28 11 11 12 2  2  6  7  7
	36 36 35 23 41 41 40 40 15 15 14 14 2  20 19 19
	36 34 35 35 41 39 39 40 15 13 13 14 20 20 18 19
	37 34 34 38 42 39 43 43 16 16 13 17 21 18 18 22
	37 37 38 38 42 42 43 1  1  16 17 17 21 21 22 22
	52 52 51 0  47 47 46 46 1  73 72 72 68 68 67 67
	52 50 51 51 47 45 45 46 73 73 71 72 68 66 66 67
	53 50 50 54 48 48 45 49 74 71 71 75 69 69 66 70
	53 53 54 54 44 48 49 49 74 74 75 75 65 69 70 70
	57 57 56 44 44 62 61 61 78 78 77 65 65 83 82 82
	57 55 56 56 62 62 60 61 78 76 77 77 83 83 81 82
	58 55 55 59 63 60 60 64 79 76 76 80 84 81 81 85
	58 58 59 59 63 63 64 64 79 79 80 80 84 84 85 85
*/