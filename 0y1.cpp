//Adrian Valdes A01720439
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

void quitaZerosUnos(vector<char> valor) {
    vector<char> vvalor;
    for (int i = 0; i < valor.size()-1; i++){
        if (i > 0)
        {
            if (valor[i] != valor[i + 1]) {
                valor[i] = '\0';
            }
            vvalor.push_back(valor[i]);
        }
    }
    for (int i = 0; i < vvalor.size(); i++) {
        cout << vvalor[i];
    }
    if (vvalor.size()>0) {
        quitaZerosUnos(vvalor);
    }
}

int main() {
    int n;
    cin >> n;
    char valor;
    vector<char> nValor;
  
    for (int i = 0; i < n; i++) {
        cin >> valor;
        nValor.push_back(valor);
    }
    quitaZerosUnos(nValor);

    return 0;
}
