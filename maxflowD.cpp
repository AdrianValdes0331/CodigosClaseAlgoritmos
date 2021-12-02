//Adrian Valdes
//A01720439
// C++ implementation of Dinic's Algorithm
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//Declaramos las variables como Edge
struct Edge{
    int v;   
    int flow;
    int C;   
    int rev ; 
};
 

class Graph{
    int V; 
    int *level ; 
    vector< Edge > *adj;
public :
    //Construimos la grafica
    Graph(int V){
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }
 
    void addEdge(int u, int v, int C){
        int tam = adj[v].size();
        Edge a{v, 0, C, tam};
        tam = adj[u].size();
        Edge b{u, 0, 0, tam};
        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }
    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};
 
//Empesamos dandole etiqueta cero al vertice de arranque
//Mientras la lista de espera no esta vacia
//La funcion BFS se encarga de ir etiquetando los niveles
//de cada vertice por medio de la busqueda de anchura, es decir, BFS
bool Graph::BFS(int s, int t){
    for (int i = 0 ; i < V ; i++)
        level[i] = -1;
    level[s] = 0;  
    queue< int > q;
    q.push(s);
 
    vector<Edge>::iterator i ;
    while (!q.empty()){
        //u es el primer elemento de la lista de espera
        int u = q.front();
        //quitamos el elemento mas viejo
        q.pop();
        for (i = adj[u].begin(); i != adj[u].end(); i++){
            Edge &e = *i;
            if (level[e.v] < 0  && e.flow < e.C){
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] < 0 ? false : true ;
}
 
//no queremos que los arcos vayan a 2 vertices del mismo nivel
//Se cancelan los arcos que vayan en el mismo nivel 
//Despues se sacan los flujos actuales y se van
//poniendo los flujos residuales temporalmente hasta que termina, repitiendo
//El proceso con los residuos y poniendo los valores en el lado opuesto
int Graph::sendFlow(int u, int flow, int t, int start[]){
    // Sink reached
    if (u == t){
        return flow;
    }
    for (  ; start[u] < adj[u].size(); start[u]++){
        Edge &e = adj[u][start[u]];                                    
        if (level[e.v] == level[u]+1 && e.flow < e.C){
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            if (temp_flow > 0){
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}
 
//Iniciamos el total con cero
//Revisa que no s y t no sean iguales
//mientras sea cierto que se puede alcanzar 
//el vertice final desde el inicial usando la funcion 
//BSF, va actualizando la variable totalcon la suma
//del flujo y al final regresa maxflow como total
int Graph::DinicMaxflow(int s, int t){
    // Corner case
    if (s == t)
        return -1;
 
    int total = 0;   
    while (BFS(s, t) == true){
        int *start = new int[V+1] {0};
        while (int flow = sendFlow(s, INT_MAX, t, start)){
            total += flow;
        }
    }
    return total;
}
 
//Tomamos los inputs y los vamos mandando a
//la funcion addEdge en la clase graph
//Manda a llamar a la funcion MaxFlow con el algoritmo de Dinic
//y al terminar imprime el texto pre-definido + la variable total
//Regresada por la funcion llamada.
int main(){
    int n, m, s, t, a, b, c;
    cin >> n >> m >> s >> t;
    Graph g(n);
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        g.addEdge(a-1, b-1, c);
    }
    cout << "The Maximum speed is " << g.DinicMaxflow(s-1, t-1) << "." << endl;
    return 0;
}
/*
7 11
1 7
1 2 10
1 3 15
1 4 20
2 3  5
2 5 10
3 4 10
3 5 12
4 5 10
4 6 10
5 7 50
6 7 10
*/