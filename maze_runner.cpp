#include <stdio.h>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
#include <utility>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;
int num_rows;
int num_cols;

void clearScreen() {
#ifdef _WIN32
    // Para Windows
    system("cls");
#else
    // Para Unix/Linux
    system("clear");
#endif
}

struct pos_t {
	int i;
	int j;
	std::vector<std::vector<char>> labirinto;
};

pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	std::ifstream arquivo(file_name);
	num_rows=0;
	num_cols=0;

	if(arquivo.is_open())
	{
		std::string primeiraLinha;
		if(std::getline(arquivo, primeiraLinha))
		{
			std::istringstream iss(primeiraLinha);
			if(iss >> num_rows >> num_cols)
			{
				//std::cout << num_rows << " " << num_cols << std::endl;
			}
		}

			std::string linha;
		while (std::getline(arquivo, linha))
		{

			std::vector<char> linhaLabirinto;
			for(char c : linha) {
				linhaLabirinto.push_back(c);
			}
			initial_pos.labirinto.push_back(linhaLabirinto);
		}
	}

	for( int i=0; i<num_rows; i++){
			for(int j=0; j<num_cols; j++){
				if (initial_pos.labirinto[i][j] == 'e')
				{
					initial_pos.i=i;
					initial_pos.j=j;
				}
			}
	}

	return initial_pos;
}
    void print(std::vector<std::vector<char>> maze)
    {
        clearScreen();
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                cout << maze[i][j];
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }

bool findPath(vector<vector<char>>& maze, int row, int col) {
    int numRows = maze.size();
    int numCols = maze[0].size();

    // Verificar se estamos fora dos limites da matriz.
    if (row < 0 || row >= numRows || col < 0 || col >= numCols){
        return false;
    }
    // Verificar se atingimos o ponto de chegada.
    if (maze[row][col] == 's') {
        return true;
    }

    // Verificar se a célula atual é uma parede, já foi visitada ou não faz parte do caminho correto.
    if (maze[row][col] == '#' || maze[row][col] == '-' || maze[row][col] == ' ')
    {
        return false;
    }

    print(maze);
    // Marcar a célula como parte do caminho temporariamente.
    char originalCell = maze[row][col];
    maze[row][col] = '-';

    // Tentar mover nas quatro direções possíveis.
    if (findPath(maze, row + 1, col) ||
        findPath(maze, row - 1, col) ||
        findPath(maze, row, col + 1) ||
        findPath(maze, row, col - 1)) {
        return true;
    }

    // Restaurar a célula original, pois não faz parte do caminho correto.
    maze[row][col] = originalCell;
    return false;
}


int main(int argc, char* argv[]){
    pos_t maze = load_maze(argv[1]);
    int startRow = maze.i;
    int startCol = maze.j;
    cout<<startRow<<"  "<<startCol<<endl;
    cout<<num_rows<<"  "<<num_cols<<endl;

    // Encontrar o caminho correto.
    findPath(maze.labirinto, startRow, startCol);
      
    return 0;
}