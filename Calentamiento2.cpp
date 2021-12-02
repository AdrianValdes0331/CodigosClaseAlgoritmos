//Adrian Valdes
//Profe: Luis Humberto Gonzalez

#include <iostream>

using namespace std;

//Complejidad O(1)
int obtenRes(int n) {
	int suma = n * (n + 1) / 2;
	return (suma % 2 == 0) ? 0 : 1;
}

int main() {
	int n;
	cin >> n;
	cout << obtenRes(n) << endl;
}