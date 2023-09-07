import matplotlib.pyplot as plt

# plotar grafico de linha dos dados no arquivo data/etapa1.txt

x = []
y1 = []
y2 = []
y3 = []

with open('data/etapa1.txt', 'r') as f:
    for line in f:
        n, t1, t2, t3 = line.split()
        x.append(int(n))
        y1.append(float(t1))
        y2.append(float(t2))
        y3.append(float(t3))

plt.plot(x, y1, label='Sequencial')
plt.plot(x, y2, label='Threads')
plt.plot(x, y3, label='Processos')
plt.legend()
plt.xlabel('Dimensão da matriz')
plt.ylabel('Tempo (ms)')
plt.show()

