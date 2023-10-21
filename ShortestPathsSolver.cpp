#include "ShortestPathsSolver.h"

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

        for (const Edge& edge : graph[curr_vertex]) {
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

    for (int i = 0; i < graph.size() - 1; ++i) {
        for (const auto& entry : graph) {
            int u = entry.first;
            for (const Edge& edge : entry.second) {
                int v = edge.target;
                int weight = edge.weight;
                if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }
    }

    // Проверка наличия отрицательных циклов
    for (const auto& entry : graph) {
        int u = entry.first;
        for (const Edge& edge : entry.second) {
            int v = edge.target;
            int weight = edge.weight;
            if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                std::cout << "Граф содержит отрицательный цикл!" << std::endl;
                return {};
            }
        }
    }

    return distances;
}
