#include <iostream>
#include <stdio.h>
#define MAX 50
using namespace std;

//Complejidad: O(n*m)
int solve(int n, int m) {
	int mat[MAX][MAX];
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			mat[i][j] = 0;
		}
	}
	mat[0][0] = 1;
	for (int i = 0; i < n-1; i++){
		for (int j = 0; j < m-1; j++){
			if (i + 2 < n && j+1 < m){
				mat[i+2][j+1] += mat[i][j];
			}
			if (i + 1 < n && j + 2 < m) {
				mat[i+1][j+2] += mat[i][j];
			}
		}
	}
	return mat[n-1][m-1];
}

int main() {
	int n, m;
	cin >> n >> m;

	cout << solve(n, m) << endl;
}

/*
FunCaballo(i,j) = cab(i-2, j-1)+cab(i-1, j-2)

3 2 
==> 1

5 6
==> 3

6 6
==> 0

*/