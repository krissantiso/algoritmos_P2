// Created by antia on 18/10/2024.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define checkAlg 'y'
#define algCalculated 0
#define length 10
#define iterations 1000

/* //time functions:
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
 */

void init_seed() {
    srand(time(NULL));
}

void ascending_init (int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}

void random_init (int v[],int n){
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void swap (int a,int b, int v[]){
    int aux;
    aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void InsertionSort (int v[],int n){
    int x,j;
    for (int i=1;i<n;i++){
        x=v[i];
        j=i-1;
        while((j>=0)&&(v[j]>x)){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = x;
    }
}

void QuickSortAux (int v[],int left,int right){
    if (left<right){
        int x=rand() % (right - left + 1) + left;
        int pivot= v[x];
        swap (left,x,v);
        int i = left+1;
        int j = right;
        while (i<=j) {
            while ((i<=right)&&(v[i]<pivot)) {i++;}
            while (v[j]>pivot) {j--;}
            if (i<=j){
                swap (i,j,v);
                i++;
                j--;
            }
        }
        swap(left,j,v);
        QuickSortAux(v,left,j-1);
        QuickSortAux(v,j+1,right);
    }
}

void QuickSort(int v[],int n){
    QuickSortAux(v,0,n-1);
}

void QuickSortTest (int v[],int n){
    QuickSort(v,n);
    printf("\nQuick sort:\n");
    for (int i=0;i<n;i++) printf("%d ",v[i]);
    printf("\n");
}

void InsertionSortTest (int v[],int n){
    InsertionSort(v,n);
    printf("\nInsertion sort:\n");
    for (int i=0;i<n;i++) printf("%d ",v[i]);
}

void test(int v[],int n){
    int v1[n],v2[n];
    printf("Array:\n");
    for (int i=0;i<n;i++) {
        v1[i]=v[i];
        v2[i]=v[i];
        printf("%d ",v[i]);
    }
    InsertionSortTest(v1,n);
    QuickSortTest(v2,n);
}

int main(){
    init_seed();
    int v[length]={10,9,8,7,6,5,4,3,2,1};
    int r[length];
    int a[length];
    ascending_init(a,length); random_init(r,length);
    test(v,length); test(r,length); test(a,length);
}

/*
void printResultsInsertion(double t, int fAlgValue) {
    double x, y, z;
    //x = t / sqrt(log(fAlgValue));
    //y = t / log(fAlgValue);
    //z = t / pow(fAlgValue, 0.5);
    printf("Array\t\tTime\tUnderest.\tTight\t\tOverest.\n");
    printf("%12d%15.3f%15.6f%15.6f%15.6f\n", fAlgValue, t, x, y, z);
}

int main() {
    if (checkAlg == 'y') {
        //checkAlgorithms();
    }
    double t1, t2, t;
    if (algCalculated == 0) {
        printf("\nInsertion Sort\n");
        for (int n = 2; n <= 32; n = n*2 ) {
            t1 = microsegundos();
            InsertionSort(v,n);
            t2 = microsegundos();
            t = t2-t1;
            if (t < 500) {
                t = iterateAlgorithms(1, n, iterations);
            }
            printResultsInsertion(t, n);
        }
        printf("\nInsertion Sort\n");
        for (int n = 1000; n <= 10000000; n = n*10 ) {
            t1 = microsegundos();
            fib2(n);
            t2 = microsegundos();
            t = t2-t1;
            if (t < 500) {
                t = iterateAlgorithms(2, n, iterations);
            }

            printResults2(t, n);
        }

    } else {

        if (algCalculated == 1) {
            t1 = microsegundos();
            fib1(algValue);
            t2 = microsegundos();

            t = t2-t1;

            if (t < 500) {
                t = iterateAlgorithms(1, algValue, iterations);
            }
            printf("\nTable 1\n");
            printResults1(t, algValue);
        } else if (algCalculated == 2) {
            t1 = microsegundos();
            fib2(algValue);
            t2 = microsegundos();
            t = t2-t1;

            if (t < 500) {
                t = iterateAlgorithms(2, algValue, iterations);
            }
            printf("\nTable 2\n");
            printResults2(t, algValue);
        }

    }
    return 0;
}
 */
