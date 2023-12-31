#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <pthread.h>
#include <unistd.h>

std::vector<std::vector<int>> M1;
std::vector<std::vector<int>> M2;
int n1, m1, n2, m2, P;
int n_threads;

void* mult(void* a){
    int id = (int)(size_t) a;
    int begin = id * P;
    int end = begin + P;
    if(end > n1 * m2) end = n1 * m2;

    std::ofstream file("out_thread/out_" + std::to_string(id) + ".out");

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
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    // lê os caminhos dos arquivos de entrada
    std::string pathM1 = argv[1];
    std::string pathM2 = argv[2];
    P = atoi(argv[3]);

    // lê as matrizes de entrada
    std::ifstream file1(pathM1);
    std::ifstream file2(pathM2);

    // lê as dimensões das duas matrizes
    file1 >> n1 >> m1;
    file2 >> n2 >> m2;
    n_threads = ((n1 * m2 - 1) / P) + 1;
    int status;
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

    std::vector<std::chrono::steady_clock::time_point> begins(n_threads);
    std::vector<std::chrono::steady_clock::time_point> ends(n_threads);

    pthread_t threads[n_threads];
    for(int i{0}; i<n_threads; ++i){
        begins[i] = std::chrono::steady_clock::now();
        status = pthread_create(&threads[i], NULL, mult, (void *)(size_t)i);
    }

    for(int i{0}; i<n_threads; ++i){
        status = pthread_join(threads[i], NULL);
        ends[i] = std::chrono::steady_clock::now();

        std::ofstream file("out_thread/out_" + std::to_string(i) + ".out", std::ios::app);
        file << std::chrono::duration_cast<std::chrono::milliseconds>(ends[i] - begins[i]).count() << std::endl;
    }

}