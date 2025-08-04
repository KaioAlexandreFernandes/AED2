

#include<stdio.h>
#include<stdlib.h>

int converterLetraParaIndice(char letra) {
    if (letra == 32) return 0;
    return ((letra - 97) % 26) + 1;
}

int *lerSequenciaDeOrdenacao() {
    int *tabelaIndices = (int*)malloc(sizeof(int) * 27);
    int indiceTemporario;
    char sequenciaEntrada[26];

    scanf("%s", sequenciaEntrada);

    tabelaIndices[0] = 0;
    for (int i = 1; i < 27; i++) {
        indiceTemporario = converterLetraParaIndice(sequenciaEntrada[i - 1]);
        tabelaIndices[indiceTemporario] = i;
    }

    return tabelaIndices;
}

void converterMaiusculasParaMinusculas(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] < 'a')
            texto[i] += 32;
    }
}

char *criarCopiaPreenchida(char *textoOriginal, int tamanhoDesejado) {
    char *textoCopiado = (char*)malloc(sizeof(char) * tamanhoDesejado + 1);
    int posicaoOriginal = 0;
    
    for (int i = 0; i < tamanhoDesejado; i++) {
        if (textoOriginal[posicaoOriginal] != '\0')
            textoCopiado[i] = textoOriginal[posicaoOriginal++];
        else
            textoCopiado[i] = 32;
    }
    textoCopiado[tamanhoDesejado] = '\0';

    return textoCopiado;
}

int calcularTamanhoString(char *texto) {
    int tamanho;
    for (tamanho = 0; texto[tamanho] != '\0'; tamanho++);
    return tamanho;
}

void ordenarPorContagem(int *tabelaIndices, char **palavras, int totalPalavras, int posicaoCaractere) {
    int contador[27], indiceAtual;
    char **palavrasOrdenadas = (char**)malloc(sizeof(char*) * totalPalavras);

    for(int i = 0; i < 27; i++)
        contador[i] = 0;
    
    for (int i = 0; i < totalPalavras; i++) {
        indiceAtual = converterLetraParaIndice(palavras[i][posicaoCaractere]);
        contador[tabelaIndices[indiceAtual]]++;
    }

    for (int i = 1; i < 27; i++)
        contador[i] += contador[i - 1];

    for (int i = 0; i < 27; i++)
        printf("%d ", contador[i]);
    printf("\n");

    for (int i = totalPalavras - 1; i >= 0; i--) {
        indiceAtual = converterLetraParaIndice(palavras[i][posicaoCaractere]);
        palavrasOrdenadas[contador[tabelaIndices[indiceAtual]] - 1] = palavras[i];
        contador[tabelaIndices[indiceAtual]]--;
    }

    for (int i = 0; i < totalPalavras; i++)
        palavras[i] = palavrasOrdenadas[i];
        
    free(palavrasOrdenadas);
}

void ordenarPorRadix(int *tabelaIndices, char **palavras, int totalPalavras, int tamanhoMaximo) {
    for (int posicaoAtual = (tamanhoMaximo - 1); posicaoAtual >= 0; posicaoAtual--)
        ordenarPorContagem(tabelaIndices, palavras, totalPalavras, posicaoAtual);
}

int main() {
    int totalPalavras, tamanhoPalavra, tamanhoMaximo = 0;
    char palavraEntrada[20];

    scanf("%d", &totalPalavras);

    int *tabelaIndices = lerSequenciaDeOrdenacao();

    char **palavrasTemporarias = (char**)malloc(sizeof(char*) * totalPalavras);
    
    for (int i = 0; i < totalPalavras; i++) {
        scanf("%s", palavraEntrada);
        
        tamanhoPalavra = calcularTamanhoString(palavraEntrada);
        if (i == 0 || tamanhoPalavra > tamanhoMaximo) 
            tamanhoMaximo = tamanhoPalavra;
        
        converterMaiusculasParaMinusculas(palavraEntrada);
        
        palavrasTemporarias[i] = criarCopiaPreenchida(palavraEntrada, tamanhoPalavra);
        printf("%s.\n", palavrasTemporarias[i]);
    }
    
    printf("%d\n", tamanhoMaximo);
    
    char **palavrasParaOrdenar = (char**)malloc(sizeof(char*) * totalPalavras);
    
    for (int i = 0; i < totalPalavras; i++) { 
        palavrasParaOrdenar[i] = criarCopiaPreenchida(palavrasTemporarias[i], tamanhoMaximo);  
        free(palavrasTemporarias[i]);
    }
    free(palavrasTemporarias);

    ordenarPorRadix(tabelaIndices, palavrasParaOrdenar, totalPalavras, tamanhoMaximo);
    
    for (int i = 0; i < totalPalavras; i++) {
        puts(palavrasParaOrdenar[i]);
        free(palavrasParaOrdenar[i]);
    }
    free(palavrasParaOrdenar);

    return 0;
}
