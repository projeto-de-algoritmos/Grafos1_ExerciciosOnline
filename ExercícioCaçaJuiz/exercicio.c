int findJudge(int n, int** trust, int trustSize, int* trustColSize) {

    int* grauEntrada = (int*)malloc((n+1) * sizeof(int));
    int* grauSaida = (int*)malloc((n+1) * sizeof(int));

    memset(grauEntrada, 0, (n+1) * sizeof(int));
    memset(grauSaida, 0, (n+1) * sizeof(int));

    for(int i = 0; i < trustSize; i++) {
        grauSaida[trust[i][0]]++;
        grauEntrada[trust[i][1]]++;
    }

    for(int i = 1; i <= n; i++) {
        if(grauEntrada[i] == n - 1 && grauSaida[i] == 0) {
            free(grauEntrada);
            free(grauSaida);
            return i;
        }
    }

    free(grauEntrada);
    free(grauSaida);
    return -1;
}