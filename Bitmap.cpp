#include <iostream>
#include <vector>
using namespace std;

typedef unsigned char uchar;

uchar add(uchar mask, int pos) {
	return(mask | (1 << pos));
}

uchar remove(uchar mask, int pos) {
	return(mask & !(1 << pos));
}

bool test(uchar mask, int pos) {
	return((mask & (1 << pos)) != 0);
}

void imprimeConjunto(vector<int>& S, uchar mask) {
	cout << "{";
	for (int i = 0; i < S.size(); i++) {
		if (test(mask, i)) {
			cout << S[i] << " ";
		}
	}
	cout << "}\n";
}

int main() {
	int n, pos;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}
	int cant;
	uchar mask = 0;
	cout << "Cuantas quieres incluir: ";
	cin >> cant;
	for (int i = 0; i < cant; i++) {
		cout << "Pos a incluir";
		cin >> pos;
		mask = add(mask, pos);
	}
	imprimeConjunto(vec, mask);

}