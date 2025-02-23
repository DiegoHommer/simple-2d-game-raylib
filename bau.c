#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "mapa.h"

#define MAXG 10000

/*
    Mapa *mapa - Endere�o de uma vari�vel do tipo Mapa (fun��o coloca a chave, bombas e gemas nos ba�s do mapa)
*/
void inicializa_baus(Mapa *mapa)
{
    srand(time(NULL));
    int i, gema;


    // ESVAZIA TODOS OS BA�S DO VETOR
    for(i = 0; i < MAXBAUS; i++)
    {
        mapa->baus[i].conteudo = ' ';
    }

    int bau_chave = rand() % mapa->numeroBaus;  // Salva um n�mero aleat�rio de 0 at� mapa->numeroBaus em bau_chave
    int bau_bomba;

    mapa->baus[bau_chave].conteudo = 'K';       // Coloca chave dentro do ba� com essa posi��o no vetor de ba�s

    // Insere mapa->nivel bombas no vetor de ba�s
    for(i = 0; i < mapa->nivel; i++)
    {
        // Repete intera��o at� encontrar um ba� vazio para colocar a bomba
        do{
            bau_bomba = rand() % mapa->numeroBaus;     // Salva um n�mero aleat�rio de 0 at� mapa->numeroBaus em bau_bomba
            if(bau_bomba != bau_chave)                 // Se esse n�mero � diferente do bau_chave (ba� est� vazio)
            {
                mapa->baus[bau_bomba].conteudo = 'B';  // Coloca bomba dentro do ba� com essa posi��o no vetor de ba�s
            }
        }while(bau_bomba == bau_chave);
    }

    // Insere gemas nos ba�s restantes (vazios) do vetor de ba�s
    for(i = 0; i < mapa->numeroBaus; i++)
    {
        gema = 1 + rand() % (MAXG);                            // gema recebe um n�mero aleat�rio de 1 a 10000
        if(mapa->baus[i].conteudo == ' ')                      // Se o ba� da posi��o i do vetor est� vazio
        {
            mapa->baus[i].conteudo = gera_gema(mapa, gema);    // Insere uma gema aleat�ria dentro desse ba�
        }
    }
}

/*
    Mapa *mapa - Endere�o de uma vari�vel do tipo Mapa (fun��o gera uma gema para ser inserida num ba�)
*/
char gera_gema(Mapa *mapa, int gema)
{
    int probabilidade = 1000 * (mapa->nivel - 1); // probabilidade que muda conforme o n�vel

    if(gema > (6000 + (probabilidade * 1.5)))         // Ametista(!) : Chance inicial de 40% -> Diminui 15% a cada n�vel
    {
        return '!';
    }
    else if(gema > (4000 + (probabilidade * 1.75)))   // Safira(@)   : Chance inicial de 20% -> Diminui 2,5% a cada n�vel
    {
        return '@';
    }
    else if(gema > (2000 + probabilidade * 1.75))     // Rubi(#)     : Chance inicial de 20% -> Se mant�m constante a cada n�vel
    {
        return '#';
    }
    else if(gema > (500 + (probabilidade * 1.25)))    // Anel($)     : Chance inicial de 15% -> Aumenta 5% a cada n�vel
    {
        return '$';
    }
    else                                              // Coroa(%)    : Chance inicial de 5%  -> Aumenta 12,5% a cada n�vel
    {
        return '%';
    }
}

/*
    Mapa *mapa - Endere�o de uma vari�vel do tipo Mapa (fun��o abre um ba� e verifica seu conte�do)
*/
void abre_bau(Mapa *mapa)
{
    int i;
    for(i = 0; i < mapa->numeroBaus; i++)
    {
        // Se o jogador est� sobre o bau de posi��o i do vetor, verifica o conte�do desse ba�...
        if(mapa->player.posicaoJ.linha == mapa->baus[i].posicaoB.linha && mapa->player.posicaoJ.coluna == mapa->baus[i].posicaoB.coluna)
        {
            switch(mapa->baus[i].conteudo)
            {
                // SE BA� CONT�M UMA CHAVE
                case 'K':
                    mapa->player.chave = 1;                                                     // flag de chave se torna verdadeiro
                    jog_aumenta_pontuacao(&mapa->player, 1000);                                 // Jogador ganha 1000 pontos
                    mapa->matriz[mapa->posicaoSaida.linha][mapa->posicaoSaida.coluna] = 'P';    // Sa�da aparece no mapa
                    break;

                // SE BA� CONT�M UMA BOMBA
                case 'B':
                    jog_aumenta_pontuacao(&mapa->player, -500); // Jogador perde 500 pontos
                    mapa_diminui_vida(mapa);
                    // Jogador perde uma vida e volta � posi��o inicial do mapa
                    break;

                // SE BA� CONT�M UMA COROA
                case '%':
                    jog_aumenta_pontuacao(&mapa->player, 300);  // Jogador ganha 300 pontos
                    break;

                // SE BA� CONT�M UM ANEL
                case '$':
                    jog_aumenta_pontuacao(&mapa->player, 200);  // Jogador ganha 200 pontos
                    break;

                // SE BA� CONT�M UM RUBI
                case '#':
                    jog_aumenta_pontuacao(&mapa->player, 150);  // Jogador ganha 150 pontos
                    break;

                // SE BA� CONT�M UMA SAFIRA
                case '@':
                    jog_aumenta_pontuacao(&mapa->player, 100);  // Jogador ganha 100 pontos
                    break;

                // SE BA� CONT�M UMA AMETISTA
                case '!':
                    jog_aumenta_pontuacao(&mapa->player, 50);  // Jogador ganha 50 pontos
                    break;

                // SE BA� EST� QUEIMADO OU VAZIO
                default:
                    break;
            }

            if(mapa->baus[i].conteudo == 'B') // Se ba� continha uma bomba...
            {
                mapa->baus[i].conteudo = '*'; // Ba� fica queimado
            }                                 // Sen�o...
            else
            {
                mapa->baus[i].conteudo = ' '; // Ba� fica vazio ap�s ser aberto
            }
        }
    }
}
