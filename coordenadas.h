#ifndef COORDENADAS_B
#define COORDENADAS_B

/*  TIPO LOCALIZACAO CRIADO:

    int linha  - Representa a coordenada X da posi��o/localiza��o do mapa
    int coluna - Representa a coordenada Y da posi��o/localiza��o do mapa

*/

typedef struct
{
    int linha, coluna;
}Localizacao;

Localizacao localizacao_cria(int linha, int coluna);

#endif // COORDENADAS_H
