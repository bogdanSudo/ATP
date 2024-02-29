#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "/Users/bogdanmica/Desktop/sem2.an1/ATP/seminar2-matrice/matrice.in"
#define FILE_NAME2 "/Users/bogdanmica/Desktop/sem2.an1/ATP/seminar2-matrice/matrice2.in"
#define MAX_ELEMENTS 30
#define MAX_LINES 10

void getMatrix(int **mat, int nrLin, int nrCol){
    printf("nr de linii = %d si nr de coloane = %d\n", nrLin, nrCol);
    for(int i = 0; i < nrLin; i++){
        for(int j = 0; j < nrCol; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int createMatrix(int ***matrix, int nrLin, int nrColumn){
    *matrix = malloc(nrLin * sizeof(int*));
    if(!(*matrix)){
        printf("nu s a alocat matricea\n");
        return -1;
    }
    for(int i = 0; i < nrLin; i++){
        (*matrix)[i] = malloc(nrColumn * sizeof(int));
        if(!(*matrix)[i]){
            printf("nu s a alocat linia pt matrice\n");
            return -1;
        }
    }
    return 0;
}

int readMatrix(FILE *fptr, int ***matrix, int nrLines, int nrColumn){
    int i,j;
    if(!(*matrix)){
        return -1;
    }
    for(i = 0; i < nrLines; i++){
        for(j = 0; j < nrColumn; j++){
            fscanf(fptr, "%d", &((*matrix)[i][j]));
        }
    }
    return 0;
}
int **readMatrixFile(char *fileName, int *nrLines, int *nrColumn){
    int **matrix,i,j;
    FILE *fptr = fopen(fileName, "r");
    if(fptr){
        fscanf(fptr, "%d", nrLines);
        fscanf(fptr, "%d", nrColumn);
        createMatrix(&matrix,*nrLines, *nrColumn);
        readMatrix(fptr, &matrix, *nrLines, *nrColumn);
    } else {
        return NULL;
    }

    return matrix;
}

/*
 * se citeste linia din fisier si separ numerele de spatiu
 * sa adaug elementele de tip int intr-un vector alocat dinamic
 */
int getLine(char *str, int **line, int *nrColumn){
    int nrElem = 0;
    *line = malloc(sizeof(int) * strlen(str));
    if(!(*line)){
        printf("nu s-a alocat linia pt matrice\n");
        return -1;
    }
    for(int i = 0; i < strlen(str); i = i + 2){
        (*line)[nrElem++] = str[i] - '0'; // ca sa obtin valoarea de tip int din char
    }
    *nrColumn = nrElem;
    return 0;
}
int **readEachLine(char *fileName, int *nrLin, int *nrCol){
    int **matrix, i, j;
    FILE *fptr;
    char *line = malloc(MAX_ELEMENTS * sizeof(char));
    *nrLin = 0;
    *nrCol = 0;

    if(!line){
        printf("nu s-a alocat string-ul pt linie\n");
        return NULL;
    }

    fptr = fopen(fileName, "r");
    if(!fptr){
        printf("nu s-a deschis fisierul\n");
        return  NULL;
    } else {
        while (fgets(line, MAX_ELEMENTS, fptr)) {
            *nrLin = (*nrLin) + 1;
        }
        rewind(fptr);
        matrix = malloc((*nrLin) * sizeof(int*));
        if(!matrix){
            printf("matricea nu s-a alocat\n");
            return NULL;
        } else {
            int nrCurrentLine =0;
            while (fgets(line, MAX_ELEMENTS, fptr)) {
                getLine(line, &matrix[nrCurrentLine++], nrCol);
            }
        }
    }
    return matrix;
}


void freeMatrix(int ***mat, int nrLin){
    int i,j;
    for(i = 0; i < nrLin; i++){
        free((*mat)[i]);
    }
    free(*mat);
}
int main() {
    int **matrix, nrLin, nrCol, i, j;
    int **matrix2;

    matrix = readMatrixFile(FILE_NAME, &nrLin, &nrCol);
    if(matrix) {
        getMatrix(matrix, nrLin, nrCol);
    }

    freeMatrix(&matrix, nrLin);
    printf("=====Citirea a doua fara nr de linii si coloane in fisier=====\n");

    matrix2 = readEachLine(FILE_NAME2, &nrLin, &nrCol);
    getMatrix(matrix2, nrLin, nrCol);

    return 0;
}
