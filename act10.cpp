//Adrian Valdes Zavala
//A01720439
//Act10

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define MAXOBJ 202
#define MAXMOCH 202

struct obj {
    int valor, peso;
    float valPeso;
};

bool myComp(const obj& a, const obj& b) {
    return a.valPeso > b.valPeso;
}

// Complejidad: O(n*m)
int mochDP(vector<obj>& datos, int N, int PESO) {
    int mat[MAXOBJ][MAXMOCH];
    for (int i = 0; i <= N; i++) {
        mat[i][0] = 0;
    }
    for (int j = 0; j <= PESO; j++) {
        mat[0][j] = 0;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= PESO; j++) {
            if (datos[i - 1].peso > j) {
                mat[i][j] = mat[i - 1][j];
            }
            else {
                mat[i][j] = max(mat[i - 1][j], datos[i - 1].valor + mat[i - 1][j - datos[i - 1].peso]);
            }
        }
    }
    return mat[N][PESO];
}

int main() {
    // N = cantidad de objetos
    // PESO = Peso que soporta la mochila

    int n;
    cin >> n;
    while (n--) {
        int FinalWeight = 0;
        int personas = 0;
        int v, p, N, PESO;
        float vp;
        vector<obj> datos;

        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> v >> p;
            vp = v * 1.0 / p;

            obj misDatos;
            misDatos.valor = v;
            misDatos.peso = p;
            misDatos.valPeso = vp;

            datos.push_back(misDatos);
        }
        cin >> personas;
        for (int j = 0; j < personas; j++) {
            cin >> PESO;
            sort(datos.begin(), datos.end(), myComp);
             FinalWeight += mochDP(datos, N, PESO);
        }
        cout << FinalWeight << endl;
    }
    return 0;
}

/*
2
3
72 17
44 23
31 24
1
26
6
64 26
85 22
52 4
99 18
39 13
54 9
4
23
20
20
26

==> 72
==> 514

2
1
10 10
1
9
2
20 10
20 20
2
9
8

==> 0
==> 0

1
3 
50 5
60 10
140 20
1
30
==> 200

1
6 
64 26
85 22
52 4
99 18
39 13
54 9
1
89
==>354

*/