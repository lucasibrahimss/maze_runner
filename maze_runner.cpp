#include <stdio.h>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
#include <utility>

// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
	std::vector<std::vector<char>> labirinto;
};



// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)

	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
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
	// Aloca a matriz maze (malloc)
	for (int i = 0; i < num_rows; ++i)
		// Aloca cada linha da matriz
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
		}
	}
	return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
};

std::vector<std::pair<int, int>> encontrarSaidaLabirinto(std::vector<std::vector<char>>& labirinto, int linhaInicial, int colunaInicial) {
    int linhas = labirinto.size();
    int colunas = labirinto[0].size();
	std::vector<std::pair<int, int>> valid_pos;

    // Criar uma fila para BFS
    std::queue<std::pair<int, int>> fila;
    fila.push(std::pair<int, int>(linhaInicial, colunaInicial));

    // Movimentos possíveis: cima, baixo, esquerda, direita
    int movimentosLin[] = {-1, 1, 0, 0};
    int movimentosCol[] = {0, 0, -1, 1};

    while (!fila.empty()) {
        int linha = fila.front().first;
        int coluna = fila.front().second;
        fila.pop();

        // Checar se a posição atual é a saída
        if (labirinto[linha][coluna] == 's') {
        	return valid_pos;
        }

        // Marcar a posição como visitada
        labirinto[linha][coluna] = '#';

        // Tentar mover para todas as direções possíveis
        for (int i = 0; i < 4; ++i) {
            int novaLinha = linha + movimentosLin[i];
            int novaColuna = coluna + movimentosCol[i];

            // Checar se a nova posição está dentro do labirinto e não é um obstáculo
            if (novaLinha >= 0 && novaLinha < linhas && novaColuna >= 0 && novaColuna < colunas && labirinto[novaLinha][novaColuna] != '#') {
                fila.push(std::pair<int, int>(novaLinha, novaColuna));
				valid_pos.push_back(std::pair<int, int>(novaLinha, novaColuna));
				
            }
        }
    }



}



int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze(argv[1]);
	// chamar a função de navegação
	std::vector<std::pair<int, int>> exit_found = encontrarSaidaLabirinto(initial_pos.labirinto, initial_pos.i, initial_pos.j);
	for(int i=0; i<exit_found.size(); i++)
	{
		std::cout << exit_found[i].first << "    -    " << exit_found[i].second << std::endl;
	}
	
	// Tratar o retorno (imprimir mensagem)
	
	return 0;
};