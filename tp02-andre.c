/* TRABALHO PRATICO 02 ALGORITMOS E ESTRUTURAS DE DADOS 2 */
/* UFSCAR - 2021/1 ENPE */
/* ALUNO: ANDRE SILVEIRA SOUSA RA: 628239 CURSO: ENGENHARIA DE COMPUTACAO */

#include <stdio.h>
#include <stdlib.h>

/* ********************* */
/* Foi decidido resolver o problema das inversoes genomicas atraves de um algoritmo merge sort */
/* Onde usou-se a estrategia de ordenar os valores dos genes atraves da inversao numerica  */
/* Ou seja, dois numeros consecutivos sao invertidos se o numero da esquerda for maior que o da direita */
/* ********************* */

/* ********************* */
/* Prototipos de Funcoes */
/* ********************* */
unsigned long long int qtdswap_merge_sort (int v[], int n);
unsigned long long int divisao (int v[], int temp[], int esq, int dir);
unsigned long long int conquista (int v[], int temp[], int esq , int quebra, int dir);

/* ************************** */
/* Funcao qtdswap_merge_sort */
/* ************************** */
/* entradas: um vetor de valores inteiros e um numero inteiro com a quantidade de itens do vetor */
/* saida: um inteiro com a quantidade de inversoes para ordenar o vetor a partir de merge sort */
/* ************************** */

unsigned long long int qtdswap_merge_sort (int v[], int n){

    /* vetor temporario que contera o vetor v ordenado */
    /* infelizmente nao consegui pensar em uma maneira de contar inversoes sem ordenar */
    int* temp = (int*)malloc(sizeof(int) * n);

    /* para fazer a contagem e necessario dividir e conquistar :) */
    unsigned long long int qtdswap = divisao(v, temp, 0, n-1);

    return qtdswap;
}

/* ************** */
/* Funcao divisao */
/* ************** */
/* entradas: um vetor "v" de inteiros com os valores de entrada, um vetor "temp" de inteiros editavel */
/* um valor inteiro "esq" correspondente a posicao inicial do vetor a ser dividido */
/* um valor inteiro "dir" correspondente a posicao final do vetor a ser dividido */
/* saida: um inteiro com a quantidade de inversoes dos vetores divididos */
/* ************** */

unsigned long long int divisao (int v[], int temp[], int esq, int dir){
    int quebra;
	unsigned long long int qtd_inversoes=0;

    if(dir>esq){

        /* divide em 2 subvetores a partir da metade */
        quebra = (esq+dir)/2;

        /* divide o subvetor da esquerda ao menor possivel */
        qtd_inversoes = divisao(v, temp, esq, quebra);

        /* divide o subvetor da direita ao menor possivel */
        qtd_inversoes += divisao(v, temp, quebra+1, dir);

        /* caso base: vetor com 1 unidade, ordenado, 0 inversoes */
        /* vai para o conquistar: une 2 subvetores, ordenando-os */
        qtd_inversoes += conquista(v, temp, esq, quebra+1, dir);
    }
return qtd_inversoes;
}

/* **************** */
/* Funcao conquista */
/* **************** */
/* entradas: um vetor "v" de inteiros com os valores de entrada, um vetor "temp" de inteiros editavel */
/* um valor inteiro "esq" correspondente a posicao do subvetor da esquerda */
/* um valor inteiro "quebra" correspondente a posicao do subvetor da direita*/
/* um valor inteiro "dir" correspondente a ultima posicao do subvetor da direita */
/* saida: um inteiro com a quantidade de inversoes do vetor temporario ordenado */
/* **************** */

unsigned long long int conquista (int v[], int temp[], int esq, int quebra, int dir){

    unsigned long long int qtd_inversoes = 0;

    /* definicao de indices moveis para os subvetores */
    /* v1 = vetor da esquerda */
    /* v2 = vetor da direita */
    /* posicao = posicao do menor valor */
    int i_v1 = esq;
    int i_v2 = quebra;
    int i_posicao = esq;

    while(i_v1 <= quebra-1 && i_v2 <= dir){

        /* compara se o valor do subvetor da esquerda e menor que o subvetor da direita */
        /* caso positivo: passa para o proximo valor incrementando os indices, nao aumenta a qtd de inversoes */
        if(v[i_v1] <= v[i_v2]){
            temp[i_posicao] = v[i_v1];
            i_posicao++;
            i_v1++;
        }

        /* se o valor do subvetor da esquerda eh maior que o subvetor da direita, acontece a inversao */
        else{ /* so acontece quando todos da esquerda estao ordenados */
            temp[i_posicao] = v[i_v2];
            i_posicao++;
            i_v2++;
            /* para o menor valor ir para a posicao mais da esquerda */
            /* e necessario fazer a diferenca entre a posicao do v2 e a posicao do v1 onde ele deveria estar */
            qtd_inversoes += (quebra - i_v1);
        }
    }

    /* copiando os valores para o retorno dos merges */
    /* quando a posicao esta correta (ja ordenado) */
    while(i_v1 <= quebra-1){
        temp[i_posicao] = v[i_v1];
        i_posicao++;
        i_v1++;
    }
    while(i_v2 <= dir){
        temp[i_posicao] = v[i_v2];
        i_posicao++;
        i_v2++;
    }

    /* copiando o vetor temp ordenado para o vetor original*/
    for(int i=esq; i <= dir; i++) v[i] = temp[i];

    return qtd_inversoes;
}


/* *********** */
/* Funcao MAIN */
/* *********** */

int main(){

	/************************************/
    // ESTRUTURA DO ARQUIVO:
	// Entrada:
    // 5 (numero de valores para ler)
	// 5 2 1 3 4 (vetor de n numeros)
	// Saida:
	// N (numero de inversoes)
    /**************************************/

    /* Ler arquivo de entrada com casos teste */
    FILE *entrada;
    char nomedoarquivo[10];
    scanf("%s",nomedoarquivo);
    entrada=fopen(nomedoarquivo, "r");

    /* variaveis de operacao */
    int n, i;
	unsigned long long int qtdinversoes;

    /* le o primeiro int da linha do arquivo (qtd de itens) */
    fscanf(entrada, "%d", &n);

	/* preenche um vetor com os valores de entrada */
    int vetorentrada[n];

    for(i=0; i<n; i++){
        fscanf(entrada, "%d", &vetorentrada[i]);
    }

    /* chamada para funcao calcular a qtd de inversoes do vetor de entrada */
    qtdinversoes = qtdswap_merge_sort(vetorentrada, n);

    /* impressao do resultado */
	printf("%lld\n", qtdinversoes);

    fclose(entrada);
    return 0; // fim da funcao MAIN
}
