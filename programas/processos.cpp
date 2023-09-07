#include <iostream>
#include <map>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>

std::vector<std::vector<int>> M1;
std::vector<std::vector<int>> M2;
int n1, m1, n2, m2, P;
int n_processos;

void mult(int id){
    int begin = id * P;
    int end = begin + P;
    if(end > n1 * m2) end = n1 * m2;

    std::ofstream file("out_processos/out_" + std::to_string(id) + ".out");

    file << n1 << " " << m2 << std::endl;

    for(int i{begin}; i<end; ++i){
        int row = i / m2;
        int col = i % m2;
        int sum = 0;

        for(int j{0}; j<m1; ++j){
            sum += M1[row][j] * M2[j][col];
        }
        file << "c" << row + 1 << col + 1 << ' ' << sum << std::endl;
    }

    file.close();

}

int main(int argc, char** argv) {
    // lê os caminhos dos arquivos de entrada
    std::string pathM1 = argv[1];
    std::string pathM2 = argv[2];
    P = atoi(argv[3]);
    std::vector<pid_t> pids(P);

    // lê as matrizes de entrada
    std::ifstream file1(pathM1);
    std::ifstream file2(pathM2);

    // lê as dimensões das duas matrizes
    file1 >> n1 >> m1;
    file2 >> n2 >> m2;
    n_processos = ((n1 * m2 - 1) / P) + 1;
    pid_t pid_filho;
    // declara as matrizes com seus respectivos tamanhos
    M1 = std::vector<std::vector<int>>(n1, std::vector<int>(m1));
    M2 = std::vector<std::vector<int>>(n2, std::vector<int>(m2));

    // lê a matriz 1
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m1; j++) {
            file1 >> M1[i][j];
        }
    }

    // lê a matriz 2
    for(int i = 0; i < n2; i++) {
        for(int j = 0; j < m2; j++) {
            file2 >> M2[i][j];
        }
    }

    // fecha os arquivos de entrada
    file1.close();
    file2.close();

    std::map<pid_t, int> map_index;
    std::map<pid_t, std::chrono::steady_clock::time_point> map_begins;

    pthread_t processos[n_processos];

    for(int i{0}; i<n_processos; ++i){
        auto begin = std::chrono::steady_clock::now();
        pids[i] = fork();
        
        if(pids[i] == 0){
            mult(i);
            exit(0);
        }
        else{
            map_index[pids[i]] = i;
            map_begins[pids[i]] = begin;
        }

    }

    for(int i{0}; i < n_processos; ++i){
        pid_filho = wait(NULL);
        auto end = std::chrono::steady_clock::now();
        std::ofstream file("out_processos/out_" + std::to_string(map_index[pid_filho]) + ".out", std::ios::app);
        file << std::chrono::duration_cast<std::chrono::milliseconds>(end - map_begins[pid_filho]).count() << std::endl;

    }

}