// Problema de la mochila

#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

#define MAXOBJ 202
#define MAXMOCH 202
struct obj {
    int valor, peso;
    float valPeso;
};

struct node {
    int niv;
    int va;
    int pa;
    int vp;
    bool operator<(const node& otro) const{
        return vp < otro.vp;
    }
};
bool myComp(const obj &a, const obj &b) {
    return a.valPeso > b.valPeso;
}

int calculaVP(vector<obj>& datos, int i, int vpAux, int pesoAux, int N, int PESO) {
    int k = i + 1;
    while (k < N && pesoAux + datos[k].peso <= PESO) {
        vpAux += datos[k].valor;
        pesoAux += datos[k].peso;
        k++;
    }
    if (k < N) {
        vpAux += ((PESO - pesoAux)*datos[k].valPeso);
    }
    return vpAux;
}

int mochBB(vector<obj>& datos, int N, int PESO) {
    priority_queue<node> pq;
    int valOptimo = 0;
    int vp = calculaVP(datos, -1, 0, 0, N, PESO);
    node arranque;
    arranque.niv = -1;
    arranque.va = 0;
    arranque.pa = 0;
    arranque.vp = vp;
    pq.push(arranque);
    while (!pq.empty()) {
        arranque = pq.top();
        pq.pop();
        if (arranque.va > valOptimo) {
            valOptimo = arranque.va;
        }
        if (arranque.vp > valOptimo){
            arranque.niv++;
            arranque.vp = calculaVP(datos, arranque.niv, arranque.va, arranque.pa, N, PESO);
            if (arranque.vp > valOptimo && arranque.pa <= PESO) {
                pq.push(arranque);
            }
            arranque.va += datos[arranque.niv].valor;
            arranque.pa += datos[arranque.niv].peso;
            arranque.vp = calculaVP(datos, arranque.niv, arranque.va, arranque.pa, N, PESO);
            if (arranque.vp > valOptimo && arranque.pa <= PESO) {
                pq.push(arranque);
            }
        }
    }
    return valOptimo;
}

// Complejidad: O(n*m)
int mochDP(vector<obj> &datos, int N, int PESO) {
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

// Complejidad: O(2^n)
int mochDyV(vector<obj>& datos, int N, int PESO) {
    if (N == 0 || datos[N - 1].peso > PESO) {
        return 0;
    }
    return max(datos[N - 1].valor + mochDyV(datos, N - 1, PESO - datos[N - 1].peso), mochDyV(datos, N - 1, PESO));
}

void bt_helper(vector<obj> &datos, int i, int va, int pa, int vp, int N, int PESO,  int &valOptimo, vector<bool> &res, vector<bool> &inc) {
    if (i < N && pa <= PESO && vp > valOptimo) {
        if (va > valOptimo) {
            valOptimo = va;
            for (int j = 0; j < N; j++) {
                res[j] = inc[j];
            }
        }
        if (i + 1 < N) {
            //Si incluye sig obj
            inc[i + 1] = true;
            bt_helper(datos, i + 1, va + datos[i + 1].valor, pa + datos[i + 1].peso, vp, N, PESO, valOptimo, res, inc);
            //No incluye sig obj
            inc[i + 1] = false;
            int vpAux = calculaVP(datos, i + 1, va, pa, N, PESO);
            bt_helper(datos, i + 1, va, pa, vpAux, N, PESO, valOptimo, res, inc);
        }
    }
}

// Complejidad: O(2^N)
int mochBT(vector<obj> &datos, int N, int PESO, vector<bool> &res) {
    vector<bool> inc(res.size(), false);
    int vpAux = calculaVP(datos, -1, 0, 0, N, PESO);
    int valOptimo = 0;
    bt_helper(datos, -1, 0, 0, vpAux, N, PESO, valOptimo, res, inc);

    return valOptimo;
}

int main() {
    // N = cantidad de objetos
    // PESO = Peso que soporta la mochila
    int v, p, N, PESO;
    float vp;
    vector<obj> datos;

    cin >> N >> PESO;
    for (int i = 0; i < N; i++) {
        cin >> v >> p;
        vp = v * 1.0 / p;

        obj misDatos;
        misDatos.valor = v;
        misDatos.peso = p;
        misDatos.valPeso = vp;

        datos.push_back(misDatos);
    }

    sort(datos.begin(), datos.end(), myComp);
    cout << "Datos Ordenados: " << endl;
    for (int i = 0; i < N; i++) {
        cout << "Obj " << (i + 1) << ": " << datos[i].valor << datos[i].peso << endl;
    }
    cout << "La mochila con DyV: " << mochDyV(datos, N, PESO) << endl;
    cout << "La mochila con DP: " << mochDP(datos, N, PESO) << endl;
    vector<bool> res(datos.size(), false);
    cout << "La mochila con BT: " << mochBT(datos, N, PESO, res) << endl;
    cout << "Con los objetos: ";
    for (int i = 0; i < res.size(); i++) {
        if (res[i]) {
            cout << (i + 1) << " ";
        }
    }
    cout << endl;
    cout << "La mochila con BB: " << mochBB(datos, N, PESO) << endl;

    return 0;
}

/*
CASOS DE PRUEBA

4 16
10 5
40 2
50 10
30 5

3 30
50 5
60 10
140 20

6 89
64 26
85 22
52 4
99 18
39 13
54 9

*/