#include <vector>
#include <map>
#include <limits>
#include <queue>
#include <iostream>
#include <omp.h>

// Структура для представления ребра
struct Edge {
    int target;
    int weight;
};

// Тип для представления графа (список смежности)
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
        std::cout << "Граф:" << std::endl;
        for (const auto& entry : graph) {
            int u = entry.first;
            std::cout << "Вершина " << u << " соединена с: ";
            for (const Edge& edge : entry.second) {
                int v = edge.target;
                int weight = edge.weight;
                std::cout << v << " (вес " << weight << "), ";
            }
            std::cout << std::endl;
        }
    }

    // Функция для добавления ребра в граф
    void addEdge(int u, int v, int weight) {
        Edge edge = { v, weight };
        graph[u].push_back(edge);
    }


    // Функция для ввода графа с клавиатуры
    void inputGraph() {
        int vertices, edges;
        std::cout << "Введите количество вершин: ";
        std::cin >> vertices;
        std::cout << "Введите количество ребер: ";
        std::cin >> edges;

        for (int i = 0; i < vertices; ++i) {
            graph[i] = std::vector<Edge>();
        }

        for (int i = 0; i < edges; ++i) {
            int u, v, weight;
            std::cout << "Введите вершину начала, вершину конца и вес ребра: ";
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