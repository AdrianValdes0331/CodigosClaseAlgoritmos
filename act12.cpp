//Adrian Valdes
//A01720439
//Franklings con kruskal

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <unordered_set>


#define MAX 110
using namespace std;

int parent[MAX];
int E, V; 
// To represent Disjoint Sets 
struct DisjointSets{
    int u, v;
    double n;

    friend bool operator < (const DisjointSets& a, const DisjointSets& b){
        return a.n < b.n;
    }

}rnk[MAX * MAX];


int find(int x){
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

int merge(int a, int b){
    if (a % b == 0) {
        return b;
    }
    else {
        merge(b, a % b);
    }
}

struct Node{
    double x, y;
}nodo[MAX];

void load() {
    cin >> V;
    for (int i = 1; i <= V; i++) {
        cin >> nodo[i].x >> nodo[i].y;
    }
    E = 0;
    for (int i = 1; i <= V; i++) {
        for (int j = i+1; j <= V; j++) {
            rnk[E].u = i;
            rnk[E].v = j;
            rnk[E++].n = sqrt((nodo[j].x - nodo[i].x) *
                (nodo[j].x - nodo[i].x) + (nodo[j].y - nodo[i].y) *
                (nodo[j].y - nodo[i].y));
        }
        sort(rnk, rnk + E);
    }
}

//Complejidad: O(E log E)
double kruskalMST() {
    // Aquí va tu código
    double costMSTKruskal = 0;
    for (int i = 0; i <= V; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < E; i++) {
        int u = rnk[i].u;
        int v = rnk[i].v;
        double w = rnk[i].n; 
        int x = find(u);
        int y = find(v);
        if (x != y) {
            costMSTKruskal += w;
            parent[x] = y;
        }
    }
    return costMSTKruskal;
}

int main() {   
    load();
    double costMSTKruskal = kruskalMST();
    cout << fixed << setprecision(2);
    cout << costMSTKruskal << endl;    
}
/*
Casos De Prueba:

3
1.0 1.0
2.0 2.0
2.0 4.0
==> 3.41

3
1.0 1.0
-2.0 -2.0
2.0 4.0
==> 7.40

4
-1.0 -1.0
-2.0 -2.0
-2.0 4.0
==> 8.75

2
1.0 5.0
6.0 3.0 
==> 5.39
*/