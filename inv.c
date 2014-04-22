#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

void initMat(double **matrix, int n, int m);
void rowSwap(double **A, int swap, int with, int n, int m);
void setMatrix(double **A, int n,  int m);
void onesPivot(double **A, int row, int col, int m);
void multAdd(double **A, int row, int row2, int col, int m);;
void inv(double **A, int n, int m);

int main(int argc, char *argv[]){
    if(argc !=3 && atoi(argv[1]) != atoi(argv[2])){
	printf("Usage: ./inv rows cols //square matrix only\n");
	return 0;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int i, j, col, row;
    double **matrix = (double **) malloc (sizeof(double) * n);
    double *data = (double *) malloc (sizeof(double) * n * 2 * m);

    printf("\n\nn rows: %d \n",n);
    printf("m cols: %d \n\n",m);
    for(i=0;i<n;i++)
    {
	*(matrix+i) = data + 2*m*i;
    }

    /*init the matrix*/
    initMat(matrix, n, m);
    /*larger values of potential pivot on top*/ 
    /*inv(matrix, n, m);not needed, put the init into the regular init*/
    setMatrix(matrix, n, m);
    col = 0;
    row = 0;
    printf("Steps taken:\n");
    printf("1. Sort by column one, largest to row 0, smallest to row n\n");
    printf("2. Check non zero pivot candidate, then normalize row\n");
    printf("3. Annihilate rows below pivot through row n\n");
    printf("4. If not top row, annihilate rows above current pivot row through row 0 to achieve RREF\n");
    printf("5. Print augmented reduced matrix which is inv(A)\n\n");

    for(row=0;row<n;row++){
	while(*(*(matrix+row)+col) == 0 ){
	    col++;
	}
	onesPivot(matrix, row, col, m);
	for(j = row+1;j<n;j++){
	    if(*(*(matrix + j)+col) !=0){
		multAdd(matrix, row, j, col, m);
	    }
	}
	if(row != 0){
	    for(j = row;j>0;j--){
		    multAdd(matrix, row, j-1, col, m);
	    }
	}
	col++;
    }


    printf("Inverse of this %dx%d matrix is\n\n", n, m);
    for(i=0; i<n;i++){
	for(j=m;j<2*m;j++){
	    printf("%.3f ",*(*(matrix+i)+j));
	}
	printf("\n");
    }
    printf("\n");
    printf("\n");
    return 0;
}

void rowSwap(double **A, int swap, int with, int n, int m){
    int i, j;
    double *temp = (double *) malloc (sizeof(double)*2*m);
    temp = *(A+swap);
    *(A+swap) = *(A+with);
    *(A+with) = temp;/*
			for(i=0; i<n;i++){
			for(j=0;j<m;j++){
			printf("%f ",*(*(A+i)+j));
			}
			printf("\n");
			}
			printf("\n");
			*/
}

void setMatrix(double **A, int n, int m){
    int i, j;
    for(i = 0;i<n-1;i++){
	for(j=i+1;j<n;j++){
	    if(*(*(A+i)) < *(*(A+j))){
		rowSwap(A, i, j, n, m);
	    }
	}
    }

}

void initMat(double **matrix, int n, int m){
    int i, j, k;
    printf("Initial Matrix via initMat\n(*(*(matrix+i)+j) = i*m+j+j*(i+5)%4+1)\nAugmented with Identity Matrix\n\n");
    for(i=0; i<n;i++){
	for(j=0;j<m;j++){
	    *(*(matrix+i)+j) = i*m+j+j*(i+5)%4+1;
	    printf("%.3f ",*(*(matrix+i)+j));
	}
	printf(" | ");
	for(k=0;k<m;k++){
	    if(k == i){	
		*(*(matrix+i)+m+k) = 1;
	    }
	    else{
		*(*(matrix+i)+m+k) = 0;
	    }
	    printf("%.3f ",*(*(matrix+i)+k+m));
	}
	printf("\n");
    }
    printf("\n");
}

void onesPivot(double **A, int row, int col, int m){
    int i, j;	
    double pivot = *(*(A+row)+col); 
    for(i=col;i<2*m;i++){
	*(*(A+row)+i) = (double)(*(*(A+row)+i) / pivot);/*this will divide all by the pivot*/
    }/*
     for(i=0; i<m;i++){
       for(j=0;j<2*m;j++){
       printf("%f ",*(*(A+i)+j));
       }
       printf("\n");
       }
       printf("\n");*/
}

void multAdd(double **A, int row, int row2, int col,  int m){
    int i, j;
    double eliminate = *(*(A+row2)+col);
    for(i=col;i<2*m;i++){
	*(*(A+row2)+i) = (*(*(A+row)+i)*eliminate*-1) + *(*(A+row2)+i);
    }
   /*  for(i=0; i<m;i++){
       for(j=0;j<2*m;j++){
       printf("%f ",*(*(A+i)+j));
       }
       printf("\n");
       }
       printf("\n");*/
}

void inv(double **A, int n, int m){
    /*make this add identity to guassian initMat*/
    int i, j, k;
    printf("Initial Matrix via initMat\n(*(*(matrix+i)+j) = i*m+j+j*(i+5)%4+1)\nAugmented with Identity Matrix\n\n");
    for(i=0; i<n;i++){
	for(j=0;j<m;j++){
	    printf("%.3f ",*(*(A+i)+j));
	}
	printf(" | ");
	for(k=0;k<m;k++){
	    if(k == i){	
		*(*(A+i)+m+k) = 1;
	    }
	    else{
		*(*(A+i)+m+k) = 0;
	    }
	    printf("%.3f ",*(*(A+i)+k+m));
	}
	printf("\n");
    }
    printf("\n");

}
