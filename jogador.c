#include <stdio.h>
#include <string.h>
#include "jogador.h"

#define VIDAS 3
#define PONTUACAO 0

/*
    int x - Inteiro que representa a coordenada X da posi��o inicial do jogador no mapa
    int y - Inteiro que representa a coordenada Y da posi��o inicial do jogador no mapa
*/
Jogador jog_inicializa(int x, int y)
{
    Jogador player = {"Teste", localizacao_cria(x, y), VIDAS, PONTUACAO, 0};
    return player;
}

/*
    Jogador *jogador - Endere�o de uma vari�vel do tipo jogador (fun��o modifica o n�mero de pontos guardada na vari�vel do tipo jogador)
*/
void jog_aumenta_pontuacao(Jogador *jogador, int pontos)
{
    if(jogador->pontuacao + pontos >= 0)
        jogador->pontuacao += pontos;
    else
        jogador->pontuacao = 0;
}

/*
    Jogador *jogador - Endere�o de uma vari�vel do tipo jogador (fun��o modifica a string nome guardada na vari�vel do tipo jogador)
*/
void jog_le_nome(Jogador *jogador)
{
    printf("\n Informe o nome do jogador: ");
    fgets(jogador->nome, MAXLINHAS, stdin);
    jogador->nome[strlen(jogador->nome) - 1] = '\0';
}

/*
    Jogador jogador - Vari�vel do tipo jogador (fun��o imprime o n�mero de vidas, pontos e a string nome guardadas na vari�vel do tipo jogador)
*/
void jog_print_info(Jogador jogador)
{
    printf(" -----------------------------\n");
    printf(" PLAYER    : %s\n", jogador.nome);
    printf(" VIDAS     : %d\n", jogador.vidas);
    printf(" PONTUACAO : %d\n", jogador.pontuacao);
    printf(" -----------------------------\n");
}
