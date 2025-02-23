#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "arquivo.h"
#include "ranking.h"

#define TAM_FONTE 80
#define TAM_PIXEL 70

/*
    Esta fun��o recebe um n�mero inteiro de 0 a 3, imprimindo um menu de 4 op��es onde
a op��o correspondente ao n�mero de entrada possui uma formata��o e cor diferente das
demais.
*/
void DesenhaMenu(int opcao)
{

    // Declara��o e defini��o de dados
    int i;
    char TEXT[OPCOES + 1][TAMANHO_TEXTO];     // Matriz com 5 linhas para armazenar as strings das 4 op��es do menu e 1 string para uso posterior
    sprintf(TEXT[0],"NOVO JOGO");             // Guarda a string da direita na linha 0 da matriz
    sprintf(TEXT[1],"CARREGAR JOGO");         // Guarda a string da direita na linha 1 da matriz
    sprintf(TEXT[2],"RANKING PONTOS");        // Guarda a string da direita na linha 2 da matriz
    sprintf(TEXT[3],"SAIR");                  // Guarda a string da direita na linha 3 da matriz

    // Execu��o do comando que desenha as op��es do menu na janela do raylib
    for(i = 0; i < OPCOES; i++)
    {
        if(i == opcao)
        {
            sprintf(TEXT[4], "[%s]", TEXT[i]);
            DrawText(TEXT[4], (LARGURA / 1.75) , POSICAO_Y_MENU + (DESLOCAMENTO_Y_MENU * i), TAMANHO_FONTE, RED);
        }
        else
        {
            DrawText(TEXT[i], (LARGURA / 1.75), POSICAO_Y_MENU + (DESLOCAMENTO_Y_MENU * i), TAMANHO_FONTE, WHITE);
        }
    }

    /* A f�rmula utilizada para centralizar os textos � (LARGURA - (MeasureText(TEXT[i], TAMANHO_FONTE))) / 2, onde o tamanho da largura da janela
    do raylib subtraido pelo largura do texto d� o valor do espa�o em branco. Como queremos deslocar o texto para o centro, dividimos esse espa�o em
    branco em 2 "peda�os" iguais. Logo, o valor da largura do espa�o em branco dividido por 2 nos devolve o deslocamento para a direita que o texto
    deve ter para ficar centralizado no eixo X. */

    EndDrawing();
}

/*
    Esta fun��o desenha um menu interativo que pode ser navegado com as teclas do teclado.
Setas para cima e baixo deslocam a op��o selecionada no menu e ENTER retorna a op��o sele-
nada para a fun��o main para executar o comando adequado.
*/

void menuJogo(Mapa *mapa, int *nivel, int *flag, Ranking ranking[], int *posicoes)
{
    int opcao = 0;                        // Inicia op��o como zero (menu inicia com a primeira op��o selecionada)
    int fim = 1;

    SetWindowSize(LARGURA, ALTURA);
    SetWindowTitle("Lightest Dungeon");
    Texture2D background = LoadTexture("menu.png");

    while (*flag && fim)  // Encerra loop quando X da janela for clicado ou quando flag se tornar falsa
    {

        // Desenha as op��es do menu e a string guardada no vetor mensagem (no topo) dentro da janela do raylib
        BeginDrawing();
        DrawTexture(background, 0, 0, RAYWHITE);
        DesenhaMenu(opcao);

        // Modifica o menu conforme o input do usu�rio
        if(IsKeyPressed(KEY_DOWN))   // Se usu�rio aperta a tecla da seta para baixo...
        {
            opcao++;                 // Soma 1 a op��o (mudando a entrada da fun��o desenho -> desloca a op��o selecionada para baixo no menu)
            if(opcao > 3)            // Se op��o ultrapassar o valor 3, op��o se torna 0 novamente (menu circular)
            {
                opcao = 0;
            }
        }
        if(IsKeyPressed(KEY_UP))     // Se usu�rio aperta a tecla da seta para cima...
        {
            opcao--;                 // Subtrai 1 da op��o (mudando a entrada da fun��o desenho -> desloca a op��o selecionada para cima no menu)
            if(opcao < 0)                // Se op��o se tornar negativa, op��o se torna 3 (menu circular)
            {
                opcao = 3;
            }
        }
        if(IsKeyPressed(KEY_ENTER))  // Se usu�rio aperta a tecla ENTER
        {
            switch(opcao)
            {
                case 0:
                    fim = 0;
                    mapa_carrega(mapa, *nivel);
                    mapa->player = jog_inicializa(mapa->posicaoInicialJ.linha, mapa->posicaoInicialJ.coluna);
                    SetWindowSize((TAM_PIXEL * mapa->dimensoes.coluna), (30 + (TAM_PIXEL * mapa->dimensoes.linha)));
                    break;
                case 1:
                    fim = 0;
                    arq_recupera_jogo(mapa);
                    *nivel = mapa->nivel;
                    SetWindowSize((TAM_PIXEL * mapa->dimensoes.coluna), (30 + (TAM_PIXEL * mapa->dimensoes.linha)));
                    break;
                case 2:
                    carrega_rankings(ranking, posicoes);
                    imprime_rankings(ranking, *posicoes);
                    SetWindowSize(LARGURA, ALTURA);
                    break;
                case 3:
                    *flag = 0;
                    break;
            }
        }
    }
}

void gameOver(Mapa *mapa, int *menu)
{
    BeginDrawing();

    int altura = ((30 + (TAM_PIXEL * mapa->dimensoes.linha)) - TAM_FONTE) / 2;
    int largura = ((TAM_PIXEL * mapa->dimensoes.coluna) - MeasureText("GAME OVER", TAM_FONTE)) / 2;
    DrawText("GAME OVER", largura, altura, TAM_FONTE, RED);
    DrawText("[1] - Continue?", largura, altura + 80, TAM_FONTE - 40, RED);
    DrawText("[2] - Give Up?", largura, altura + 120, TAM_FONTE - 40, RED);
    if(IsKeyPressed(KEY_ONE))
    {
        arq_recupera_jogo(mapa);
    }
    else if(IsKeyPressed(KEY_TWO))
    {
        *menu = 1;
    }

    ClearBackground(RAYWHITE);
    EndDrawing();
}

void pausa_jogo(Mapa mapa, int *pause)
{
    int altura = ((30 + (TAM_PIXEL * mapa.dimensoes.linha)) - TAM_FONTE) / 2;
    int largura = ((TAM_PIXEL * mapa.dimensoes.coluna) - MeasureText("PAUSED", TAM_FONTE)) / 2;

    while(*pause)
    {
        BeginDrawing();
        DrawText("PAUSED", largura, altura, TAM_FONTE, WHITE);
        EndDrawing();
        if(IsKeyPressed(KEY_ENTER))
        {
            *pause = 0;
        }
    }
}
