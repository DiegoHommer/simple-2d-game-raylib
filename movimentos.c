#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mapa.h"

/*
    Mapa *mapa - Endere�o de uma vari�vel do tipo Mapa (fun��o atualiza o mapa para derrubar jogador enquanto ele estiver flutuando)
*/
void gravidade(Mapa *mapa)
{
    char* posicaoAtual = &(mapa->matriz[mapa->player.posicaoJ.linha][mapa->player.posicaoJ.coluna]);
    char* posicaoAbaixo = &(mapa->matriz[mapa->player.posicaoJ.linha + 1][mapa->player.posicaoJ.coluna]);

    if(!(mapa->escada))
    {
        // SE JOGADOR EST� ACIMA DE UM BA�
        if (*posicaoAbaixo == 'C')
        {
            mapa->bau = 1;
        }
        // SE JOGADOR EST� ACIMA DA SA�DA
        else if(*posicaoAbaixo == 'P')
        {
            mapa->player.queda = 0;
            mapa->nivel++;
        }
        // SE JOGADOR EST� ACIMA DE UMA PORTA
        else
        {
            mapa->porta = *posicaoAbaixo;
        }

        *posicaoAtual = ' ';
        *posicaoAbaixo = 'D';
        (mapa->player.queda)++;
    }
}


/*
    Mapa *mapa  - Endere�o de uma vari�vel do tipo Mapa (fun��o atualiza o mapa para movimentos verticais v�lidos do jogador)
    int direcao - Inteiro que representa a direcao para qual o usu�rio deseja movimentar o jogador (-1 para cima, 1 para baixo)
*/
void movimenta_vertical(Mapa *mapa, int direcao)
{
    Localizacao local_porta;       // Inicia vari�vel do tipo localiza��o que representa a posi��o de uma porta
    char* posicaoAtual = &(mapa->matriz[mapa->player.posicaoJ.linha][mapa->player.posicaoJ.coluna]);
    char* posicaoSeguinte = &(mapa->matriz[mapa->player.posicaoJ.linha + direcao][mapa->player.posicaoJ.coluna]);

    // SE JOGADOR ENTROU EM UMA PORTA
    if(mapa->porta != ' ' && direcao == -1)
    {
        mapa_busca_porta(*mapa, mapa->porta, &local_porta);
        *posicaoAtual = mapa->porta;
        mapa->matriz[local_porta.linha][local_porta.coluna] = 'D';
    }

    // SE JOGADOR ABRIU UM BA�
    else if(mapa->bau == 1 && direcao == -1)
    {
        abre_bau(mapa);
    }

    else if(*posicaoSeguinte != 'X')
    {
        // MOVIMENTA��O SE JOGADOR EST� SOBRE UMA ESCADA
        if(mapa->escada)
        {
            // SE POSI��O PARA ONDE JOGADOR DESEJA SE MOVER EST� COM A SA�DA
            if(*posicaoSeguinte == 'P')
            {
                mapa->nivel++;
            }
            // SE POSI��O PARA ONDE JOGADOR DESEJA SE MOVER N�O EST� COM UMA ESCADA
            else if(*posicaoSeguinte != 'H')
            {
                // SE POSI��O PARA ONDE JOGADOR DESEJA SE MOVER EST� COM UM BA�
                if(*posicaoSeguinte == 'C')
                {
                    mapa->bau = 1;
                }

                // SE POSI��O PARA ONDE JOGADOR DESEJA SE MOVER EST� COM UMA PORTA
                else if(*posicaoSeguinte != ' ')
                {
                    mapa->porta = *posicaoSeguinte;
                }
                mapa->escada = 0;
            }
            *posicaoAtual = 'H';
            *posicaoSeguinte = 'D';
        }
        // MOVIMENTA��O SE O JOGADOR EST� ACIMA DE UMA ESCADA E JOGADOR DESCEU
        else if(direcao == 1 && *posicaoSeguinte == 'H')
        {
            if(mapa->bau)
            {
                *posicaoAtual = 'C';
                mapa->bau = 0;
            }
            else if(mapa->porta != ' ')
            {
                *posicaoAtual = mapa->porta;
                mapa->porta = ' ';
            }
            else
            {
                *posicaoAtual = ' ';
            }
            *posicaoSeguinte = 'D';
            mapa->escada = 1;
        }
    }
}

/*
    Mapa *mapa  - Endere�o de uma vari�vel do tipo Mapa (fun��o atualiza o mapa para movimentos horizontais v�lidos do jogador)
    int direcao - Inteiro que representa a direcao para qual o usu�rio deseja movimentar o jogador (-1 para esquerda, 1 para direita)
*/
void movimenta_horizontal(Mapa *mapa, int direcao)
{
    char* posicaoAtual = &(mapa->matriz[mapa->player.posicaoJ.linha][mapa->player.posicaoJ.coluna]);
    char* posicaoSeguinte = &(mapa->matriz[mapa->player.posicaoJ.linha][mapa->player.posicaoJ.coluna + direcao]);

    // SE JOGADOR EST� TENTANDO SE DESLOCAR PARA UMA CASA V�LIDA
    if(*posicaoSeguinte != 'X')
    {
        // SE JOGADOR EST� SOBRE UMA ESCADA
        if(mapa->escada == 1)
        {
            *posicaoAtual = 'H';
            mapa->escada = 0;
        }
        // SE JOGADOR EST� SOBRE UM BA�
        else if(mapa->bau == 1)
        {
            *posicaoAtual = 'C';
            mapa->bau = 0;
        }
        // SE JOGADOR EST� SOBRE UMA PORTA
        else if(mapa->porta != ' ')
        {
            *posicaoAtual = mapa->porta;
            mapa->porta = ' ';
        }
        // SE JOGADOR EST� SOBRE VAZIO
        else
        {
            *posicaoAtual = ' ';
        }

        // SE POSI��O PARA ONDE JOGADOR DESEJA SE MOVER � A SA�DA
        if(*posicaoSeguinte == 'P')
        {
            mapa->nivel++;
        }
        // SE POSI��O PARA QUAL JOGADOR DESEJA SE MOVER EST� COM UMA ESCADA
        else if(*posicaoSeguinte == 'H')
        {
            mapa->escada = 1;
        }
        // SE POSI��O PARA QUAL JOGADOR DESEJA SE MOVER EST� COM UM BA�
        else if(*posicaoSeguinte == 'C')
        {
            mapa->bau = 1;
        }
        // SE POSI��O PARA QUAL JOGADOR DESEJA SE MOVER EST� COM UMA PORTA
        else if(*posicaoSeguinte != ' ')
        {
            mapa->porta = *posicaoSeguinte;
        }

        *posicaoSeguinte = 'D';
    }
}
