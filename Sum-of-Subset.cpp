//Adrian Valdes Zavala 
//A01720439
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int VALOR, n;
vector<int> obj;
vector<bool> include;

// Complejidad: 0(2^n), teenmos 2 llamadas recursivas lineales
void sum_of_subsets(int idx, int acum, int total) {
	// La primera parte del if ==> Todavia alcanza.
	// Segunda parte del if ==> Ya consegi el acumulado o incluyendo al sig. obj no pasa
	if (acum+total >= VALOR && (acum == VALOR || acum+obj[idx+1] <= VALOR)) {
		if (acum == VALOR) { // Ya consegui una solucion y la imprimo
			for (int i = 0; i < n; i++) {
				if (include[i]){
					cout << obj[i] << " ";
				}
			}
			cout << endl;
		}
		else {
			// Si incluir al sig.obj
			include[idx + 1] = true;
			sum_of_subsets(idx+1, acum+obj[idx+1],total-obj[idx+1]);
			// No incluir al sig. obj.
			include[idx + 1] = false;
			sum_of_subsets(idx + 1, acum, total - obj[idx + 1]);
		}
	}
}

int main() {
	cin >> n >> VALOR;
	int dato, total = 0;
	for (int i = 0; i < n; i++) {
		cin >> dato; 
		obj.push_back(dato);
		total += dato;
		include.push_back(false);
	}
	sort(obj.begin(), obj.end());
	sum_of_subsets(-1, 0, total);
}

/*
5 21
10
6
5
16
11
*/
