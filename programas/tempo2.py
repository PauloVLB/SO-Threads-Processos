import os
import math

n1 = 3200 # dimensao da matriz 1
m2 = 3200 # dimensao da matriz 2

denominador_ptr = 0 # numero de threads/processos
denominadores = [8, 16, 32, 4, 2]
P = math.ceil((n1 * m2)/denominadores[denominador_ptr])

arquivos_paralelos = ["out_thread/out_", "out_processos/out_"]

while True:

    print(f'P: {P}')
    print(f'denominador: {denominadores[denominador_ptr]}')

    tempo_threads = 0
    tempo_processos = 0

    for i in range(10):
        os.system(f'./threads in/M1.in in/M2.in {P}')
        os.system(f'./processos in/M1.in in/M2.in {P}')

        for pasta in arquivos_paralelos:
            max_tempo_threads = 0
            max_tempo_processos = 0

            # calcula quantidade de arquivo de saida
            qnt_arquivos = denominadores[denominador_ptr]

            for i in range(qnt_arquivos):
                with open(f'{pasta}{i}.out', 'r') as f:
                    for line in f:
                        pass
                    if pasta == "out_thread/out_":
                        max_tempo_threads = max(max_tempo_threads, float(line))
                    else:
                        max_tempo_processos = max(max_tempo_processos, float(line))
            tempo_processos += max_tempo_processos
            tempo_threads += max_tempo_threads

    tempo_threads /= 10
    tempo_processos /= 10

    with open('data/etapa2.txt', 'a') as f:
        f.write(f'{P} {tempo_threads} {tempo_processos}\n')
    
    denominador_ptr += 1
    if denominador_ptr == len(denominadores):
        break
    
    P = math.ceil((n1 * m2)/denominadores[denominador_ptr])
    
