#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

class Graph {
int V;
vector<int>* adj;
public:
Graph(int V);
void addEdge(int v, int w);
void parallelBFS(int s);
void parallelDFS(int s);
};

Graph::Graph(int V) {
this->V = V;
adj = new vector<int>[V];
}
void Graph::addEdge(int v, int w) {
adj[v].push_back(w);
adj[w].push_back(v);
}


void Graph::parallelBFS(int s) {
bool* visited = new bool[V];
for (int i = 0; i < V; i++) {
visited[i] = false;
}
queue<int> q;
visited[s] = true;
q.push(s);
while (!q.empty()) {
s = q.front();
cout << s << " ";
q.pop();
#pragma omp parallel for
for (size_t i = 0; i < adj[s].size(); ++i) {
    int neighbor = adj[s][i];
    if (!visited[neighbor]) {
        visited[neighbor] = true;
        q.push(neighbor);
    }
}

}
}

void Graph::parallelDFS(int s) {
bool* visited = new bool[V];
for (int i = 0; i < V; i++) {
visited[i] = false;
}
stack<int> st;
st.push(s);

while (!st.empty()) {
s = st.top();
st.pop();
if (!visited[s]) {
cout << s << " ";
visited[s] = true;
}
#pragma omp parallel for
for (size_t i = 0; i < adj[s].size(); ++i) {
    int neighbor = adj[s][i];
    if (!visited[neighbor]) {
        st.push(neighbor);
    }
}

}
}
int main() {
int n;
cout << "Enter the number of vertices: ";
cin >> n;
Graph g(n);
int e;
cout << "Enter the number of edges: ";
cin >> e;
for (int i = 0; i < e; i++) {
int a, b;
cout << "Enter the vertices of edge (space separated):" << i + 1 << ": ";
cin >> a >> b;
g.addEdge(a, b);
}
cout << "Parallel Breadth First Traversal:\n";
g.parallelBFS(0);
cout << "\nParallel Depth First Traversal:\n";
g.parallelDFS(0);
return 0;
}