//Algoritmo Dijkstra
#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
#include <climits>

using namespace std;

#define INF INT_MAX
#define Edge pair<int, int> //Donde llego y su costo
#define Graph vector<vector<Edge>> //Lista de Adjacencias
#define Vertex pair<int, int>	//Distancia (costo), ID

vector<int> dijkstra(Graph &G, int source) {
	vector<int> dist(G.size(), INF);
	dist[source] = 0;
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> queue;
	Vertex vs(0, source);
	queue.push(vs);
	while (!queue.empty()){
		int u = queue.top().second;
		queue.pop();
		for (int i = 0; i < G[u].size(); i++) {
			Edge e = G[u][i];
			int v = e.first; // Hacia donde llega el arco
			int w = e.second; // Costo del Arco
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				Vertex vtx(dist[v], v);
				queue.push(vtx);
			}
		}
	}
	return dist;
}

int main() {
	int nodes, edges, source, u, v, w;
	cin >> nodes >> edges >> source;
	Graph G(nodes);
	for (int i = 0; i < edges; i++) {
		cin >> u >> v >> w;
		//Edge from u->v cost w
		Edge edge1(v-1, w);
		G[u - 1].push_back(edge1);
		// Edge from v->u cost w
		Edge edge2(u - 1, w);
		G[v - 1].push_back(edge2);
	}
	vector<int> distances = dijkstra(G, source - 1);
	cout << "Distances: " << endl;
	for (int i = 0; i < nodes; i++) {
		if (i != source - 1) {
			cout << source << "-->" << (i + 1) << " : ";
			if (distances[i] == INF){
				cout << "INF" << endl;
			}
			else {
				cout << distances[i] << endl;
			}
		}
	}
}

//Cantidad de nodos, cantidad de arcos, nodo origen
//arcos, punto origen punto destino y costo
/*
5 8 1
1 2 2
1 3 12
1 4 10
2 3 9
2 5 5
3 4 6
3 5 3
4 5 7

5 7 1
1 2 5
1 3 4
1 4 7
2 5 3
3 4 2
3 5 4
4 5 1

4 6 1
1 2 1
1 3 1
1 4 1
2 3 1
2 4 1
3 4 1
*/


