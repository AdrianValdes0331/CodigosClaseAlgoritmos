//Adrian Valdes Zavala A01720439

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

bool solve(string st, int n) {
	vector<int> t, m;
	for (int i = 0; i < n; i++) {
		if (st[i] == 'T') {
			t.push_back(i);
		}
		else {
			m.push_back(i);
		}
	}
	if (2*m.size() != t.size()) {
		return false;
	}
	for (int i = 0; i < m.size(); i++) {
		if (m[i] < t[i] || m[i] > t[t.size()-1-i]) {
			return false;
		}
	}
	return true;

}

int main() {
	int t,n;
	string st;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n >> st;
		cout << (solve(st, n) ? "YES" : "NO") << endl;
	}
}


/*
5
3
TMT
3
MTT
6
TMTMTT
6
TMTTTT
6
TTMMTT

Salida:
YES
NO
YES
NO
YES
*/


/*int n;
cin >> n;
int v1;
string v2;
for (int i = 1; i < n; i++) {
	cin >> v1;
	for (int j = 1; j < n; j++) {
		cin >> v2;
	}
}
cout << v1 << endl;
cout << v2 << endl;*/