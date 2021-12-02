//Adrian Valdes A01720439
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

//Complejidad: O(n)
/*
En este caso es lineal, mientras la longitud sea mayor a cero 
prueba las condiciones para borrar 01 o 10
*/
void quitaZerosUnos(string valor, string v1, string v2) {

    while (valor.size() > 0)
    {
        int idx = valor.find(v1);
        if (idx == -1){
            int idx2 = valor.find(v2);
            if (idx2 == -1)
                break;
            valor.erase(idx2, v2.size());
            idx = idx2;
        }
        else {
            if (idx == -1)
                break;
            valor.erase(idx, v1.size());
        }
        
    }
    cout << valor.size() << endl;
}

//Complejidad: O(n)
int main() {
    int n;
    cin >> n;
    char valor;
    string v1 = "01";
    string v2 = "10";
    vector<char> nValor;

    for (int i = 0; i < n; i++) {
        cin >> valor;
        nValor.push_back(valor);
    }
    string SValor(nValor.begin(), nValor.end());
    quitaZerosUnos(SValor, v1, v2);

    return 0;
}

/*
Casos de Prueba:

(Caso base)
4
1100
Resultado: 0

10
1010100111
Resultado: 2

7
1100110
Resultado: 1

8
01001101
resultado: 0

*/