#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <queue>
#include "ShortestPathsSolver.h"
#include <locale>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

Graph generateGraph(int n, int m, int q, int r) {
    Graph graph;

    for (int i = 0; i < n; ++i) {
        vector<Edge> edges;
        for (int j = 0; j < m; ++j) {
            if (i != j && edges.size() < n - 1) { // Ensure edges for a vertex don't exceed n - 1
                int weight = rand() % r + q;
                edges.push_back({ j, weight });
            }
        }
        graph[i] = edges;
    }

    return graph;
}

void saveResultsToFile(vector<int>& n_values, vector<double>& time_a, vector<double>& time_b, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (size_t i = 0; i < n_values.size(); ++i) {
            file << n_values[i] << " " << time_a[i] << " " << time_b[i] << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }
}



void experiment_1() {
    cout << "Experiment 1" << endl;
    const int q = 1;
    const int r = 1000000;

    vector<int> n_values;
    vector<double> times_a_dijkstra;
    vector<double> times_b_dijkstra;

    vector<double> times_a_bellman;
    vector<double> times_b_bellman;

    ShortestPathsSolver solver_a;
    ShortestPathsSolver solver_b;

    high_resolution_clock::time_point start_time, end_time;

    for (int n = 1; n <= 10001; n += 100) {
        const int m_a = n * n / 10;
        const int m_b = n * n;

        Graph graph_a = generateGraph(n, m_a, q, r);
        Graph graph_b = generateGraph(n, m_b, q, r);

        solver_a.setGraph(graph_a);
        solver_b.setGraph(graph_b);

        // Dijkstra
        start_time = high_resolution_clock::now();
        vector<int> distances_a;
        distances_a.reserve(n); // Предварительное выделение памяти
        distances_a = solver_a.dijkstra(0);
        end_time = high_resolution_clock::now();
        duration<double> time_a = end_time - start_time;

        // Bellman-Ford
        start_time = high_resolution_clock::now();
        vector<int> distances_a_bellman;
        distances_a_bellman.reserve(n); // Предварительное выделение памяти
        distances_a_bellman = solver_a.bellmanFord(0);
        end_time = high_resolution_clock::now();
        duration<double> time_a_bellman = end_time - start_time;

        // Dijkstra
        start_time = high_resolution_clock::now();
        vector<int> distances_b;
        distances_b.reserve(n); // Предварительное выделение памяти
        distances_b = solver_b.dijkstra(0);
        end_time = high_resolution_clock::now();
        duration<double> time_b = end_time - start_time;

        // Bellman-Ford
        start_time = high_resolution_clock::now();
        vector<int> distances_b_bellman;
        distances_b_bellman.reserve(n); // Предварительное выделение памяти
        distances_b_bellman = solver_b.bellmanFord(0);
        end_time = high_resolution_clock::now();
        duration<double> time_b_bellman = end_time - start_time;

        double time_dijkstra_a = time_a.count();
        double time_dijkstra_b = time_b.count();
        double time_bellman_a = time_a_bellman.count();
        double time_bellman_b = time_b_bellman.count();

        cout << "n = " << n << ", m_a = " << m_a << ", m_b = " << m_b << endl;
        cout << "Dijkstra (m = n^2/10): " << fixed << setprecision(9) << time_dijkstra_a << " seconds" << endl;
        cout << "Dijkstra (m = n^2): " << time_dijkstra_b << " seconds" << endl;
        cout << "Bellman (m = n^2/10): " << time_bellman_a << " seconds" << endl;
        cout << "Bellman (m = n^2): " << time_bellman_b << " seconds" << endl;

        n_values.push_back(n);
        times_a_dijkstra.push_back(time_dijkstra_a);
        times_b_dijkstra.push_back(time_dijkstra_b);
        times_a_bellman.push_back(time_bellman_a);
        times_b_bellman.push_back(time_bellman_b);

        // Очистка памяти
        distances_a.clear();
        distances_a_bellman.clear();
        distances_b.clear();
        distances_b_bellman.clear();
        solver_a.clearGraph();
        solver_b.clearGraph();
    }

    saveResultsToFile(n_values, times_a_dijkstra, times_b_dijkstra, "Experiment_1_Dijkstra.txt");
    saveResultsToFile(n_values, times_a_bellman, times_b_bellman, "Experiment_1_Bellman.txt");
}




int main() {
    setlocale(LC_ALL, "Russian");
    Graph graph = {
        {0, {{1, 10}, {2, 5}}},
        {1, {{0, 7}, {2, 6}}},
        {2, {{3, 15}, {4, 5}, {5, 15}}},
        {3, {{2, 8}, {5, 7}, {6, 20}}},
        {4, {{2, 5}, {5, 9}}},
        {5, {{2, 6}, {4, 10}, {3, 2}, {6, 7}}},
        {6, {{5, 6}, {3, 7}}}
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


    auto start_dijkstra = high_resolution_clock::now();
    dijkstra_distances = solver.dijkstra(start_vertex);
    auto end_dijkstra = high_resolution_clock::now();
    duration_dijkstra = duration_cast<microseconds>(end_dijkstra - start_dijkstra);

    auto start_bellman_ford = high_resolution_clock::now();
    bellman_ford_distances = solver.bellmanFord(start_vertex);
    auto end_bellman_ford = high_resolution_clock::now();
    duration_bellman_ford = duration_cast<microseconds>(end_bellman_ford - start_bellman_ford);

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

    experiment_1();

    return 0;
}
