#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Representasi graf menggunakan adjacency list
typedef pair<int, int> pii; // pasangan (node, weight)
typedef vector<vector<pii>> Graph;

// Fungsi untuk mengimplementasikan algoritma Dijkstra
void dijkstra(const Graph& graph, int start, vector<int>& distance, vector<int>& parent) {
    int n = graph.size();
    distance.assign(n, INF);
    parent.assign(n, -1);

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    distance[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > distance[u]) {
            continue; // Skip jika sudah ada jalur lebih pendek ke u
        }

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
}

// Fungsi untuk mencetak jalur terpendek dari start ke target
void printShortestPath(const vector<int>& parent, int target) {
    if (parent[target] == -1) {
        cout << "Tidak ada jalur ke " << target << endl;
        return;
    }

    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    cout << "Jalur terpendek: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
        if (i > 0) {
            cout << " -> ";
        }
    }
    cout << endl;
}

// Fungsi untuk mencetak representasi graf ke layar
void printGraph(const Graph& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        cout << "Node " << i << ": ";
        for (const auto& neighbor : graph[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

int main() {
    // Contoh penggunaan algoritma Dijkstra
    int n = 6; // Jumlah node dalam graf
    Graph graph(n);

    // Menambahkan edge dan bobotnya
    graph[0].push_back({1, 2});
    graph[0].push_back({2, 4});
    graph[1].push_back({2, 1});
    graph[1].push_back({3, 7});
    graph[2].push_back({4, 3});
    graph[3].push_back({5, 1});
    graph[4].push_back({5, 5});

    // Menampilkan representasi graf
    cout << "Representasi Graf:" << endl;
    printGraph(graph);

    int startNode = 0; // Node awal
    vector<int> distance, parent;
    dijkstra(graph, startNode, distance, parent);

    // Menampilkan jarak terpendek dari startNode ke semua node
    cout << "\nJarak terpendek dari " << startNode << " ke node lain:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << distance[i] << endl;
    }

    // Memilih hingga 3 tujuan
    cout << "\nMemilih tujuan (maksimal 3): ";
    vector<int> targetNodes;
    for (int i = 0; i < 3; ++i) {
        int targetNode;
        cin >> targetNode;
        targetNodes.push_back(targetNode);
    }

    // Menampilkan jalur terpendek ke setiap tujuan
    for (int targetNode : targetNodes) {
        cout << "\nJalur terpendek ke " << targetNode << ":" << endl;
        printShortestPath(parent, targetNode);
    }

    return 0;
}
