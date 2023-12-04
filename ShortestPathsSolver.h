#include <vector>
#include <map>
#include <limits>
#include <queue>
#include <iostream>
#include <omp.h>

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

    ShortestPathsSolver() {}

    void setGraph(const Graph& g) {
        graph = g;
    }

    void clearGraph() {
        graph.clear();
    }

    std::vector<int> dijkstra(int start);
    std::vector<int> bellmanFord(int start);

    void drawGraph() const {
        std::cout << "����:" << std::endl;
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

    // ������� ��� ���������� ����� � ����
    void addEdge(int u, int v, int weight) {
        Edge edge = { v, weight };
        graph[u].push_back(edge);
    }


    // ������� ��� ����� ����� � ����������
    void inputGraph() {
        int vertices, edges;
        std::cout << "������� ���������� ������: ";
        std::cin >> vertices;
        std::cout << "������� ���������� �����: ";
        std::cin >> edges;

        for (int i = 0; i < vertices; ++i) {
            graph[i] = std::vector<Edge>();
        }

        for (int i = 0; i < edges; ++i) {
            int u, v, weight;
            std::cout << "������� ������� ������, ������� ����� � ��� �����: ";
            std::cin >> u >> v >> weight;
            addEdge(u, v, weight);
        }
    }

};

//0 1 1
//1 2 2
//0 3 3
//1 4 4
//3 4 1
//4 5 3
//2 5 1