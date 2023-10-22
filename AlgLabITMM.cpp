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
#include <functional>

using namespace std;
using namespace std::chrono;

Graph generateGraph(int n, int m, int q, int r) {
    Graph graph;

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        vector<Edge> edges;
        for (int j = 0; j < m; ++j) {
            if (i != j && edges.size() < n - 1) { // Ensure edges for a vertex don't exceed n - 1
                int weight = rand() % r + q;
                edges.push_back({ j, weight });
            }
        }

#pragma omp critical
        {
            graph[i] = edges;
        }
    }

    return graph;
}


// Функция для преобразования времени в строку
std::string timeToString(const std::chrono::system_clock::time_point& timePoint) {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm tmInfo;
    localtime_s(&tmInfo, &time);

    // Форматирование времени в строку
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &tmInfo);
    return std::string(buffer);
}

void saveResultsToFile(const std::vector<int>& n_values, vector<double>& time_a, vector<double>& time_b, const string& filename) {

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


void experiment_1_d() {
    cout << "Experiment 1 Djikstra" << endl;
    const int q = 1;
    const int r = 1000000;

    vector<int> n_values;
    vector<double> times_a_dijkstra;
    vector<double> times_b_dijkstra;

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

        // Dijkstra
        start_time = high_resolution_clock::now();
        vector<int> distances_b;
        distances_b.reserve(n); // Предварительное выделение памяти
        distances_b = solver_b.dijkstra(0);
        end_time = high_resolution_clock::now();
        duration<double> time_b = end_time - start_time;

        double time_dijkstra_a = time_a.count();
        double time_dijkstra_b = time_b.count();


        cout << "n = " << n << ", m_a = " << m_a << ", m_b = " << m_b << endl;
        cout << "Dijkstra (m = n^2/10): " << fixed << setprecision(9) << time_dijkstra_a << " seconds" << endl;
        cout << "Dijkstra (m = n^2): " << time_dijkstra_b << " seconds" << endl;

        n_values.push_back(n);
        times_a_dijkstra.push_back(time_dijkstra_a);
        times_b_dijkstra.push_back(time_dijkstra_b);


        // Очистка памяти
        distances_a.clear();
        distances_b.clear();
        solver_a.clearGraph();
        solver_b.clearGraph();
    }

    saveResultsToFile(n_values, times_a_dijkstra, times_b_dijkstra, "Experiment_1_Dijkstra.txt");
}

void experiment_1_b() {
    cout << "Experiment 1 Bellman" << endl;
    const int q = 1;
    const int r = 1000000;

    vector<int> n_values;

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


        // Bellman-Ford
        start_time = high_resolution_clock::now();
        vector<int> distances_a_bellman;
        distances_a_bellman.reserve(n); // Предварительное выделение памяти
        distances_a_bellman = solver_a.bellmanFord(0);
        end_time = high_resolution_clock::now();
        duration<double> time_a_bellman = end_time - start_time;

        // Bellman-Ford
        start_time = high_resolution_clock::now();
        vector<int> distances_b_bellman;
        distances_b_bellman.reserve(n); // Предварительное выделение памяти
        distances_b_bellman = solver_b.bellmanFord(0);
        end_time = high_resolution_clock::now();
        duration<double> time_b_bellman = end_time - start_time;

        double time_bellman_a = time_a_bellman.count();
        double time_bellman_b = time_b_bellman.count();

        cout << "n = " << n << ", m_a = " << m_a << ", m_b = " << m_b << endl;
        cout << "Bellman (m = n^2/10): " << fixed << setprecision(9) << time_bellman_a << " seconds" << endl;
        cout << "Bellman (m = n^2): " << time_bellman_b << " seconds" << endl;

        n_values.push_back(n);
        times_a_bellman.push_back(time_bellman_a);
        times_b_bellman.push_back(time_bellman_b);

        // Очистка памяти
        distances_a_bellman.clear();
        distances_b_bellman.clear();
        solver_a.clearGraph();
        solver_b.clearGraph();
    }

    saveResultsToFile(n_values, times_a_bellman, times_b_bellman, "Experiment_1_Bellman.txt");
}

void experiment(const std::vector<int>& n_values, std::function<int(int)> m_func, int q, int r, const std::string& experiment_name) {
    std::vector<double> times_dijkstra(n_values.size(), 0.0); // Локальные времена для каждого потока
    std::vector<double> times_bellman(n_values.size(), 0.0);

    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::string timeString = timeToString(currentTime);
    cout << "[" << timeString << "] Start " << experiment_name << "\n";

    // Убираем общие переменные для обоих солверов из разделяемой области
#pragma omp parallel
    {
        ShortestPathsSolver solver_a, solver_b;

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < n_values.size(); ++i) {
            int n = n_values[i];
            int m_a = m_func(n);
            auto graph_a = generateGraph(n, m_a, q, r);

            auto start_time = std::chrono::high_resolution_clock::now();
            solver_a.setGraph(graph_a);
            solver_a.dijkstraParallel(0);
            auto end_time = std::chrono::high_resolution_clock::now();
            times_dijkstra[i] = std::chrono::duration<double>(end_time - start_time).count();

            // Локальные выводы для каждого потока
            #pragma omp critical
            {
                cout << "[" << experiment_name << "] dijkstra data n = " << n << " m = " << m_a << " time = " << times_dijkstra[i] << "\n";
            }
        }

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < n_values.size(); ++i) {
            int n = n_values[i];
            int m_a = m_func(n);
            auto graph_a = generateGraph(n, m_a, q, r);

            auto start_time = std::chrono::high_resolution_clock::now();
            solver_b.setGraph(graph_a);
            solver_b.bellmanFordParallel(0);
            auto end_time = std::chrono::high_resolution_clock::now();
            times_bellman[i] = std::chrono::duration<double>(end_time - start_time).count();

            // Локальные выводы для каждого потока
            #pragma omp critical
            {

                cout << "[" << experiment_name << "] bellman data n = " << n << " m = " << m_a << " time = " << times_bellman[i] << "\n";
            }
        }
    }

    currentTime = std::chrono::system_clock::now();
    timeString = timeToString(currentTime);
    cout << "[" << timeString << "] Ended " << experiment_name << "\n";

    saveResultsToFile(n_values, times_dijkstra, times_bellman, experiment_name);
}


int m_a(int n) {
    return n * n / 10;
}

int m_b(int n) {
    return n * n;
}

int m_c(int n) {
    return 100 * n;
}

int m_d(int n) {
    return 1000 * n;
}

int m_e(int m) {
    return m;
}

int m_f(int m) {
    return m;
}

std::vector<int> r_values() {
    std::vector<int> values;
    for (int i = 1; i <= 200; ++i) {
        values.push_back(i);
    }
    return values;
}

int m_g(int n) {
    return n * n;
}

int m_h(int n) {
    return 1000 * n;
}


int main() {
    setlocale(LC_ALL, "Russian");
    
    std::vector<int> n_values;
    #pragma omp parallel for
    for (int i = 1; i <= 10000; i += 100) {
        n_values.push_back(i);
    }
    int q = 1;
    int r = 1000000;

    std::thread thread_a(experiment, n_values, m_a, q, r, "Experiment 1. a");
    std::thread thread_b(experiment, n_values, m_b, q, r, "Experiment 1. b");

    thread_a.join();
    thread_b.join();

    //n_values.clear();

    return 0;
}
