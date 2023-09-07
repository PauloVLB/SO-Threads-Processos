import os
import math

n1 = 100 # dimensao da matriz 1
m2 = 100 # dimensao da matriz 2

P = math.ceil((n1 * m2)/8) # numero de threads/processos 

arquivos_paralelos = ["out_thread/out_", "out_processos/out_"]

while True:
    os.system(f'./generate {n1} {n1} {m2} {m2}')

    tempo_sequencial = 0
    tempo_threads = 0
    tempo_processos = 0
    for i in range(10):
        os.system(f'./sequencial in/M1.in in/M2.in')
        os.system(f'./threads in/M1.in in/M2.in {P}')
        os.system(f'./processos in/M1.in in/M2.in {P}')

        with open('out_sequencial/sequencial.out', 'r') as f:
            for line in f:
                pass
            tempo_sequencial += float(line)

        for pasta in arquivos_paralelos:
            max_tempo_threads = 0
            max_tempo_processos = 0
            for i in range(8):
                with open(f'{pasta}{i}.out', 'r') as f:
                    for line in f:
                        pass
                    if pasta == "out_thread/out_":
                        max_tempo_threads = max(max_tempo_threads, float(line))
                    else:
                        max_tempo_processos = max(max_tempo_processos, float(line))
            tempo_processos += max_tempo_processos
            tempo_threads += max_tempo_threads

    tempo_sequencial /= 10
    tempo_threads /= 10
    tempo_processos /= 10

    with open('data/etapa1.txt', 'a') as f:
        f.write(f'{n1} {tempo_sequencial} {tempo_threads} {tempo_processos}\n')
    
    n1 *= 2
    m2 *= 2
    P = math.ceil((n1 * m2)/8)

    if tempo_sequencial >= (400):
        break
