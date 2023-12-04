import matplotlib.pyplot as plt

# Чтение данных из файла
with open('results_2_b.txt', 'r') as file:
    lines = file.readlines()

n_values = []
dijkstra_times = []
bellman_ford_times = []

for line in lines:
    data = line.split(',')
    n_values.append(int(data[0].split('=')[1]))
    dijkstra_times.append(float(data[1].split('=')[1]))
    bellman_ford_times.append(float(data[2].split('=')[1]))

# Построение графиков
plt.figure(figsize=(10, 6))
plt.plot(n_values, dijkstra_times, label='Dijkstra')
plt.plot(n_values, bellman_ford_times, label='Bellman-Ford')
plt.xlabel('n')
plt.ylabel('Time')
plt.title("Experiment 2.b")
plt.legend()
plt.show()
