#include "coordenadas.h"

/*
    int linha  - Inteiro que representa a coordenada X da posi��o/localiza��o
    int coluna - Inteiro que representa a coordenada Y da posi��o/localiza��o
 */
Localizacao localizacao_cria(int linha, int coluna)
{
    Localizacao posicao = {linha, coluna};
    return posicao;
}
