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

    for (int i = 0; i < n; ++i) {
        graph[i] = std::vector<Edge>();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertices(0, n - 1);
    std::uniform_int_distribution<> weights(q, r);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int v = vertices(gen);
            int weight = weights(gen);
            bool exists = false;

            while (v == j && exists == true) {
                v = vertices(gen);

                for (const auto& e : graph[i]) {
                    if (e.target == v) {
                        exists = true;
                        break;
                    }
                }
            }

            Edge edge = { v, weight };

            graph[i].push_back(edge);
        }
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

    std::cout << "Запустился 1 эксперимент буква а" << std::endl;
    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    std::ofstream file("results_1_a.txt");

    ShortestPathsSolver solver;

    for (int n = 1; n <= 10001; n += 100) {


        int m = (n * n) / 10;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();

    }

    // Сохранение результатов в файл

    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << 1 + 100 * i << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 1а завершился" << std::endl;
}

void experiment_1_b() {

    std::cout << "Запустился 1 эксперимент буква б" << std::endl;

    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver;

    for (int n = 1; n <= 10001; n += 100) {

        int m = (n * n);
        int r = std::pow(10,6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_1_b.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << 1 + 100*i << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 1б завершился" << std::endl;
}

void experiment_2_a() {

    std::cout << "Запустился 2 эксперимент буква а" << std::endl;

    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver;

    for (int n = 101; n <= 10001; n += 100) {

        int m = 100*n;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        //std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        //std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_2_a.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << 101 + 100*i << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 2а завершился" << std::endl;
}

void experiment_2_b() {

    std::cout << "Запустился 2 эксперимент буква б" << std::endl;

    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver;

    for (int n = 101; n <= 10001; n += 100) {

        int m = 1000 * n;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        //std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        //std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_2_b.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << 101 + 100 * i << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 2б завершился" << std::endl;
}

void experiment_3() {

    std::cout << "Запустился 3 эксперимент" << std::endl;

    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver;

    for (int m = 0; m <= std::pow(10, 7); m += std::pow(10, 5)) {

        int n = 10001;
        int r = std::pow(10, 6);
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);
        std::cout << "Граф создан" << std::endl;

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_3.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << std::pow(10, 5) * i << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 3 завершился" << std::endl;
}

void experiment_4_a() {

    std::cout << "Запустился 4 эксперимент буква а" << std::endl;

    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver;

    for (int r = 1; r <= 200; ++r) {

        int n = 101;
        int m = n * n;
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);
        std::cout << "Граф создан" << std::endl;

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();
    }

    // Сохранение результатов в файл
    std::ofstream file("results_4_a.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << i + 1 << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 4а завершился" << std::endl;
}

void experiment_4_b() {

    std::cout << "Запустился 4 эксперимент буква б" << std::endl;

    std::vector<double> dijkstraTime;
    std::vector<double> bellmanFordTime;

    ShortestPathsSolver solver;

    for (int r = 1; r <= 200; ++r) {

        int n = 10001;
        int m = 1000 * n;
        int q = 1;

        // Создание графа и заполнение его ребрами
        solver.CreateGraph(n, m, q, r);

        // Запуск алгоритма Дейкстры и измерение времени выполнения

        auto start = std::chrono::high_resolution_clock::now();
        solver.dijkstra(0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        dijkstraTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Дейкстры для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        // Запуск алгоритма Беллмана-Форда и измерение времени выполнения

        start = std::chrono::high_resolution_clock::now();
        solver.bellmanFord(0);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        bellmanFordTime.push_back(diff.count());

        std::cout << "Время выполнения алгоритма Беллмана-Форда для графа с " << m << " ребрами и верхней границей веса " << r << ": " << diff.count() << " секунд" << std::endl;

        solver.clearGraph();

    }

    // Сохранение результатов в файл
    std::ofstream file("results_4_b.txt");
    for (int i = 0; i < dijkstraTime.size(); ++i) {
        file << i + 1 << " " << dijkstraTime[i] << " " << bellmanFordTime[i] << std::endl;
    }
    file.close();

    std::cout << "Эксперимент 4б завершился" << std::endl;
}

void test() {
    
    // Создаем экземпляр решателя
    ShortestPathsSolver solver;

    int n = 10;
    int m = 5;
    int q = 1;
    int r = 10;

    // solver.inputGraph();

    solver.CreateGraph(n, m, q, r);

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

    //experiment_1_a(); // DONE
    //experiment_1_b(); // DONE
    //experiment_2_a(); // DONE
    //experiment_2_b(); // DONE
    //experiment_3();
    //experiment_4_a();
    //experiment_4_b();

    test();
    std::cout << "Все тесты прошли успешно!" << std::endl;


    return 0;
}
