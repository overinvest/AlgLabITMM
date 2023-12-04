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
#include <random>
#include <cmath>
#include <cassert>

Graph createGraph(int n, int m, int q, int r) {
    Graph graph;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(q, r);

    for (int i = 0; i < n; ++i) {
        std::vector<Edge> edges;
        for (int j = 0; j < n; ++j) {
            if (i != j) { // Убедитесь, что ребра для вершины не превышают n - 1
                int weight = dis(gen);
                edges.push_back({ j, weight });
            }
        }
        graph[i] = edges;
    }

    return graph;
}

// n = 1, ..., 10^4 + 1, 100
// m = n^2 / 2
// r = 10^6
// q = 1

//void experiment_1(ShortestPathsSolver path) {
//    for (int n = 1; n <= 10001; n += 100) {
//        int m = (n * n) / 2;
//        int r = 10^6;
//        int q = 1;
//
//        // Создание графа и заполнение его ребрами
//        Graph graph1 = path.createGraph(n, m, q, r);
//
//        // Запуск алгоритма Дейкстры и измерение времени выполнения
//        auto start = std::chrono::high_resolution_clock::now();
//        path.setGraph(graph1);
//        path.dijkstra(0);
//        auto end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double> diff = end - start;
//        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;
//
//        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения
//        start = std::chrono::high_resolution_clock::now();
//        path.setGraph(graph1);
//        path.bellmanFord(0);
//        end = std::chrono::high_resolution_clock::now();
//        diff = end - start;
//        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;
//    }
//}

void experiment_1_a() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int n = 1; n <= 10001; n += 100) {

        std::cout << n << std::endl;

        int m = (n * n) / 2;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_1_a.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "n = " << 1 + 100 * i << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void experiment_1_b() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int n = 1; n <= 10001; n += 100) {

        std::cout << n << std::endl;

        int m = (n * n);
        int r = std::pow(10,6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_1_b.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "n = " << 1 + 100*i << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void experiment_2_a() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int n = 101; n <= 10001; n += 100) {

        std::cout << n << std::endl;

        int m = 100*n;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_2_a.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "n = " << 101 + 100*i << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void experiment_2_b() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int n = 101; n <= 10001; n += 100) {

        std::cout << n << std::endl;

        int m = 1000 * n;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_2_b.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "n = " << 101 + 100 * i << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void experiment_3() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int m = 0; m <= std::pow(10, 7); m += std::pow(10, 5)) {

        int n = 10001;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_3.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "m = " << std::pow(10, 5) * i << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void experiment_4_a() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int r = 1; r <= 200; ++r) {

        int n = 10001;
        int m = n * n;
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_4_a.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "r = " << i + 1 << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void experiment_4_b() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int r = 1; r <= 200; ++r) {

        int n = 10001;
        int m = n * n;
        int q = 1;

        // Создание графа и заполнение его ребрами
        Graph graph = createGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver_a.setGraph(graph);
        solver_a.dijkstra(0);
        solver_a.clearGraph();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver_b.setGraph(graph);
        solver_b.bellmanFord(0);
        solver_b.clearGraph();
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        graph.clear();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_4_b.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << "n = " << i + 1 << ", Dijkstra time = " << dijkstraTime[i] << ", Bellman-Ford time = " << bellmanFordTime[i] << std::endl;
    }
    file.close();
}

void test() {
    // Создаем граф
    int n = 5, m = 10, q = 1, r = 10;
    Graph g = createGraph(n, m, q, r);

    // Проверяем, что граф создан правильно
    assert(g.size() == n);
    for (int i = 0; i < n; ++i) {
        assert(g[i].size() == n - 1);
        for (const Edge& edge : g[i]) {
            assert(edge.target != i);
            assert(edge.weight >= q && edge.weight <= r);
        }
    }

    // Создаем экземпляр решателя
    ShortestPathsSolver solver(g);

    // Проверяем алгоритм Дейкстры
    std::vector<int> dijkstraDistances = solver.dijkstra(0);
    assert(dijkstraDistances.size() == n);

    // Проверяем алгоритм Беллмана-Форда
    std::vector<int> bellmanFordDistances = solver.bellmanFord(0);
    assert(bellmanFordDistances.size() == n);

    // Проверяем, что оба алгоритма дают одинаковые результаты
    assert(dijkstraDistances == bellmanFordDistances);

    solver.drawGraph();
}

int main() {
    setlocale(LC_ALL, "Russian");

    // experiment_1_a(); // DONE
    // experiment_1_b(); // DONE
    // experiment_2_a(); // DONE
    /*experiment_2_b();
    experiment_3();
    experiment_4_a();
    experiment_4_b();*/

    test();
    std::cout << "Все тесты прошли успешно!" << std::endl;

    return 0;
}
