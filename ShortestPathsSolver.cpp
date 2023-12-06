#include "ShortestPathsSolver.h"
#include <random>
#include <chrono>
#include <set>

std::vector<int> ShortestPathsSolver::dijkstra(int start) {
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    distances[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int curr_vertex = pq.top().second;
        pq.pop();

        if (curr_dist > distances[curr_vertex])
            continue;

        if (curr_vertex >= graph.size())
            continue;

        for (const Edge& edge : graph[curr_vertex]) {
            if (edge.target >= graph.size())
                continue;

            int new_dist = curr_dist + edge.weight;
            if (new_dist < distances[edge.target]) {
                distances[edge.target] = new_dist;
                pq.push({ new_dist, edge.target });
            }
        }
    }

    return distances;
}


std::vector<int> ShortestPathsSolver::bellmanFord(int start) {
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    distances[start] = 0;
    std::queue<int> q1, q2;
    std::queue<int>* q = &q1;
    std::queue<int>* next = &q2;
    q->push(start);

    for (int i = 0; i < graph.size() - 1; ++i) {
        while (!q->empty()) {
            int u = q->front();
            q->pop();
            if (distances[u] == std::numeric_limits<int>::max()) continue; // Skip unreachable nodes

            if (u >= graph.size())
                continue;

            for (const Edge& edge : graph[u]) {
                int v = edge.target;
                int weight = edge.weight;
                if (v >= graph.size())
                    continue;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    next->push(v);
                }
            }
        }
        std::swap(q, next);
        while (!next->empty()) next->pop(); // Clear the 'next' queue
    }

    // Проверка наличия отрицательных циклов
    for (const auto& entry : graph) {
        int u = entry.first;

        if (u >= graph.size())
            continue;

        if (distances[u] == std::numeric_limits<int>::max()) continue; // Skip unreachable nodes
        for (const Edge& edge : entry.second) {
            int v = edge.target;
            int weight = edge.weight;
            if (v >= graph.size())
                continue;

            if (distances[u] + weight < distances[v]) {
                std::cout << "Граф содержит отрицательный цикл!" << std::endl;
                return {};
            }
        }
    }

    return distances;
}

void ShortestPathsSolver::CreateGraph(int n, int m, int q, int r) {
    for (int i = 0; i < n; ++i) {
        graph[i] = std::vector<Edge>();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(q, r);

    for (int i = 0; i < n; ++i) {
        std::vector<Edge> edges;
        for (int j = 0; j < m; ++j) {
            if (i != j) { // Убедитесь, что ребра для вершины не превышают n - 1
                int weight = dis(gen);
                edges.push_back({ j, weight });
            }
        }
        graph[i] = edges;
    }

}


