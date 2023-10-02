#include <vector>
#include <map>
#include <limits>
#include <queue>
#include <iostream>

// ��������� ��� ������������� �����
struct Edge {
    int target;
    int weight;
};

// ��� ��� ������������� ����� (������ ���������)
using Graph = std::map<int, std::vector<Edge>>;

class ShortestPathsSolver {
private:
    Graph graph;

public:
    ShortestPathsSolver(const Graph& g) : graph(g) {}

    std::vector<int> dijkstra(int start);

    std::vector<int> bellmanFord(int start);

    void drawGraph() const {
        for (const auto& entry : graph) {
            int u = entry.first;
            std::cout << "������� " << u << " ��������� �: ";
            for (const Edge& edge : entry.second) {
                int v = edge.target;
                int weight = edge.weight;
                std::cout << v << " (��� " << weight << "), ";
            }
            std::cout << std::endl;
        }
    }
};