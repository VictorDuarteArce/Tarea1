#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Puzzle.h"

int main(){
    printf("Nombre archivo: ");
    std::string filename;
    std::cin >> filename;
    printf("Leyendo archivo ");
    std::cout << filename << std::endl;
    std::ifstream file(filename);
    if(!file.is_open()){
        printf("No se pudo abrir el archivo \n");
        return 1;
    }
    std::string line;
    std::stringstream ss;
    int num, n = 0;
    if(getline(file, line, '\n')){
        std::cout << line << std::endl;
        ss << line; //cargo en el objeto de flujo de datos mi línea
        while(ss >> num){
            n++;
        }
    }
    printf("Se leyeron %d numeros \n", n);
    file.close();
    int** board;
    board = new int*[n];
    for(int i = 0; i < n; i++){
        board[i] = new int[n];
    }
    file.open(filename);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> board[i][j];
        }
    }
    file.close();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", board[i][j]);
        }
        putchar('\n');
    }
    Puzzle *p = new Puzzle();
    p->board = board;
    p->size = n;
    time_t ti = clock();
    p->solve();
    time_t tf=clock();
    cout << "tiempo:" << (tf-ti);//CLOCKS_PER_SEC << " segundos" << endl;
    return 0;
}