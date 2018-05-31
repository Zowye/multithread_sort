/* Contador de palavras
 *
 * Este programa recebe como entrada um vetor de numeros desordenados
 * e realiza a ordenacao do mesmo utilizando o algoritmo mergeSort
 * com duas threads. 
 * Algoritmo mergeSort: https://www.geeksforgeeks.org/merge-sort/
 * Author: Caio Zowye Camacho Cabral
 * Date: may 25, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>

#define N_THREADS 2
/* C program for Merge Sort */
 

typedef struct {
  int *arr;
  int l;
  int r;  
} argumentos;


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
     /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

/* mergeSort - recursive function */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

/* funcao que a thread invoca */
void *thread_foo(void * arg){
  argumentos *parametros = (argumentos*)arg;
  int *arr =  parametros->arr;
  int l =   parametros->l;
  int r =   parametros->r;

  mergeSort(arr, l, r);

}

/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++){
      if(i == size-1) printf("%d", A[i]);
    else printf("%d ", A[i]);
    }
    printf("\n");
}
 
/* Driver program to test above functions */
int main(){
  int m;
  int L, R;
  pthread_t workers[2];
  int thread_id[2];
  int i = 0, j = 0, n = 0;
  char str[2000000], *s = str, *t = NULL;
  int num_threads;
  int arr[200000];
  int arr_size;

  fgets(s, 2000000000, stdin);

  // Remove '\n' do final da string
  while(str[i] != '\n') i++;
  str[i] = '\0';

  // Tokeniza e insere no vetor de unsigned long int - vet[]
  while ((t = strtok(s, " ")) != NULL) {
    s = NULL;
    arr[n++] = atoi(t);
  }

  arr_size = n; //VSIZE <- #elementos a verificar

  argumentos ARG_A;
  ARG_A.arr = arr;
  ARG_A.l = 0;
  ARG_A.r = arr_size/2 -1;

  argumentos ARG_B;
  ARG_B.arr = arr;
  ARG_B.l = arr_size/2;
  ARG_B.r = arr_size - 1;


  

  pthread_create(&(workers[0]), NULL, thread_foo, (void*) &ARG_A );
  pthread_create(&(workers[1]), NULL, thread_foo, (void*) &ARG_B );

  pthread_join(workers[0], NULL);
  pthread_join(workers[1], NULL);



  L = 0;
  R = arr_size - 1;
  m = arr_size/2 -1;

  merge(arr, L, m, R);

  printArray(arr, arr_size);

  return 0;
}