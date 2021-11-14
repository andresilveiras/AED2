/* TRABALHO PRATICO 01 ALGORITMOS E ESTRUTURAS DE DADOS 2 */
/* UFSCAR - 2021/1 ENPE */
/* ALUNO: ANDRE SILVEIRA SOUSA RA: 628239 CURSO: ENGENHARIA DE COMPUTACAO */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********************************** */
/* TRABALHO 01: AGENDA DE CONTATINHOS */
/* ********************************** */
/* uma agenda de contatos geralmente é implementada utilizando tabelas hash */
/* justamente por ter uma logica de chave-valor e buscas no estilo dicionario */
/* Para tratar as colisoes da tabela Hash foi escolhido o metodo de Lista Ligada */
/* portanto foi necessario criar um tipo celula para comportar os valores e o apontador */
/* ********************************** */

/* ******************************* */
/* Estruturas e Tipos de Variaveis */
/* ******************************* */

typedef struct celula CelulaTH;

struct celula{
    char *chave_nome;
    int valor_telefone;
    CelulaTH *bateu; //ponteiro usado para a proxima posicao da lista ligada
};

/* ****************************** */
/* Variaveis Globais e Definicoes */
/* ****************************** */

#define TAMANHO 9999
static CelulaTH **a_tabela_ta_aqui = NULL;
static int quantidade_chaves = 0;
//static int M;

/* ********************* */
/* Prototipos de Funcoes */
/* ********************* */

char *alocaString(char *nome);
void criaTabela(int tamanho);
int espalhamento(char *nome, int tamanho);
void procura(char *nome);
void insere(char *nome, int telefone);
void atualiza(char *nome, int telefone);
void apaga(char *nome);
void freeTabela();

/* ******************** */
/* Funcao ALOCA STRING  */
/* ******************** */
/* entradas: uma string para ser alocada  */
/* saida: um ponteiro para string com o valor alocado na memoria */

char *alocaString(char *nome){
    char *aloquei = (char*) malloc(sizeof(char)*strlen(nome));
    strcpy(aloquei, nome);
    return aloquei;
}

/* ******************* */
/* Funcao CRIA TABELA  */
/* ******************* */
/* entradas: um inteiro com o tamanho maximo da tabela hash   */
/* saida: nao tem, essa eh so uma funcao pra alocar memoria */
/* ******************* */

void criaTabela(int tamanho){
    int i;
    quantidade_chaves = 0;

    a_tabela_ta_aqui = malloc(tamanho * sizeof(CelulaTH *));

    for(i = 0; i < tamanho; i++)
        a_tabela_ta_aqui[i] = NULL;
}

/* ******************** */
/* Funcao ESPALHAMENTO  */
/* ******************** */
/* entradas: a chave (String) e o tamanho (int) da tabela hash */
/* saida: um valor resultante da funcao espalhamento que determina a posicao da chave na tabela hash */
/* ******************* */

int espalhamento(char *nome, int tamanho){
    int i, hasher = 0;
    int fator = 9973; //primo

    for(i = 0; nome[i] != '\0'; i++)
        hasher = (hasher * fator + nome[i]) % tamanho;

    return hasher;
}

/* ************** */
/* Funcao PROCURA */
/* ************** */
/* entradas: uma String nome como chave da hash             */
/* saida:  nao tem mais pq o site me obriga a fazer funcao void  */
/* ************** */

void procura(char *nome){

    CelulaTH *p;
    int posicao = espalhamento(nome, TAMANHO);
    p = a_tabela_ta_aqui[posicao];

    //compara o nome com os nomes daquela posicao enquanto tiver itens na lista
    while(p != NULL && strcmp(p->chave_nome, nome) != 0){
        p = p->bateu;
    }

    if(p == NULL){
        printf("Contatinho nao encontrado\n");
        return;
    }

    if(p != NULL && strcmp(p->chave_nome, nome) == 0){
        printf("Contatinho encontrado: telefone %d\n", p->valor_telefone);
        return;
    }
}

/* ************************** */
/* Funcao INSERE */
/* ************************** */
/* entradas: uma String nome e um int telefone     */
/* saida:  nao tem mais pq o site me obriga a fazer funcao void  */
/* ************************** */

void insere(char *nome, int telefone){
    CelulaTH *p;
    int posicao = espalhamento(nome, TAMANHO);
    p = a_tabela_ta_aqui[posicao];

    while(p != NULL && strcmp(p->chave_nome, nome) != 0){
        p = p->bateu;
    }

    //se parar o loop e encontrar uma chave com o mesmo valor, o nome ja existe
    if(p != NULL && strcmp(nome, p->chave_nome) == 0){
        printf("Contatinho ja inserido\n");
        return;
    }

    //se encontrou uma posicao vazia, insere
    if(p == NULL){
        p = malloc(sizeof(*p));
        p->chave_nome = alocaString(nome);
        p->valor_telefone = telefone; //no codigo do prof isso ta pra fora do if
        p->bateu = a_tabela_ta_aqui[posicao];
        a_tabela_ta_aqui[posicao] = p;
        quantidade_chaves++;
        return;
    }
}

/* ************************** */
/* Funcao ATUALIZA */
/* ************************** */
/* entradas: uma String nome e um int telefone     */
/* saida:  nao tem mais pq o site me obriga a fazer funcao void  */
/* ************************** */

void atualiza(char *nome, int telefone){
    CelulaTH *p;
    int posicao = espalhamento(nome, TAMANHO);
    p = a_tabela_ta_aqui[posicao];

    //verifica a primeira celula na posicao da tabela hash,
    //e vai percorrendo a lista ligada ate encontrar o nome ou uma posicao vazia
    while(p != NULL && strcmp(p->chave_nome, nome) != 0){
        p = p->bateu;
    }

    //se encontrou uma posicao vazia, nao tem contato pra atualizar
    if(p == NULL){
        printf("Operacao invalida: contatinho nao encontrado\n");
        return;
    }

    //se parar o loop e encontrar uma chave com o mesmo valor, atualiza o telefone
    if(p != NULL && strcmp(p->chave_nome, nome) == 0){
        p->valor_telefone = telefone;
        //printf("Contatinho %s atualizado\n", p->chave_nome);
        return;
    }
}

/* ************************** */
/* Funcao APAGA */
/* ************************** */
/* entradas: uma String nome como chave da hash        */
/* saida:  nao tem mais pq o site me obriga a fazer funcao void  */
/* ************************** */
void apaga(char *nome){
    CelulaTH *p, *aux;
    int posicao = espalhamento(nome, TAMANHO);
    p = a_tabela_ta_aqui[posicao];

    /* ****************************** */
    /* verificando a primeira posicao */
    /* ****************************** */

    //caso nao exista valor na primeira posicao:

    //se encontrou o contato na primeira posicao, remover
    if(p != NULL && strcmp(p->chave_nome, nome) == 0){
    //   printf("Removendo contatinho %s\n", p->chave_nome);
      if (p->bateu != NULL) a_tabela_ta_aqui[posicao] = p->bateu;
      else a_tabela_ta_aqui[posicao] = NULL;
      free(p->chave_nome);
      free(p);
      quantidade_chaves--;
      return;
    }

    /* ************************************ */
    /* se nao encontrou na primeira posicao */
    /* ************************************ */

    if(p == NULL){
        printf("Operacao invalida: contatinho nao encontrado\n");
        return;
    }
    //verifica o sucessor do ponteiro
    while(p->bateu != NULL && strcmp((p->bateu)->chave_nome, nome) != 0){
        p = p->bateu;
    }

    //se percorreu e chegou em uma posicao vazia, nao tem contato pra remover
    if(p->bateu == NULL){
        printf("Operacao invalida: contatinho nao encontrado\n");
        return;
    }

    //se encontrou no sucessor
    if(p->bateu != NULL && strcmp((p->bateu)->chave_nome, nome) == 0){

        //printf("Removendo contatinho %s\n", (p->bateu)->chave_nome);

        aux = p->bateu; //aux recebe a celula a remover
        p->bateu = aux->bateu; //OBS: aqui o p NAO MUDOU, mas o p->proximo pula a celula que vai ser removida!!!!

        free(aux->chave_nome);
        free(aux);
        quantidade_chaves--;
        return;
    }

}

/* ************************** */
/* Funcao FREE TABELA */
/* ************************** */
/* entradas: nao tem   */
/* saida:  tb nao tem  */
/* ************************** */
void freeTabela(){
    CelulaTH *p = NULL, *q = NULL;
    int h;
    for(h = 0; h < TAMANHO; h++){
        p = a_tabela_ta_aqui[h];
        while(p != NULL){
            q = p;
            p = p->bateu;
            free(q->chave_nome);
            free(q);
        }
    }
    free(a_tabela_ta_aqui);
    a_tabela_ta_aqui = NULL;
    quantidade_chaves = 0;
}


/* *********** */
/* Funcao MAIN */
/* *********** */

int main(){

    /************************************/
    // ESTRUTURA DA LINHA
    // I nome 123456789
    // P nome
    // R nome
    // A nome 987654321
    // 0
    /**************************************/

    /* Criar a tabela */
    criaTabela(TAMANHO);

    /* definicao de variaveis de operacao */
    char entrada[25];
    char operacao, nome[12];
    int telefone;

	/* leitura das operacoes */

    do{
		fgets(entrada, 25, stdin);
        sscanf(entrada, "%c %s %d", &operacao, nome, &telefone);
        //printf("-----\nEntrada: %s %s %d\n------\n", operacao, nome, telefone);

        if(operacao == 'P'){
            //printf("Procurando %s\n", nome);
            procura(nome);
        }else if(operacao == 'I'){
            //printf("Inserindo %s\n", nome);
            insere(nome, telefone);
        }else if(operacao == 'A'){
            //printf("Atualizando %s\n", nome);
            atualiza(nome, telefone);
        }else if(operacao == 'R'){
            //printf("Removendo %s\n", nome);
            apaga(nome);
        }
    }while(operacao != '0');

    freeTabela();
    return 0; // fim da funcao MAIN
}
