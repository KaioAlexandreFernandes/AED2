
#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int *keys;
    int total_keys;
    int leaf;
    struct No *pai;
    struct No **filhos;
} No;


No *criarNo(int leaf, No *pai, int m) {
    No *novo = (No*)malloc(sizeof(No));

    novo->keys = (int*)malloc(sizeof(int) * (2 * m + 1)); // aloca 1 espaco a mais para quando tranbordar
    novo->filhos = (No**)malloc(sizeof(No*) * (2 * m + 2));
    novo->total_keys = 0;
    novo->leaf = leaf;
    
    for (int i = 0; i < (2 * m + 2); i++)
        novo->filhos[i] = NULL;

    novo->pai = pai;
    
    return novo;
}


int inserirEmOrdem(No *raiz, int key) {
    int i = raiz->total_keys - 1;

    while (i >= 0 && key < raiz->keys[i]) {
        raiz->keys[i + 1] = raiz->keys[i];
        i--;
    }
    raiz->keys[i + 1] = key;
    raiz->total_keys++;

    return i + 1;
}


No *dividir(No *raiz, int m) {
    int mediana = m;
    int i, j;
    
    if (raiz->pai == NULL) {
        No *nova_raiz = criarNo(0, NULL, m);
        nova_raiz->filhos[0] = raiz;
        raiz->pai = nova_raiz;
    }
    
    No *pai = raiz->pai;
    No *novo = criarNo(raiz->leaf, pai, m);
    
    j = 0;
    for (i = mediana + 1; i < raiz->total_keys; i++)
        novo->keys[j++] = raiz->keys[i];
    novo->total_keys = j;
    raiz->total_keys = mediana;
    
    // copia os filhos
    if (!raiz->leaf) {
        j = 0;
        for (i = mediana + 1; i <= 2 * m + 1; i++) {
            novo->filhos[j] = raiz->filhos[i];

            if (novo->filhos[j]) 
                novo->filhos[j]->pai = novo;

            raiz->filhos[i] = NULL;
            j++;
        }
    }
    
    int key_mediana = raiz->keys[mediana]; // armazena o valor da mediana
    int pos = inserirEmOrdem(pai, key_mediana); // insere o valor e armazena a posição em que foi inserido

    // ajeita os filhos para inserir o novo filho na posição correta
    for (j = pai->total_keys; j > pos + 1; j--)
        pai->filhos[j] = pai->filhos[j - 1];

    pai->filhos[pos + 1] = novo;

    // verifica se o nó pai transbordou
    if (pai->total_keys > 2 * m)
        return dividir(pai, m);

    // navega até a raiz para retorna-la
    while (pai->pai != NULL)
        pai = pai->pai;

    return pai;
}


No *buscar(No *raiz, int key) {
    if (raiz != NULL) {
        int i = 0;
        
        while (i < raiz->total_keys && key > raiz->keys[i])
        i++;
        
        if (i < raiz->total_keys && key == raiz->keys[i])
        return raiz;  // retorna a pagina do valor procurado
        
        if (raiz->leaf)
            return NULL;  // não encontrado 
        
        return buscar(raiz->filhos[i], key);
    }

    return NULL;
}


No *inserir(No *raiz, int key, int m) {
    // verifica se o valor ja esta presente na arvore
    if (raiz != NULL && buscar(raiz, key))
        return raiz;

    if (raiz == NULL) {
        raiz = criarNo(1, NULL, m);

        raiz->keys[0] = key; 
        raiz->total_keys = 1;

        return raiz;
    }

    if (raiz->leaf) {
        // insere o elemento de forma ordenada
        inserirEmOrdem(raiz, key);

        // se ultrapassou o maximo, divide o nó
        if (raiz->total_keys > 2 * m)
            return dividir(raiz, m);
        else 
            return raiz;
    }

    int i = 0;
    
    // encontra a posição ideal para colocar o valor
    while (i < raiz->total_keys && key > raiz->keys[i]) i++;

    No *filho_original = raiz->filhos[i];
    No *resultado = inserir(filho_original, key, m);
    
    // verifica se houve alteração na estrutura da arvore
    if (resultado != filho_original)
        return resultado; // retorna o resultado da alteração

    if (raiz->total_keys > 2 * m)
        return dividir(raiz, m);

    return raiz;
}


void liberarArvore(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    
    if (!raiz->leaf) {
        for (int i = 0; i <= raiz->total_keys; i++) {
            liberarArvore(raiz->filhos[i]);
        }
    }

    free(raiz->keys);
    free(raiz->filhos);
    free(raiz);
}


int main() {
    No *raiz = NULL;
    int num, m;

    scanf("%d", &m);

    while (1) {
        scanf("%d", &num);

        if (num < 0) break;

        raiz = inserir(raiz, num, m);
    }

    scanf("%d", &num);
    
    printf("%d\n", raiz->total_keys);

    // armazena o nó pesquisado
    No *pesquisado = buscar(raiz, num);

    // se encontrou imprime o resultado
    if (pesquisado) {
        printf("%d\n", pesquisado->total_keys);

        for (int i = 0; i < pesquisado->total_keys; i++)
            printf("%d ", pesquisado->keys[i]);
        printf("\n");
    } else 
        printf("Valor nao encontrado\n");

    liberarArvore(raiz);
    free(pesquisado);

    return 0;
}
