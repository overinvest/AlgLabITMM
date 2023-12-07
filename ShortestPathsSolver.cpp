#include "ShortestPathsSolver.h"
#include <random>
#include <chrono>
#include <set>
#include <unordered_set>

std::vector<int> ShortestPathsSolver::dijkstra(int start) {
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    distances[start] = 0;

    std::set<std::pair<int, int>> pq;
    pq.insert({ 0, start });

    while (!pq.empty()) {
        int curr_dist = pq.begin()->first;
        int curr_vertex = pq.begin()->second;
        pq.erase(pq.begin());

        for (const Edge& edge : graph[curr_vertex]) {
            int new_dist = curr_dist + edge.weight;
            if (edge.target < distances.size() && new_dist < distances[edge.target]) {
                pq.erase({ distances[edge.target], edge.target });
                distances[edge.target] = new_dist;
                pq.insert({ new_dist, edge.target });
            }
        }
    }

    pq.clear();

    return distances;
}


std::vector<int> ShortestPathsSolver::bellmanFord(int start) {
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    distances[start] = 0;
    std::queue<int> q;
    q.push(start);
    std::vector<bool> in_queue(graph.size(), false);
    in_queue[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (const Edge& edge : graph[u]) {
            int v = edge.target;
            int weight = edge.weight;
            if (distances[u] != std::numeric_limits<int>::max() && v < distances.size() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }

    /*for (int u = 0; u < graph.size(); ++u) {
        for (const Edge& edge : graph[u]) {
            int v = edge.target;
            int weight = edge.weight;
            if (distances[u] != std::numeric_limits<int>::max() && v < distances.size() && distances[u] + weight < distances[v]) {
                std::cout << "Граф содержит отрицательный цикл!" << std::endl;
                return {};
            }
        }
    }*/

    return distances;
}


void ShortestPathsSolver::CreateGraph(int n, int m, int q, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(q, r);

    graph.clear();
    for (int i = 0; i < n; ++i) {
        std::vector<Edge> edges;
        edges.reserve(m);
        for (int j = 0; j < m; ++j) {
            int weight = dis(gen);
            edges.emplace_back(Edge{ j, weight });
        }
        graph[i] = std::move(edges);
        edges.clear();
    }
}





