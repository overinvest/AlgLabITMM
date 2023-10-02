#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <queue>
#include "ShortestPathsSolver.h"
#include <locale>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int main() {
    setlocale(LC_ALL, "Russian");
    /*Graph graph = {
        {0, {{1, 10}, {2, 5}}},
        {1, {{0, 7}, {2, 6}}},
        {2, {{3, 15}, {4, 5}, {5, 15}}},
        {3, {{2, 8}, {5, 7}, {6, 20}}},
        {4, {{2, 5}, {5, 9}}},
        {5, {{2, 6}, {4, 10}, {3, 2}, {6, 7}}},
        {6, {{5, 6}, {3, 7}}}
    };*/

    Graph graph = {
        {0, {{1, -10}, {2, 10}}},
        {1, {{2, 10}}},
        {2, {{1, 9}, {3, -9}}},
        {3, {{4, -15}}},
        {4, {{3, 50}}}
    };

    //srand(time(0)); // Инициализация генератора случайных чисел

    //Graph graph;
    //const int num_vertices = 15;

    //for (int i = 0; i < num_vertices; ++i) {
    //    vector<Edge> edges;
    //    for (int j = 0; j < num_vertices; ++j) {
    //        if (i != j) {
    //            int weight = rand() % 50 + 1;
    //            edges.push_back({ j, weight });
    //        }
    //    }
    //    graph[i] = edges;
    //}

    ShortestPathsSolver solver(graph);
    vector<int> dijkstra_distances;
    vector<int> bellman_ford_distances;
    microseconds duration_dijkstra;
    microseconds duration_bellman_ford;

    int start_vertex = 0;

    solver.drawGraph();

    // Создаем первый поток для алгоритма Дейкстры
    thread dijkstra_thread([&]() {
        auto start_dijkstra = high_resolution_clock::now();
        dijkstra_distances = solver.dijkstra(start_vertex);
        auto end_dijkstra = high_resolution_clock::now();
        duration_dijkstra = duration_cast<microseconds>(end_dijkstra - start_dijkstra);
    });

    // Создаем второй поток для алгоритма Форда-Беллмана
    thread bellman_ford_thread([&]() {
        auto start_bellman_ford = high_resolution_clock::now();
        bellman_ford_distances = solver.bellmanFord(start_vertex);
        auto end_bellman_ford = high_resolution_clock::now();
        duration_bellman_ford = duration_cast<microseconds>(end_bellman_ford - start_bellman_ford);
    });

    // Ожидаем завершения выполнения потоков
    dijkstra_thread.join();
    bellman_ford_thread.join();

    cout << "Кратчайшие пути с использованием алгоритма Дейкстры:" << endl;
    for (int i = 0; i < dijkstra_distances.size(); ++i) {
        cout << "До вершины " << i << ": " << dijkstra_distances[i] << endl;
    }
    cout << "Время работы алгоритма Дейкстры: " << duration_dijkstra.count() << " микросекунд" << endl;

    cout << "\nКратчайшие пути с использованием алгоритма Форда-Беллмана:" << endl;
    for (int i = 0; i < bellman_ford_distances.size(); ++i) {
        cout << "До вершины " << i << ": " << bellman_ford_distances[i] << endl;
    }
    cout << "Время работы алгоритма Форда-Беллмана: " << duration_bellman_ford.count() << " микросекунд" << endl;

    return 0;
}
