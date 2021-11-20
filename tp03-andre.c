/* TRABALHO PRATICO 03 ALGORITMOS E ESTRUTURAS DE DADOS 2 */
/* UFSCAR - 2021/1 ENPE */
/* ALUNO: ANDRE SILVEIRA SOUSA RA: 628239 CURSO: ENGENHARIA DE COMPUTACAO */

#include <stdio.h>
#include <stdlib.h>
#define MAX 1001

/* ********************* */
/* Foi decidido resolver o problema dos debates atraves de um grafo orientado */
/* onde cada aluno representa um vertice do grafo, e cada aresta representa as perguntas */
/* Foi escolhido implementar o grafo com a estrategia de lista de adjacencia */
/* Para o debate acontecer, o grafo deve ser bipartido */
/* ********************* */
typedef struct noh Noh;
struct noh{
	int destino; //esse int ira marcar o vertice destino do arco v(origem) -> v(destino)
	Noh *proximo;
};

typedef struct grafo *Grafo;
struct grafo{
	Noh **ListaAdj; //estrutura de lista de adjacencia
	int n_vertices;
	int n_arestas;
};

typedef struct fila Fila;
struct fila{
	int *vetor;
	int inicio;
	int fim;
};

/* ********************* */
/* Prototipos de Funcoes */
/* ********************* */

Fila *criaFila(int n);
void insereFila(Fila *F, int n);
int removeFila(Fila *F);
void resetaFila(Fila *F);
int filaVazia(Fila *F);
Fila *liberaFila(Fila *F);

Grafo inicializaGrafo(int n);
void insereArcoGrafo(Grafo G, int v, int w);
Grafo liberaGrafo(Grafo G);

int verificaBipartido(Grafo G);

/* **************** */
/* Funcao CRIA FILA */
/* **************** */
/* entradas: um inteiro correspondente as posicoes da fila */
/* saida: uma fila vazia com n posicoes */
/* ************************** */
Fila *criaFila(int n){
	Fila *F = malloc(sizeof *F);
	F->vetor = (int *)malloc(MAX * sizeof(int));
	F->inicio = 0;
	F->fim = 0;

	return F;
}

/* **************** */
/* Funcao INSERE FILA */
/* **************** */
/* entradas: uma fila de int e um int pra inserir */
/* saida: void */
/* ************************** */
void insereFila(Fila *F, int n){
	F->vetor[F->fim] = n;
	(F->fim)++;
}

/* **************** */
/* Funcao REMOVE FILA */
/* **************** */
/* entradas: remove um item da fila */
/* saida: o int removido */
/* ************************** */
int removeFila(Fila *F){
	int x;
	//if(F->inicio != F->fim){
		x = F->vetor[F->inicio];
		F->inicio++;
		return x;
	//}
}

/* **************** */
/* Funcao RESETA FILA */
/* **************** */
/* entradas: uma fila para resetar */
/* saida: void */
/* ******************** */
void resetaFila(Fila *F){
	F->inicio = 0;
	F->fim = 0;
}

/* **************** */
/* Funcao FILA VAZIA */
/* **************** */
/* entradas: uma fila */
/* saida: 1 fila vazia, 0 fila tem itens */
/* ************************** */
int filaVazia(Fila *F){
	if(F->inicio == F->fim) return 1;
	else return 0;
}

/* **************** */
/* Funcao LIBERA FILA  */
/* **************** */
/* entradas: uma fila */
/* saida: NULL com a fila apagada da memoria */
/* ************************** */
Fila *liberaFila(Fila *F){
	free(F->vetor);
	free(F);
	return NULL;
}

/* ************************** */
/* Funcao INICIALIZA GRAFO */
/* ************************** */
/* entradas: um inteiro representando o numero de vertices do grafo */
/* saida: um grafo com n vertices, sem arestas */
/* ************************** */

Grafo inicializaGrafo(int n){
	int i;
	Grafo G = malloc(sizeof *G);

	G->n_vertices = n;
	G->n_arestas = 0;
	G->ListaAdj = malloc(n * sizeof(Noh *));

	for(i=0 ; i<n ; i++) G->ListaAdj[i] = NULL;

	return G;
}

/* ************************** */
/* Funcao INSERE ARCO GRAFO */
/* ************************** */
/* entradas: um grafo e dois inteiros representando a conexao X -> Y */
/* saida: void */
/* ************************** */
void insereArcoGrafo(Grafo G, int v, int w){
	Noh *p;

	// verifica se o arco v->w ja existe
	for(p = G->ListaAdj[v] ; p != NULL ; p = p->proximo){
		if(p->destino == w) return;
	}

	// se v->w nao existir, cria o arco
	// os arcos serao inseridos no inicio da lista
	p = malloc(sizeof(Noh));
	p->destino = w;
	p->proximo = G->ListaAdj[v];
	G->ListaAdj[v] = p;
	G->n_arestas++;

}

/* ************************** */
/* Funcao LIBERA GRAFO */
/* ************************** */
/* entradas: um grafo G */
/* saida: NULL (apaga o grafo da memoria) */
/* ************************** */
Grafo liberaGrafo(Grafo G){
	int i;
	Noh *p;

	for(i=0 ; i < G->n_vertices ; i++){
		p = G->ListaAdj[i];
		while(p != NULL){
			G->ListaAdj[i] = p;
			p = p->proximo;
			free(G->ListaAdj[i]);
		}
		G->ListaAdj[i] = NULL;
	}
	free(G->ListaAdj);
	G->ListaAdj = NULL;
	free(G);
	return NULL;
}

/* ************************** */
/* Funcao VERIFICA BIPARTIDO */
/* ************************** */
/* entradas: um grafo */
/* saida: um int: 1 significa que o grafo eh bipartido; 0 significa que nao eh */
/* ************************** */
int verificaBipartido(Grafo G){

	/* *********************************************************************** */
	/* utiliza a propriedade de grafo bipartido onde ha particao em 2 grupos: */
	/* grupos com distancia par a uma origem, e grupos com distancia impar */
	/* Para isso ja foi feita a verificacao de paridade da distancia no codigo de distancias */
	/* ******************************************************************** */

	int origem, p_grafo, p_fila;
	int *dist;
	Fila *fila;
	Noh *p;

	dist = malloc(G->n_vertices * sizeof(int));
	fila = criaFila(G->n_vertices);

	for(p_grafo=0 ; p_grafo < G->n_vertices ; p_grafo++) dist[p_grafo] = -1;

	for(origem=0 ; origem < G->n_vertices ; origem++){
		dist[origem] = 0;

		insereFila(fila, origem);

		while(!filaVazia(fila)){
			p_grafo = removeFila(fila);
			p = G->ListaAdj[p_grafo];

			while(p != NULL){
				p_fila = p->destino;
				if(dist[p_fila] == -1){
					//printf("%d entrou em dist -1\n", p_fila);
					dist[p_fila] = dist[p_grafo] + 1;
					insereFila(fila, p_fila);
				}else{
					// AQUI EH A VERIFICACAO DE PARIDADE !!!!
					//dist[p_fila]%2 != (dist[p_grafo]+1)%2
					if(dist[p_fila]%2 != (dist[p_grafo]+1)%2){
						fila = liberaFila(fila);
						return 0;
					} // fim da verficacao de paridade
				} // fim do else -1
				p = p->proximo;
			} // fim do p != null
		} // fim da fila != vazia
		//printf("origem %d chegou no fim\n", origem);
		for(p_grafo=0 ; p_grafo < G->n_vertices ; p_grafo++) dist[p_grafo] = -1;
		resetaFila(fila);
	}// fim das operacoes em um vertice origem
	fila = liberaFila(fila);
	return 1; //eh bipartido
}

/* *********** */
/* Funcao MAIN */
/* *********** */

int main(){

	/************************************/
	// ESTRUTURA DO ARQUIVO:
	// Entrada:
	// 6		(numero de alunos)
	// 2 4 5	(primeiro int: numero de perguntas. prox: alunos que o aluno 0 deseja fazer perguntas)
	// 1 3		(primeiro int: numero de perguntas. prox: alunos que o aluno 1 deseja fazer perguntas)
	// 2 3 5	...
	// 1 0
	// 2 2 1
	// 1 1
	// Saida:
	// Vai ter debate (caso de para agrupar em 2 grupos)
	// Impossível (caso contrario)
	/**************************************/

    /* Ler arquivo de entrada com casos teste */
    FILE *entrada;
    char nomedoarquivo[10];
    scanf("%s",nomedoarquivo);
    entrada=fopen(nomedoarquivo, "r");

    /* variaveis de operacao */
		int i, j, n_alunos, n_perguntas, perguntado;
		Grafo alunos;

    /* le o primeiro int da linha do arquivo (qtd de alunos) */
    fscanf(entrada, "%d", &n_alunos);
		//printf("leu qtd alunos %d\n", n_alunos);
		alunos = inicializaGrafo(n_alunos);

		/* preenche o grafo com as arestas (perguntas) */
		for(i=0 ; i < n_alunos ; i++){
			fscanf(entrada, "%d", &n_perguntas);
			//printf("leu %d perguntas\n", n_perguntas);
			for(j=0 ; j < n_perguntas ; j++){
				fscanf(entrada, "%d", &perguntado);
				//printf("aluno %d pergunta para %d\n", i, perguntado);
				insereArcoGrafo(alunos, i, perguntado);
			}
		}

    /* impressao do resultado */
		if(verificaBipartido(alunos) == 0) printf("Impossivel\n");
		else printf("Vai ter debate\n");

		/* limpar memoria */
		alunos = liberaGrafo(alunos);
    fclose(entrada);

    return 0; // fim da funcao MAIN
}
