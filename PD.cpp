#include <iostream>
#include <stdio.h>

#define MAX 10
using namespace std;

int maxPathPD(int mat[MAX][MAX], int n) {
	for (int i = n-2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			mat[i][j] += max(mat[i+1][j], mat[i+1][j+1]);
		}	
	}
	return mat[0][0];
}

void print(int mat [MAX][MAX], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}

}

int main() {
	int t, n;
	int mat[MAX][MAX];
	cin >> t;
	for (int k = 1; k <= t; k++) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				cin >> mat[i][j];
			}
		}
		cout << maxPathPD(mat, n) << endl;
	}
}







/*
2
3
1
2 1
1 2 3
4
1
1 2
4 1 2
2 3 1 1

5
9
*/