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
            if (distances[u] == std::numeric_limits<int>::max()) continue; // Skip unreachable nodes
            for (const Edge& edge : entry.second) {
                int v = edge.target;
                int weight = edge.weight;
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }
    }

    // Проверка наличия отрицательных циклов
    for (const auto& entry : graph) {
        int u = entry.first;
        if (distances[u] == std::numeric_limits<int>::max()) continue; // Skip unreachable nodes
        for (const Edge& edge : entry.second) {
            int v = edge.target;
            int weight = edge.weight;
            if (distances[u] + weight < distances[v]) {
                std::cout << "Граф содержит отрицательный цикл!" << std::endl;
                return {};
            }
        }
    }

    return distances;
}

std::vector<int> ShortestPathsSolver::dijkstraParallel(int start) {
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    distances[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({ 0, start });

#pragma omp parallel
    {
        while (true) {
            int curr_dist, curr_vertex;

#pragma omp critical (pq_access)
            {
                if (pq.empty()) break;

                curr_dist = pq.top().first;
                curr_vertex = pq.top().second;
                pq.pop();
            }

            if (curr_dist > distances[curr_vertex])
                continue;

            for (int i = 0; i < graph[curr_vertex].size(); ++i) {
                Edge edge = graph[curr_vertex][i];
                int new_dist = curr_dist + edge.weight;

                if (new_dist < distances[edge.target]) {
                    distances[edge.target] = new_dist;

#pragma omp critical (pq_insert)
                    {
                        pq.push({ new_dist, edge.target });
                    }
                }
            }
        }
    }

    return distances;
}

std::vector<int> ShortestPathsSolver::bellmanFordParallel(int start) {
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    distances[start] = 0;

#pragma omp parallel
    {
        for (int k = 0; k < graph.size() - 1; ++k) {
#pragma omp for
            for (const auto& entry : graph) {
                int u = entry.first;

                if (distances[u] == std::numeric_limits<int>::max()) continue; // Skip unreachable nodes

                for (const Edge& edge : entry.second) {
                    int v = edge.target;
                    int weight = edge.weight;

                    if (distances[u] + weight < distances[v]) {
#pragma omp critical
                        {
                            distances[v] = distances[u] + weight;
                        }
                    }
                }
            }
        }
    }

    // Проверка наличия отрицательных циклов
#pragma omp parallel
    {
#pragma omp for
        for (const auto& entry : graph) {
            int u = entry.first;

            if (distances[u] == std::numeric_limits<int>::max()) continue; // Skip unreachable nodes

            for (const Edge& edge : entry.second) {
                int v = edge.target;
                int weight = edge.weight;

                if (distances[u] + weight < distances[v]) {
#pragma omp critical
                    {
                        std::cout << "Граф содержит отрицательный цикл!" << std::endl;
                    }
                }
            }
        }
    }

    return distances;
}
