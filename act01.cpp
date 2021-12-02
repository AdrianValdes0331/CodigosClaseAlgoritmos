//Adrian Valdes A01720439
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

//Complejidad:O(n^2)
//Mientras que replace_if se considera lineal si va de inicio a fin (segun cplusplus.com), en este caso es cuadratica
//porque tiene que repetir el proceso por cada par de letras, por el momento es la unica manera que lo he podido solucionar
//Si este texto todavia esta, significa que al hasta el momento de subirlo no he encontrado una forma mas eficiente. 
void changeName(int n, string lw, vector<char> nDA) {
	for (int i = 0; i < n; i++) {
		char substit;
		map<char, char> rs = {{nDA[i], nDA[i+1]}, {nDA[i + 1], nDA[i]}};
		replace_if(lw.begin(), lw.end(), [&](char c) { return (rs.find(c) != rs.end()) && (substit = rs[c]); }, substit);
		i++;
	}
	
	cout << lw << endl;
}

int main() {
	int  n;
	string lw;
	char dA;
	vector<char> nDA;

	cin >> n;
	cin >> lw;
	for (int i = 0; i < (n*2); i++) {
		cin >> dA;
		nDA.push_back(dA);
	}
	
	changeName((n*2), lw, nDA);
}

/*
Casos de Prueba:

(Caso Base):
6
abacabadaba
a b
b c
a d 
e g
f a 
b b
Resultado: cdcbcdcfcdc

5
abahgffhj
a f
b g
f h
j a
h b
Resultado: bgbfhjjfa

2
fggffggfgff
g f
f g
Resultado: fggffggfgff

10
abcdefghijklmnopqrst
a b
c d
e f
g h
i j
k l
m n
o p
q r
s t
Resultado: badcfehgjilknmporqts

*/