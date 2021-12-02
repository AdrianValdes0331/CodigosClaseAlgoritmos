//Adrian Valdes Zavala
//A01720439

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
sin patron
aaabaaab
i:1 r:2
i:2 r:2
i:3 r:2
i:4 r:7
i:5 r:7
i:6 r:7
i:7 r:7
0,2,1,0,4,3,2,1,
O(n)

con patron
bacacabcaca
aca
i:1 r:0
i:2 r:2
i:3 r:2
i:4 r:3
i:5 r:7
i:6 r:7
i:7 r:9
i:8 r:9
i:9 r:9
i:10 r:9
i:11 r:10
i:12 r:14
i:13 r:14
i:14 r:14
2 4 9
O(n+m)
*/


vector<int> z_function(string texto) {
	int n = texto.length();
	vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i-1]);
		}
		while (i + z[i] < n && texto[z[i]] == texto[i + z[i]]) {
			z[i]++;
		}
		if (i+z[i]-1 > r) {
			l = i;//L no es necesaria
			r = i + z[i] - 1;
		}
		cout << "i:" << i << " r:" << r << endl;
	}
	return z;
}

vector<int> PMP(string texto, string patron) {
	string gral = patron + "$" + texto;
	vector<int> zF = z_function(gral);
	/*for (int i = 0; i < zF.size(); i++) {
		cout << zF[i] << ",";
	}
	cout << endl;*/
	vector<int> salida;
	for (int i = patron.length() + 1; i < gral.length(); i++) {
		if (zF[i] == patron.length()) {
			salida.push_back(i - patron.length());
		}
	}
	return salida;
}

int main() {
	string texto, patron;
	cin >> texto >> patron;
	vector<int> pos = PMP(texto, patron);
	if (pos.size() == 0) {
		cout << "No existen coincidencias" << endl;
	}
	else {
		for (int i = 0; i < pos.size(); i++) {
			cout << pos[i] << " ";
		}
		cout << endl;
	}
}