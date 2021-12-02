// Algoritmo Knuth-Morris-Pratt (KMP)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//longest proper prefix which is also a suffix
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
			else{
				j = lpsv[j - 1];				
			}				
		}
		
	}
	return posMatch;
}

int main() {
	string texto, patron;
	cin >> texto >> patron;
	vector<int> posMatch = kmp(texto, patron);
	if (posMatch.size() == 0) {
		cout << "No Match" << endl;
	}
	else {
		for (int i = 0; i < posMatch.size(); i++) {
			cout << posMatch[i] << " ";
		}
		cout << endl;
	}
}
