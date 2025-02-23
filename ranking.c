#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "mapa.h"
#include "raylib.h"
#include "ranking.h"


#define ARQUIVO_RANKING "ranking.txt"
#define ARQUIVO_SAVE "jogo.dat"
#define TAM_NOME 10
#define POS_Y_TEXTO 100
#define DESLOCA_Y_TEXTO 50

/*
    char nome[NOMEMAX] - Nome de um jogador que ser� inserido numa estrutura do tipo Ranking
    int pontuacao      - Pontuacao de um jogador que ser� inserida numa estrutura do tipo Ranking
*/
Ranking cria_ranking(char nome[NOMEMAX], int pontuacao)
{
    Ranking ranking;
    strcpy(ranking.nome, nome);
    ranking.pontuacao = pontuacao;
    return ranking;
}

/*
    Ranking entradas[VETORMAX] - Vetor de rankings respons�vel por guardar o ranking de no m�ximo 5 jogadores
    int ocupacao - N�mero de endere�os ocupados no vetor de rankings
*/
void salva_rankings(Ranking entradas[VETORMAX], int ocupacao)
{
    FILE *arquivo;
    int i = 0;
    arquivo = fopen(ARQUIVO_RANKING, "w");
    if(arquivo)
    {
        while(i < ocupacao) // Enquanto i for menor que ocupa��o...
        {
            // Guarda o nome e a pontua��o do jogador do ranking[i] no arquivo.txt
            fputs(entradas[i].nome, arquivo);
            fprintf(arquivo, " ");
            fprintf(arquivo, "%d", entradas[i].pontuacao);
            fprintf(arquivo, "\n");
            i++;
        }
    }else
        printf(" Arquivo nao pode ser aberto!\n");
    fclose(arquivo);
}

/*
    Ranking entradas[VETORMAX] - Vetor de rankings respons�vel por guardar o ranking de no m�ximo 5 jogadores
    int *ocupacao - Endere�o da vari�vel que representa o n�mero de endere�os ocupados no vetor de rankings
*/
void carrega_rankings(Ranking entradas[VETORMAX], int *ocupacao)
{
    FILE *arquivo;
    int i = 0;         // Contador para preencher vetor inicia com 0.
    *ocupacao = 0;     // Conte�do de ocupa��o inicia com 0 (ser� incrementado conforme vetor � preenchido)
    int valores_lidos;
    char nome[NOMEMAX];
    int pontuacao;
    arquivo = fopen("ranking.txt", "r");
    if(arquivo)
    {
        while(!feof(arquivo))  // Enquanto n�o chegou ao fim do arquivo
        {
            // Valores_lidos recebe o n�mero de informa��es lidas pelo comando fscanf
            valores_lidos = fscanf(arquivo, "%s %d", nome, &pontuacao);

            // Se o fscanf leu pelo menos uma informa��o... (arquivo n�o est� no fim)
            if(valores_lidos > 0)
            {
                strcpy(entradas[i].nome, nome);     // Copia o nome lido do arquivo para o nome do ranking[i] do vetor
                entradas[i].pontuacao = pontuacao;  // Copia a pontua��o lida para a pontua��o do ranking[i] do vetor
                (*ocupacao)++;                      // Incrementa 1 � ocupa��o
                i++;                                // Incrementa 1 ao contador
            }
        }
    }else
        printf(" Arquivo nao pode ser aberto!\n");
    fclose(arquivo);
}

/*
    Ranking entradas[VETORMAX] - Vetor de rankings respons�vel por guardar o ranking de no m�ximo 5 jogadores
    int ocupacao - Vari�vel que representa o n�mero de endere�os ocupados no vetor de rankings
*/
void imprime_rankings(Ranking entradas[VETORMAX], int ocupacao)
{
    const int screenWidth = 550;
    const int screenHeight = 450;
    int i;
    char nome[NOMEMAX];
    int fecha = 1;
    SetWindowSize(screenWidth, screenHeight);

    while (fecha)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha as posi��es e os campos de nome e pontua��o
        DrawText("1ST", 100, 100, 20, BLACK);
        DrawText("2ND", 100, 150, 20, BLACK);
        DrawText("3RD", 100, 200, 20, BLACK);
        DrawText("4TH", 100, 250, 20, BLACK);
        DrawText("5TH", 100, 300, 20, BLACK);
        DrawText("Name", 200, 50, 20, BLACK);
        DrawText("Score", 350, 50, 20, BLACK);

        for(i = 0; i < ocupacao; i++)
        {
            DrawText(entradas[i].nome, 200, POS_Y_TEXTO + (i * DESLOCA_Y_TEXTO), 20, BLACK);
            DrawText(itoa(entradas[i].pontuacao, nome, 10), 350, POS_Y_TEXTO + (i * DESLOCA_Y_TEXTO), 20, BLACK);
        }

        if(IsKeyPressed(KEY_SPACE))
        {
            fecha = 0;
        }

        EndDrawing();
    }
}

/*
    Ranking entradas[VETORMAX] - Vetor de rankings respons�vel por guardar o ranking de no m�ximo 5 jogadores
    int *ocupacao - Endere�o da vari�vel que representa o n�mero de endere�os ocupados no vetor de rankings
    Ranking novo_jogador - Vari�vel do tipo Ranking que ser� adicionada ao vetor de rankings adequadamente
*/
void adiciona_ranking(Ranking entradas[VETORMAX], int *ocupacao, Ranking novo_jogador)
{
    Ranking aux, aux2; // Vari�veis auxiliares do tipo ranking para fazer as substitui��es
    int i, j;
    int fim = 1;
    if(*ocupacao == 0) // Se vetor de rankings n�o est� com nenhum ranking...
    {
        entradas[*ocupacao] = novo_jogador; // Adiciona novo_jogador na primeira posi��o
        (*ocupacao)++;                      // Incrementa 1 � ocupa��o
    }else              // Sen�o...
    {
        for(i = 0; i < (*ocupacao) && fim; i++) // Itera��o que repete enquanto i for menor que a ocupa��o do vetor e fim for verdadeiro
        {
            // Se a pontua��o da posi��o i � menor ou igual a pontua��o do novo_jogador...
            if(entradas[i].pontuacao <= novo_jogador.pontuacao)
            {
                aux = entradas[i];                     // aux guarda o ranking da posi��o i
                entradas[i] = novo_jogador;            // novo_jogador � colocado nessa posi��o
                for(j = i + 1; j < (*ocupacao); j++)  // Itera��o para "deslocar para a direita" o resto do vetor
                {
                    aux2 = entradas[j];
                    entradas[j] = aux;
                    aux = aux2;
                }
                fim = 0;                               // flag de fim se torna falsa
                if(*ocupacao < 5)                      // Se ocupa��o � menor que 5 e novo_jogador foi inserido...
                    (*ocupacao)++;                     // incrementa 1 � ocupa��o

            }
        }
        // Se fim � verdadeiro (n�o foi encontrado um ranking com pontua��o menor ou igual ao novo_jogador) e ocupa��o � menor que 5
        if(fim && *ocupacao < 5)
        {
            entradas[i] = novo_jogador; // Coloca jogador na primeira posi��o n�o ocupada do vetor
            (*ocupacao)++;              // Incrementa 1 � ocupa��o
        }
    }
}

void recebe_nome(Mapa *mapa)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetWindowSize(screenWidth, screenHeight);

    char nome[TAM_NOME + 1] = "\0";
    int contador = 0;
    int flag = 1;

    bool mouseTexto = false;

    Rectangle caixa_nome = { screenWidth/2.0f - 100, 180, 225, 50 };

    while (flag)
    {
        if (CheckCollisionPointRec(GetMousePosition(), caixa_nome))
        {
            mouseTexto = true;
        }

        else
        {
            mouseTexto = false;
        }
        if(mouseTexto)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int caracter = GetCharPressed();

                while (caracter > 0)
                {
                    if ((caracter >= 32) && (caracter <= 125) && (contador < TAM_NOME))
                    {
                        nome[contador] = (char)caracter;
                        nome[contador + 1] = '\0';
                        contador++;
                    }

                    caracter = GetCharPressed();
                }

                if(IsKeyPressed(KEY_BACKSPACE))
                {
                    contador--;
                    if(contador < 0)
                        contador = 0;
                    nome[contador] = '\0';
                }

            if(IsKeyPressed(KEY_ENTER))
            {
                strcpy(mapa->player.nome, nome);
                flag = 0;
            }

        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);


        if(flag)
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("DIGITE O NOME DO JOGADOR", 260, 140, 20, DARKGREEN);
            DrawRectangleRec(caixa_nome, LIGHTGRAY);
            if (mouseTexto)
            {
                DrawRectangleLines((int)caixa_nome.x, (int)caixa_nome.y, (int)caixa_nome.width, (int)caixa_nome.height, GREEN);
            }
            else
            {
                DrawRectangleLines((int)caixa_nome.x, (int)caixa_nome.y, (int)caixa_nome.width, (int)caixa_nome.height, DARKGRAY);
            }
            DrawText(nome, (int)caixa_nome.x + 5, (int)caixa_nome.y + 8, 40, DARKBLUE);

            EndDrawing();
        }

    }
}




