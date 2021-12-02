/*
5
8
2
0
1
8
==> 88210
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Complejidad: O(n logn)
void solve(vector<int> &digitos) {
	sort(digitos.begin(), digitos.end(), greater<int>());
	for (int i = 0; i < digitos.size(); i++) {
		cout << digitos[i];
	}
	cout << endl;
}

int main() {
	int n;

	cin >> n;
	vector<int> digitos(n);
	for (int i = 0; i < n; i++) {
		cin >> digitos[i];
	}
	solve(digitos);
}