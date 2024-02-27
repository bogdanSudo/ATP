#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 99999
/*
 elementul minim si nr de elemente egale cu el
 din triunghiul aflat sub diagonala secundara a unei matrice ptr.
 masivele alocate dinamic
 */

int allocateMatrix(int ***mat, int nrElem) {
    *mat = malloc(sizeof(int*) * nrElem);
    if(!(*mat)){
        printf("eroare la alocare matrice\n");
        return -1;
    }
    for(int i = 0; i < nrElem; i++){
        (*mat)[i] = malloc(sizeof(int) * nrElem);
        if(!((*mat)[i])){
            printf("eroare la alocare vector\n");
            return -1;
        }
    }
    return 0;
}
int createPositionMatrix(int ***posMatrix, int minElemNr){
    int i;
    *posMatrix = malloc(minElemNr * sizeof(int*));
    if(!(*posMatrix)){
        printf("nu s-a alocat matricea de pozitii\n");
        return -1;
    }
    for (i = 0; i < minElemNr;i++){
        (*posMatrix)[i] = malloc(sizeof(int) * 2);
        if(!((*posMatrix)[i])){
            printf("nu s-a alocat vectorul pt indici\n");
            return -1;
        }
    }
    return 0;
}
void freePositionMatrix (int **posMatrix, int nrLines){
    for(int i = 0; i < nrLines;i++){
        free(posMatrix[i]);
    }
    free(posMatrix);
}
void readMatrix(int ***mat, int nrElem) {
    int i,j, funcResult;
    for(i = 0; i < nrElem; i++){
        for(j = 0; j < nrElem; j++){
            printf("mat[%d][%d] = ",i, j);
            scanf("%d", &((*mat)[i][j]));
        }
    }
}

void getMatrix(int **mat, int nrElem){
    int i,j;
    for(i = 0; i < nrElem; i++){
        for(j = 0; j < nrElem; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

//afiseaza matricea cu pozitii
void getPositionMatrix(int **posMatrix, int nrApp){
    int i,j;
    for(i = 0; i < nrApp; i++){
        printf("elem cu indicii %d %d\n", posMatrix[i][0], posMatrix[i][1]);
    }
}

//conditia ca un elem sa fie sub diag secundara
int secondaryTriangle(int i, int j, int nrElem){
    if (i+j >= nrElem -1)
        return 1;

    return 0;
}
int getMinElement(int **mat, int nrElem){
    int minVal = MAX_VALUE, i, j;
    for(i = 0; i < nrElem; i++){
        for(j = 0; j < nrElem; j++){
            if(secondaryTriangle(i,j, nrElem) != 0){
                if(minVal > mat[i][j])
                    minVal = mat[i][j];
            }
        }
    }
    return minVal;
}

int countMinValApp(int **mat, int nrElem, int minVal){
    int i,j, app = 0;
    for(i = 0; i < nrElem; i++) {
        for (j = 0; j < nrElem; j++) {
            if(secondaryTriangle(i,j, nrElem) != 0){
                if (minVal == mat[i][j])
                    app++;
            }
        }
    }
    return app;
}

void minValuePositions(int **position, int **mat, int nrElem, int minVal){
    int i,j, elem = 0;
    for(i = 0; i < nrElem; i++){
        for(j = 0; j < nrElem; j++){
            if(mat[i][j] == minVal){
                position[elem][0] = i;
                position[elem][1] = j;
                elem++;
            }
        }
    }
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void sortArray (int *arr, int nrElem){
    qsort(arr, nrElem, sizeof(int), cmpfunc);
}
void sortMatrixLines (int **mat, int nrElem){
    int i;
    for(i = 0; i < nrElem; i++){
        sortArray(mat[i], nrElem);
    }
}
void freeMatrix(int **mat, int nrElem){
    int i,j;
    for(i = 0; i < nrElem; i++){
        free(mat[i]);
    }
    free(mat);
}

int main() {
    int **matrix, nrElem;
    int i,j, minValue, minElemNrApp = 0;
    int funcResult;
    int **posMatrix;

    printf("scrieti la tastatura nr de elem al matricei\n");
    scanf("%d", &nrElem);
    printf("nr de elem al matricei este = %d \n", nrElem);

    funcResult = allocateMatrix(&matrix, nrElem);
    if (funcResult < 0){
        printf("matricea nu s-a alocat\n");
        return -1;
    } else printf("matricea s-a alocat cu succes\n");

    readMatrix(&matrix, nrElem);

    //am citit elementele matricei
    getMatrix(matrix, nrElem);

    //caut elementul minim din triunghi de sub diag secundara : i + j > n - 1
    minValue = getMinElement(matrix, nrElem);
    printf("valoare minima este %d\n", minValue);

    //determin nr de aparitii al val minime
    minElemNrApp = countMinValApp(matrix, nrElem, minValue);
    printf("valoarea minima apare in matrice de %d ori\n", minElemNrApp);

    //creez matricea alocata dinamica pt pozitii
    funcResult = createPositionMatrix(&posMatrix, minElemNrApp);
    if(funcResult < 0){
        printf("nu s-a creat matricea de pozitii\n");
        return -1;
    }
    //determin pozitiile pe care se afla elem egale cu val minima
    minValuePositions(posMatrix, matrix, nrElem, minValue);
    getPositionMatrix(posMatrix, minElemNrApp);

    //sortez matricea citita de la tastatura
    printf("matricea sortata este \n");
    sortMatrixLines(matrix, nrElem);
    getMatrix(matrix, nrElem);

    //eliberez spatiul alocat pt cele 2 matrice
    freeMatrix(matrix, nrElem);
    //eliberez matricea cu indicii elementelor minime de sub diag sec.
    freePositionMatrix(posMatrix, minElemNrApp);

    return 0;
}


