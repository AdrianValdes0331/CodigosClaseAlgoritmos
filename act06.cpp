//Adrian Valdes Zavala
//A01720439

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
const int M = 1002;
const int N = 1002;
int LCS[M][N];

//O(N*M), soluicion dinamica
int Lsubstring(string st1, string st2) {
	int max = 0;
	for (int i = 1; i < st1.length(); i++) {
		if (st1[i] == st2[0]) {
			LCS[i][0] = 1;
			max = 1;
		}
		else {
			LCS[i][0] = 0;
		}
	}
	for (int j = 1; j < st2.length(); j++) {
		if (st1[0] == st2[j]) {
			LCS[0][j] = 1;
			max = 1;
		}
		else {
			LCS[0][j] = 0;
		}
	}
	for (int i = 1; i < st1.length(); i++) {
		for (int j = 1; j < st2.length(); j++) {
			if (st1[i] == st2[j]) {
				LCS[i][j] = LCS[i-1][j-1] + 1;
				if (LCS[i][j] > max) {
					max = LCS[i][j];
				}
			}
			else {
				LCS[i][j] = 0;
			}
		}
	}
	return max;
}


int main() {
	int n;
	string st1, st2;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> st1 >> st2;
		cout << "Case " << i << ": " << Lsubstring(st1, st2) << endl;
	}
}

/*
Casos de Prueba:

1
AAAAAAABBAAB
ABAABBAB
-> Case 1: 5

1
XMJYAUZ
MZJAWXU
-> Case 1: 1

1
REQW
QWER
-> Case 1: 2

2
POUUQQQW
WWWUUQWW
-> Case 1: 3
MMMEEEMMRT
TTRMMEEMMY
-> Case 2: 4

*/