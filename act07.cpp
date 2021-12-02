//Adrian Valdes Zavala
//A01720439

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
const int M = 1002;
const int N = 1002;
int LCS[M][N];

//O(N*M), soluicion dinamica
int LsubSequ(string st1, string st2) {

	if (st1[0] == st2[0]) {
		LCS[0][0] = 1;
	}
	else {
		LCS[0][0] = 0;
	}

	for (int i = 1; i < st1.length(); i++) {
		if (st1[i] == st2[0]) {
			LCS[i][0] = 1;
		}
		else {
			LCS[i][0] = LCS[i-1][0];
		}
	}

	for (int j = 1; j < st2.length(); j++) {
		if (st1[0] == st2[j]) {
			LCS[0][j] = 1;
		}
		else {
			LCS[0][j] = LCS[0][j-1];
		}
	}

	for (int i = 1; i < st1.length(); i++) {
		for (int j = 1; j < st2.length(); j++) {
			if (st1[i] == st2[j]) {
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
			}
			else {
				LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
	}

	return LCS[st1.length()-1][st2.length()-1];
}


int main() {
	int n;
	string st1, st2;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> st1 >> st2;
		cout << "Case " << i << ": " << LsubSequ(st1, st2) << endl;
	}
}

/*
Casos de Prueba:

2
AAAAAAABBAAB
ABAABBAB
Case 1: 7
XMJYAUZ
MZJAWXU
Case 2: 4

1
ABABAAABB
JJABBABAB
Case 1: 6

1
ATREWQSD
AMTERTSA
Case 1: 4

2
ABCDEFG
GFEDCBA
Case 1: 1
RTTATATA
TATARATA
Case 2: 6
*/