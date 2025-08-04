#include<stdio.h>
#include<stdlib.h>

typedef struct NoArvore {
    int valor;
    int altura;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

int alturaMaxima(int a, int b) {
    if (a > b) return a;
    return b;
}

int obterAltura(NoArvore *no) {
    if (no != NULL)
        return no->altura;
    return 0;
}

void atualizarAltura(NoArvore *no) {
    if (no != NULL)
        no->altura = 1 + alturaMaxima(obterAltura(no->esquerda), obterAltura(no->direita));
}

int fatorBalanceamento(NoArvore *no) {
    if (no != NULL)
        return obterAltura(no->esquerda) - obterAltura(no->direita);
    return 0;
}

NoArvore *rotacionarDireita(NoArvore *raiz) {
    NoArvore *pivo = raiz->esquerda;
    raiz->esquerda = pivo->direita;
    pivo->direita = raiz;
    
    atualizarAltura(raiz);
    atualizarAltura(pivo);
    
    return pivo;
}

NoArvore *rotacionarEsquerda(NoArvore *raiz) {
    NoArvore *pivo = raiz->direita;
    raiz->direita = pivo->esquerda;
    pivo->esquerda = raiz;
    
    atualizarAltura(raiz);
    atualizarAltura(pivo);
    
    return pivo;
}

NoArvore *rotacionarEsquerdaDireita(NoArvore *raiz) {
    raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
    return rotacionarDireita(raiz);
}

NoArvore *rotacionarDireitaEsquerda(NoArvore *raiz) {
    raiz->direita = rotacionarDireita(raiz->direita);
    return rotacionarEsquerda(raiz);
}

NoArvore *criarNo(int valor) {
    NoArvore *novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->valor = valor;
    novoNo->altura = 1;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

NoArvore *inserirNo(NoArvore *raiz, int valor) {
    if (raiz == NULL)
        return criarNo(valor);
    
    if (valor < raiz->valor)
        raiz->esquerda = inserirNo(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserirNo(raiz->direita, valor);
    else
        return raiz;

    atualizarAltura(raiz);
    int balanceamento = fatorBalanceamento(raiz);

    if (balanceamento > 1 && valor < raiz->esquerda->valor)
        return rotacionarDireita(raiz);

    if (balanceamento < -1 && valor > raiz->direita->valor)
        return rotacionarEsquerda(raiz);

    if (balanceamento > 1 && valor > raiz->esquerda->valor)
        return rotacionarEsquerdaDireita(raiz);
    
    if (balanceamento < -1 && valor < raiz->direita->valor)
        return rotacionarDireitaEsquerda(raiz);

    return raiz;
}

NoArvore *encontrarMenorValor(NoArvore *no) {
    NoArvore *atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

NoArvore *removerNo(NoArvore *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    
    if (valor < raiz->valor)
        raiz->esquerda = removerNo(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = removerNo(raiz->direita, valor);
    else {
        NoArvore *temp;
        if (raiz->esquerda == NULL) {
            temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        NoArvore *sucessor = encontrarMenorValor(raiz->direita);
        raiz->valor = sucessor->valor;
        raiz->direita = removerNo(raiz->direita, sucessor->valor);
    }

    if (raiz == NULL)
        return raiz;
    
    atualizarAltura(raiz);
    
    int balanceamento = fatorBalanceamento(raiz);
    int balanceamentoEsquerdo = fatorBalanceamento(raiz->esquerda);
    int balanceamentoDireito = fatorBalanceamento(raiz->direita);

    if (balanceamento > 1 && balanceamentoEsquerdo >= 0)
        return rotacionarDireita(raiz);

    if (balanceamento > 1 && balanceamentoEsquerdo < 0)
        return rotacionarEsquerdaDireita(raiz);

    if (balanceamento < -1 && balanceamentoDireito <= 0)
        return rotacionarEsquerda(raiz);
    
    if (balanceamento < -1 && balanceamentoDireito > 0)
        return rotacionarDireitaEsquerda(raiz);

    return raiz;
}

void liberarArvore(NoArvore *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int buscarValor(NoArvore *raiz, int valor) {
    if (raiz != NULL) {
        if (valor == raiz->valor)
            return 1;

        if (valor < raiz->valor)
            return buscarValor(raiz->esquerda, valor);
        else
            return buscarValor(raiz->direita, valor);
    }
    return 0;
}

void imprimirArvore(NoArvore *raiz, int inicio, int fim, int maior) {
    if (raiz != NULL) {
        imprimirArvore(raiz->esquerda, inicio, fim, maior);
 
        if (raiz->valor >= inicio && raiz->valor <= fim) {
            printf("%d", raiz->valor);
            
            if (raiz->valor < maior)
                printf(", ");
        }
 
        imprimirArvore(raiz->direita, inicio, fim, maior);
    }
}

void imprimirAlturas(NoArvore *raiz, int inicio, int fim) {
    if (raiz != NULL) {
        imprimirAlturas(raiz->esquerda, inicio, fim);
        
        if (raiz->valor >= inicio && raiz->valor <= fim)
            printf("%d, %d, %d\n", alturaMaxima(obterAltura(raiz->esquerda), obterAltura(raiz->direita)), obterAltura(raiz->esquerda), obterAltura(raiz->direita));
 
        imprimirAlturas(raiz->direita, inicio, fim);
    }
}

int main() {
    int numero, inicio, fim, maior = -1;
    NoArvore *raiz = NULL;

    while(1) {
        scanf("%d", &numero);

        if (numero >= 0)
            raiz = inserirNo(raiz, numero);
        else break;
    }

    printf("%d, %d, %d\n", alturaMaxima(obterAltura(raiz->esquerda), obterAltura(raiz->direita)), obterAltura(raiz->esquerda), obterAltura(raiz->direita));
    
    while (1) {
        scanf("%d", &numero);
        
        if (numero >= 0) {
            if (buscarValor(raiz, numero))
                raiz = removerNo(raiz, numero);
            else
                raiz = inserirNo(raiz, numero);
        } else break;
    }
    
    if (raiz != NULL)
        printf("%d, %d, %d\n", alturaMaxima(obterAltura(raiz->esquerda), obterAltura(raiz->direita)), obterAltura(raiz->esquerda), obterAltura(raiz->direita));
    else
        printf("ARVORE VAZIA\n");

    scanf("%d %d", &inicio, &fim);

    for (int i = inicio; i <= fim; i++) {
        if (buscarValor(raiz, i)) {
            if (maior == -1)
                maior = i;
            else if (i > maior)
                maior = i;
        }
    }

    if (maior > 0) {
        imprimirArvore(raiz, inicio, fim, maior);
        printf("\n");

        imprimirAlturas(raiz, inicio, fim);
    } else
        printf("NADA A EXIBIR\n");

    liberarArvore(raiz);

    return 0;
}
