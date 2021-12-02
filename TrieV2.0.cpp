//Adrian Valdes
//A01720439
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#include "trie.h"


int main() {
	int n;
	string dato;
	trie miTrie;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> dato;
		miTrie.insert(dato);
	}
	cout << "=======" << endl;

	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> dato;
		if (miTrie.search(dato)) {
			cout << "SI encontré a" << dato << endl;
		}
		else {
			cout << "No encontré a" << dato << endl;
		}
	}
}