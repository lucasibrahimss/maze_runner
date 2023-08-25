#include <stdio.h>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();


// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)
	std::ifstream arquivo(file_name);
	num_rows=0;
	num_cols=0;
	std::vector<std::vector<char>> labirinto;

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
			labirinto.push_back(linhaLabirinto);
		}
		arquivo.close();
		for( int i=0; i<num_rows;i++){
			for(int j; j<num_cols; i++){
				if (labirinto[i][j] == 'e')
				{
					initial_pos.i=i;
					initial_pos.j=j;
					std::cout<<initial_pos.i<< "  " << initial_pos.j<<std::endl;
				}
			}
		}


	} else{
		//std::cerr << "Nao foi possivel abrir o arquivo." << std::endl;
	}
	// Aloca a matriz maze (malloc)
	/*for (int i = 0; i < num_rows; ++i)
		// Aloca cada linha da matriz
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
		}
	}*/
	return initial_pos;
}

// Função que imprime o labirinto
/*void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			//printf("%c", maze[i][j]);
		}
		//printf("\n");
	}
}*/


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
	
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto
		
		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/

		
	
		// Verifica se a pilha de posições nao esta vazia 
		//Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		// Caso contrario, retornar falso
		if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
		}
	return false;
}

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze(argv[1]);
	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	
	// Tratar o retorno (imprimir mensagem)
	
	return 0;
}
