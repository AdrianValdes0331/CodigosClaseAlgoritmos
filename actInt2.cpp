//Adrian Valdes A01720439
//Sebastian Frenandez A01720716
//ActividadIntegradora2

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cfloat>
#include <cmath>
#include <stdio.h>
#include <string>
#include <climits>
#include <map>
#include<fstream>
#include<sstream>
#include <queue>

#define MAX 100
using namespace std;
ofstream salida("checking2.txt");

struct Nodo {
    string nombre;
    int index, x, y, costopos, costoAcum = 0;
    bool central;
    bool operator<(const Nodo &otro) const{
        return costopos >= otro.costopos;
    }
};

typedef  pair<int, pair<Nodo, Nodo>> edge;

struct Graph {
    int cont = 0;
    int V, E, costMSTKruskal;
    vector<edge> edges;
    vector<vector<pair<int, Nodo>>> adjList;
    vector<Nodo> noCentrales;
    vector<bool> isInNoCentrales;
    vector<edge> selectedEdgesK;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        adjList = vector<vector<pair<int, Nodo>>>(V, vector<pair<int,Nodo>>(V, make_pair(INT_MAX, Nodo())));
        isInNoCentrales = vector<bool> (V, 0);
        costMSTKruskal = 0;
    }

    void addEdge(Nodo u, Nodo v, int w) {
        edges.push_back({ w, {u, v} });
        kruskalMST(); //encuentra el arbol recubridor minimo del nuevo grafo

        adjList[u.index][u.index] = make_pair(INT_MAX, u);
        adjList[v.index][v.index] = make_pair(INT_MAX, v);
        adjList[u.index][v.index] = make_pair(w, v);
        adjList[v.index][u.index] = make_pair(w, u);
        if(!u.central && !isInNoCentrales[u.index]){
            noCentrales.push_back(u);
            isInNoCentrales[u.index] = 1;
        }
        if(!v.central && !isInNoCentrales[v.index]){
            noCentrales.push_back(v);
            isInNoCentrales[v.index] = 1;
        }
    }
    void kruskalMST();
    void printEdgesk();
    void shortestRoute();
};

struct DisjointSets
{
    vector<int> parent, rnk;
    int n;

    DisjointSets(int n) {
        this->n = n;
        parent = vector<int>(n);
        rnk = vector<int>(n);
        for (int i = 0; i < n; i++) {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    // Encuentra el padre del subset/nodo
    int find(int u)
    {
        //encuentra y actualiza el padre del subset/nodo 
        //e.g. si el padre del nodo 2 esta marcado como el nodo 8, pero el padre del nodo 8 es el nodo 7
        //se encuentra el nodo 7 y el padre del nodo 2 se actualiza como el nodo 7
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        //el subset menos grande se hace parte del subset mas grande
        if (rnk[x] > rnk[y]){
            parent[y] = x;
        }
        else if(rnk[x] < rnk[y]){ 
            parent[x] = y;
        }
        //si los subsets son igual de grandes, se escoge uno como el padre
        else{
             parent[x] = y;
             rnk[y]++;
        }
    }
};

//Complejidad: O(E log E)
void Graph::kruskalMST() {
    vector<edge> selEdges;
    costMSTKruskal = 0;
    sort(edges.begin(), edges.end(), 
        [](const edge &a, const edge &b) -> bool{
            return a.first<b.first;
        }); //organiza por peso
    DisjointSets ds(V);
    Nodo u, v;
    int set_u, set_v, weight, ui, vi;

    for (auto it : edges) {
        weight = it.first;
        u = it.second.first;
        v = it.second.second;
        ui = u.index; vi = v.index; //se utiliza el indice del nodo para facilitar el proceso

        //encuentra [el indice de] la raiz del subset
        set_u = ds.find(ui);
        set_v = ds.find(vi); 

        //si los subsets no tienen el mismo padre, se hace una union entre ellos
        if (set_u != set_v) {
            ds.merge(ui, vi);
            costMSTKruskal += weight;
            selEdges.push_back({weight, { u,v }});
        }
    }

    selectedEdgesK = selEdges;

}

void Graph::printEdgesk() {
    for (auto it : selectedEdgesK) {
        salida << it.second.first.nombre+" - "+it.second.second.nombre+" " << it.first << "\n";
    }
    salida << endl;
}

// --------------------------- Ciclo Hamiltoniano mas corto para las colonias no centrales, Punto 2 ---------------------------------//

void calculaCostoPosible(Nodo &nodoActual, vector<vector<pair<int, Nodo>>> matAdj , int n, vector<bool> visitados){
    salida << "---Costo Posible---\n";
    nodoActual.costopos = nodoActual.costoAcum;
    int costoObtenido;
    for (int i=0; i<n; i++){
        costoObtenido = INT_MAX;
        if (!visitados[i] || i == nodoActual.index){
            //no ha sido visitado
            for (int j=0; j<n; j++){
                if (i != j && (!visitados[j]) || j==0){
                    costoObtenido = min(costoObtenido, matAdj[i][j].first);
                    //salida << matAdj[i][j].second.nombre + " " << costoObtenido << "\n";
                }
            }

        }
        else{ //es el nodo actual
            for (int j=0; j<n; j++){
                if(!visitados[j]){
                    costoObtenido = min(costoObtenido, matAdj[i][j].first);
                    //salida << matAdj[i][j].second.index + "" << costoObtenido << "\n";
                }
            }
        }
        nodoActual.costopos += costoObtenido;
    }
    salida << "------------\n";
}

void Graph::shortestRoute() {

    int costoOptimo = INT_MAX;
    vector<vector<pair<int, Nodo>>> mat = adjList;
    vector<bool> visitados = vector<bool>(V, 0);
    int primerIndex = noCentrales[0].index;

    
    //cambiar el primer nodo no central con el primer nodo en la lista de adyacencias
    mat[0] = adjList[primerIndex];
    mat[primerIndex] = adjList[0];
    mat[0][0] = adjList[primerIndex][primerIndex];
    mat[0][0].second.index = 0;
    mat[0][primerIndex] = adjList[primerIndex][0];
    mat[0][primerIndex].second.index = primerIndex;
    primerIndex = 0;

    visitados[primerIndex] = 1;

    calculaCostoPosible(mat[primerIndex][primerIndex].second, mat, V, visitados);
    salida << mat[primerIndex][primerIndex].second.nombre + " " << mat[primerIndex][primerIndex].second.costopos << "\n";
    priority_queue<Nodo> pq;
    pq.push(mat[primerIndex][primerIndex].second);
    for(int i=0; i<V; i++){
        if(mat[primerIndex][i].second.index!=primerIndex){
            //visitados[adjList[primerIndex][i].second.index] = 1;
            calculaCostoPosible(mat[primerIndex][i].second, mat, V, visitados);
            mat[primerIndex][i].second.costopos+=mat[primerIndex][i].first;
            salida << mat[primerIndex][i].second.nombre + " " << mat[primerIndex][i].second.costopos << "\n";
        }
    }
    // while(!pq.empty()){
    //     pq.pop();
    //     for(int i=0; i<V; i++){
    //         if(adjList[primerIndex][i].second.index!=primerIndex){
    //             calculaCostoPosible(adjList[primerIndex][i].second, matAdj, V, visitados);   
    //         }
    //     }
    // }
    
}

// --------------------------- Floyd, Punto 3 ---------------------------------//

void leeArcos(int mat[MAX][MAX], int p[MAX][MAX], int m) {
    for (int i = 0; i < MAX; i++) {
        mat[i][i] = p[i][i] = 0;
        for (int j = i + 1; j < MAX; j++) {
            mat[i][j] = mat[j][i] = INT_MAX;
            p[i][j] = p[j][i] = -1;
        }
    }
}

// Complejidad: O(n^3)
void floyd(int mat[MAX][MAX], int p[MAX][MAX], int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][k] != INT_MAX && mat[k][j] != INT_MAX && mat[i][k] + mat[k][j] < mat[i][j]) {
                    mat[i][j] = mat[i][k] + mat[k][j];
                    p[i][j] = k;
                }
            }
        }
    }
}

void print(int mat[MAX][MAX], int p[MAX][MAX], int n) {
    salida << "La matriz de costos" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            salida << mat[i][j] << "\t";
        }
        salida << endl;
    }
    salida << "La matriz de Trayectoria" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            salida << p[i][j] << "\t";
        }
        salida << endl;
    }
}

void checarTrayectoria(int p[MAX][MAX], int a, int b, unordered_map<string, Nodo> um) {
    
    if (p[a][b] != -1) {
        checarTrayectoria(p, a, p[a][b], um);
        for (auto it = um.begin(); it != um.end(); ++it) {
            if (it->second.index == (p[a][b])) {
                salida << it->first << " - ";

            }
        }
        checarTrayectoria(p, p[a][b], b, um);
    } 
}

void consultas(int mat[MAX][MAX], int p[MAX][MAX], int q, vector<int> cent, unordered_map<string, Nodo> um) {
    for (int i = 0; i < cent.size(); i++) {
        for (int j = i + 1; j < cent.size(); j++) {
            int a = cent.at(i);
            int b = cent.at(j);
            if (mat[a][b] == INT_MAX) {
                salida << "no path" << endl;
            }
            else {
                for (auto it2 = um.begin(); it2 != um.end(); ++it2) {
                    if (it2->second.index == a) {
                        salida << it2->first << " - ";
                        checarTrayectoria(p, a, b, um);
                    }
                    else if (it2->second.index == b) {
                        salida << it2->first << " (" << mat[a][b] << ") " << endl;
                    }
                }
            }
        }
    }
}

// --------------------------- Distancia 2 puntos, Punto 4 ---------------------------------//

int closest(const Nodo &punto, vector<Nodo> conectadas) {
    // Ordenar con respecto al eje X
    sort(conectadas.begin(), conectadas.end(), 
        [punto](const Nodo &a, const Nodo &b) -> bool{
            return (punto.x-a.x)*(punto.x-a.x)+(punto.y-a.y)*(punto.y-a.y) < (punto.x-b.x)*(punto.x-b.x)+(punto.y-b.y)*(punto.y-b.y);
        });
    return conectadas[0].index;
}

int main() {
    unordered_map<string, Nodo> um;
    unordered_map<string, Nodo> newUm;
    vector<int> central;
    vector<Nodo> colonias;
    vector<Nodo> coloniasNoConectadas;
    string a, b;
    int mat[MAX][MAX];
    int p[MAX][MAX];
    int cont = 0;
    string nconection1, nconection2;
    int c;
    string lugar;
    int V, E, C;
    cin >> V >> E >> C;
    Graph g(V, E);
    Nodo n;

    for (int i = 0; i < V; i++) {
        cin >> n.nombre;
        n.index = i;
        cin >> n.x >> n.y >> n.central;
        um.emplace(n.nombre, n);
        colonias.push_back(n);
        if (n.central == 1) {       
            cont++;
            central.push_back(n.index);
        }
    }

    leeArcos(mat, p, E);
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> c;
        g.addEdge(um[a], um[b], c);
        mat[um[a].index][um[b].index] = mat[um[b].index][um[a].index] = c;
    }
    floyd(mat, p, V);

    Nodo nuevaColonia;
    for (int i = 0; i < C; i++) {
        cin >> nuevaColonia.nombre;
        cin >> nuevaColonia.x >> nuevaColonia.y;
        coloniasNoConectadas.push_back(nuevaColonia);
    }

    salida << "\n-------------------";
    salida << "\n1 - Cableado optimo de nueva conexion." << endl << endl;
    g.printEdgesk();
    salida << "Costo Total = " << g.costMSTKruskal << endl;

    salida << "\n2 - Problema del viajero" << endl << endl;
    g.shortestRoute();

    salida << "\n-------------------";
    salida << "\n3 - Caminos mas cortos entre centrales" << endl << endl;
    consultas(mat, p, cont, central, um);

    salida << "\n-------------------";
    salida << "\n4 - Conexion de nuevas colonias." << endl << endl;
    for (auto it : coloniasNoConectadas) {
        salida << it.nombre +" debe conectarse con "+colonias[closest(it, colonias)].nombre+"\n";
    }

    return 0;
}

/*

9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7

//Crear un struct para guardar los nombres 

5 8 2
//kruscal
ciudad = sorce
destination, peso, central
LindaVista 200 120 1
Purisima 150 75 0
Tecnologico -50 20 1
Roma -75 50 0
AltaVista -50 40 0

//viajero
LindaVista Purisima 48
LindaVista Roma 17
Purisima Tecnologico 40
Purisima Roma 50
Purisima AltaVista 80
Tecnologico Roma 55
Tecnologico AltaVista 15
Roma AltaVista 18

//datos insertados
Independencia 180 -15
Roble 45 68

Lindavista = 0
Purisima = 1
tec = 2
roma = 3
altavista = 4

5 8
0 1 48
0 3 17
1 2 40
1 3 50
1 4 80
2 3 55
2 4 15
3 4 18
90

5 8 2
LindaVista 200 120 1
Purisima 150 75 0
Tecnologico -50 20 1
Roma -75 50 0
AltaVista -50 40 0
LindaVista Purisima 48
LindaVista Roma 17
Purisima Tecnologico 40
Purisima Roma 50
Purisima AltaVista 80
Tecnologico Roma 55
Tecnologico AltaVista 15
Roma AltaVista 18
Independencia 180 -15
Roble 45 68


for (auto it : um) {
    Nodo aux = it.second;
    salida << "\n" << it.first << " " << aux.indice << " " << aux.x << " " << aux.y << endl;
}

    
salida << "Lindavista  = 0" << endl;
salida << "Purisima    = 1" << endl;
salida << "tec         = 2"  << endl;
salida << "roma        = 3" << endl;
salida << "altavista   = 4" << endl << endl;
    
punto 3
1
5 8 2
1 2 48
1 4 17
2 3 40
2 4 50
2 5 80
3 4 55
3 5 15
4 5 18
1 3
Costo: 50 Path: 1-4-5-3
3 1
Costo: 50 Path: 3-5-4-1


0 1 48
0 3 17
1 2 40
1 3 50
1 4 80
2 3 55
2 4 15
3 4 18

10 19 4
Condesa -193 -151 1
DelValle -142 -70 0
Polanco 144 -122 1
RomaNorte -91 -160 1
Pantitlán -108 42 0
Juárez -97 127 1
Tlatelolco -160 12 0
SantaFe 169 -91 1
Cosmopolita 160 -67 1
Merced 78 16 0
Condesa Polanco 27
Condesa Juárez 68
Condesa Cosmopolita 34
DelValle RomaNorte 80
DelValle Pantitlán 68
DelValle SantaFe 94
DelValle Cosmopolita 86
Polanco Juárez 92
Polanco Tlatelolco 58
Polanco Merced 54
RomaNorte Juárez 69
RomaNorte Cosmopolita 25
Pantitlán Juárez 4
Pantitlán SantaFe 67
Pantitlán Cosmopolita 25
Juárez SantaFe 78
Juárez Cosmopolita 29
Tlatelolco Cosmopolita 82
SantaFe Merced 66
FelipeAngeles -64 25
Tlazintla -85 -106
Penitenciaria -99 -83
Porvenir -95 -196

*/