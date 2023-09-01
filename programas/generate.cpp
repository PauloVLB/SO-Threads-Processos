#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

int main(int argc, char** argv) {
    // define semente do rand
    srand(time(NULL));

    // lê as dimensões das duas matrizes
    int n1 = atoi(argv[1]);
    int m1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    int m2 = atoi(argv[4]);

    // declara as matrizes com seus respectivos tamanhos
    std::vector<std::vector<int>> M1(n1, std::vector<int>(m1));
    std::vector<std::vector<int>> M2(n2, std::vector<int>(m2));

    // gera aleatoriamente matriz 1
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m1; j++) {
            M1[i][j] = rand() % 10 + 1;
        }
    }   

    // gera aleatoriamente matriz 2
    for(int i = 0; i < n2; i++) {
        for(int j = 0; j < m2; j++) {
            M2[i][j] = rand() % 10 + 1;
        }
    }

    // escreve as matrizes em arquivos
    std::ofstream file1("in/M1.in");
    std::ofstream file2("in/M2.in");

    file1 << n1 << " " << m1 << std::endl;
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m1; j++) {
            file1 << M1[i][j] << " ";
        }
        file1 << std::endl;
    }

    file2 << n2 << " " << m2 << std::endl;
    for(int i = 0; i < n2; i++) {
        for(int j = 0; j < m2; j++) {
            file2 << M2[i][j] << " ";
        }
        file2 << std::endl;
    }

    // fecha os arquivos de entrada
    file1.close();
    file2.close();
}