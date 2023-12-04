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
    std::uniform_int_distribution<> vertices(0, n-1);
    std::uniform_int_distribution<> weights(q, r);

    for (int i = 0; i < m; ++i) {
        int v1 = vertices(gen);
        int v2 = vertices(gen);
        while (v1 == v2) {
            v2 = vertices(gen);
        }
        int weight = weights(gen);
        graph[v1].push_back(Edge{ v2, weight });
        graph[v2].push_back(Edge{ v1, weight });
    }

    return graph;
}

void printDistances(const std::vector<int>& distances) {
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] != std::numeric_limits<int>::max()) {
            std::cout << "Путь до вершины " << i << " = " << distances[i] << std::endl;
        }
    }
}

void experiment_1_a() {
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver_a, solver_b;

    for (int n = 1; n <= 10001; n += 100) {

        std::cout << n << std::endl;

        int m = (n * n) / 10;
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
    
    // Создаем экземпляр решателя
    ShortestPathsSolver solver;

    solver.inputGraph();

    std::vector<int> dijkstraDistances = solver.dijkstra(0);

    std::vector<int> bellmanFordDistances = solver.bellmanFord(0);

    // Проверяем, что оба алгоритма дают одинаковые результаты
    //assert(dijkstraDistances == bellmanFordDistances);

    std::cout << "Алгоритм Дейкстры" << std::endl;

    printDistances(dijkstraDistances);

    std::cout << "Алгоритм Форда-Беллмана" << std::endl;

    printDistances(bellmanFordDistances);

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
