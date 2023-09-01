#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>

int main(int argc, char** argv) {
    // lê os caminhos dos arquivos de entrada
    std::string pathM1 = argv[1];
    std::string pathM2 = argv[2];

    // lê as matrizes de entrada
    std::ifstream file1(pathM1);
    std::ifstream file2(pathM2);

    // lê as dimensões das duas matrizes
    int n1, m1; file1 >> n1 >> m1;
    int n2, m2; file2 >> n2 >> m2;

    // declara as matrizes com seus respectivos tamanhos
    std::vector<std::vector<int>> M1(n1, std::vector<int>(m1));
    std::vector<std::vector<int>> M2(n2, std::vector<int>(m2));

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

    // declara a matriz resultante
    std::vector<std::vector<int>> M3(n1, std::vector<int>(m2));

    // multiplica as matrizes e salva o tempo de execução
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            for(int k = 0; k < m1; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // escreve a matriz resultante em arquivo
    std::ofstream file3("out_sequencial/M3_sequencial.out");

    file3 << n1 << " " << m2 << std::endl;
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            file3 << "c" << i+1 << j+1 << ' ' << M3[i][j] << std::endl;
        }
    }
    file3 << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

    // fecha o arquivo de saída
    file3.close();
}