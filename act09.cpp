//Adrian Valdes Zavala
//A01720439
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

//Complejidad: O(n log n)
vector<int> dijkstra(Graph &G, int source) {
	vector<int> dist(G.size(), INF);
	dist[source] = 0;
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> queue;
	Vertex vs(0, source);
	queue.push(vs);
	while (!queue.empty()) {
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
	int n;
	int cont = 0;
	int val = 0;
	cin >> n;
	while (n--) {
		int contt = 0;
		cont++;
		int nodes, edges, source, w;
		int nu, nv;
		char u, v;
		vector<char> Alphabet = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		cin >> nodes >> edges;
		source = 1;
		Graph G(nodes);
		for (int i = 0; i < edges; i++) {
			cin >> u >> v >> w;

			nu = int(u)-64;
			nv = int(v)-64;
			
			Edge edge1(nv - 1, w);
			G[nu - 1].push_back(edge1);
			// Edge from v->u cost w
			Edge edge2(nu - 1, w);
			G[nv - 1].push_back(edge2);
		}
		vector<int> distances = dijkstra(G, source - 1);
		for (int i = 0; i < nodes; i++) {
			if (i != source - 1) {
				//cout << source << "-->" << (i + 1) << " : ";
				if (distances[i] == INF) {
					cout << "INF" << endl;
				}
				if (contt == 0) {
					val = distances[i];
					contt++;
				}
				else {
					if (distances[i] < val) {
						val = distances[i];
					}
				}
			}
		}
		cout << "Case " << cont << ": " << Alphabet[val] << endl;
	}
}

//Casos De Prueba
/*
2
5 7 
A B 5
A C 4
A D 7
B E 3
C D 2
C E 4
D E 1
4 6 
A B 1
A C 1
A D 1
B C 1
B D 1
C D 1
==>Case 1: E
==>Case 2: B

1
6 7
A B 5
A C 4
A F 7
B E 3
C D 2
C E 4
D E 3
==> Case 1: E

3
5 7
A B 5
A C 1
A D 3
B E 3
C D 6
C E 4
D E 4
5 7
A B 5
A C 6
A D 5
B E 4
C D 3
C E 2
D E 1
5 7
A B 1
A C 1
A D 2
B E 2
C D 2
C E 4
D E 1
==> Case 1: B
==> Case 2: F
==> Case 3: B

1
4 6
A B 2
A C 2
A D 2
B C 2
B D 2
C D 2
==> Case 1: C
*/