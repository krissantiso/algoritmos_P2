#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>

//test teh algorithms: y/n
#define checkAlg 'y'
#define length 10
#define iterations 10000

//time functions:
double microsegundos () {
    struct timeval t;
    if (gettimeofday (&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void init_seed () {
    srand(time(NULL));
}

void ascending_init (int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descending_init (int v[], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = n-i;
}

void random_init (int v[], int n) {
    init_seed();
    int i, m = 2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void printArray (int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
}

void swap (int a, int b, int v[]){
    int aux;
    aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void InsertionSort (int v[], int n){
    int x, j;
    for (int i = 1; i < n; i++){
        x = v[i];
        j = i-1;
        while (j >= 0 && v[j] > x){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = x;
    }
}

void QuickSortAux (int v[], int left, int right) {
    if (left < right){
        int x = rand() % (right - left + 1) + left;
        int pivot= v[x];
        swap(left, x, v);
        int i = left+1;
        int j = right;
        while (i <= j) {
            while (i <= right && v[i] < pivot) {
                i++;
            }
            while (v[j] > pivot) {
                j--;
            }
            if (i <= j){
                swap(i, j, v);
                i++;
                j--;
            }
        }
        swap(left, j, v);
        QuickSortAux(v, left, j-1);
        QuickSortAux(v, j+1, right);
    }
}

void QuickSort (int v[], int n) {
    QuickSortAux(v,0,n-1);
}

int checkSorted (int v[], int n) {
    for (int i = 1; i < n; i++) {
        if ( v[i-1] > v[i] ) {
            return 0; //0 means not sorted
        }
    }
    return 1; //1 means sorted
}

int checkInitialization (int initialization[], int n) {
    int sorted;
    int v1[length],v2[length];
    printArray(initialization, n);
    sorted = checkSorted(initialization, n);
    printf("\nSorted? %d\n", sorted);
    if ( sorted == 0 ) {
        for (int i=0;i<n;i++) {
            v1[i]=initialization[i];
            v2[i]=initialization[i];
        }
        printf("Insertion Sort:\nSorting...\n");
        InsertionSort(v1, n);
        printArray(v1, n);
        sorted = checkSorted(v1, n);
        printf("\nSorted? %d\n", sorted);
        if ( sorted == 0 ) {
            return 0;
        }
        printf("Quick Sort:\nSorting...\n");
        QuickSort(v2, n);
        printArray(v2, n);
        sorted = checkSorted(v2, n);
        printf("\nSorted? %d\n", sorted);
        if ( sorted == 0 ) {
            return 0;
        }
        return 1;
    }
    return 1;
}

void test (int a[], int b[], int c[], int n) {
    ascending_init(a,length);
    descending_init(b,length);
    random_init(c,length);
    printf("Ascending array:\n");
    checkInitialization(a,length);
    printf("Descending array:\n");
    checkInitialization(b,length);
    printf("Random array:\n");
    checkInitialization(c,length);
}

void printAlgorithms (double t, int n, int alg, int init,int iterated) {
    double x, y, z;
    if ( alg == 0 ) { //Quicksort
            if ( init == 0 ) { //descending
                x = t / log(n); y = t / n; z = t / pow(n, 1.5);
            }
            if ( init == 1 ) { //ascending
                x = t / pow(n, 0.5); y = t / pow(n, 1.1); z = t / pow(n, 2);
            }
            if ( init == 2 ) { //random
                x = t / n; y = t / (n * log(n)); z = t / pow(n, 2.0);
            }
    }
    if ( alg == 1 ) { //InsertionSort
            if ( init == 0 ) { //descending
                x = t / pow(n, 1.8); y = t / pow(n, 2); z = t / pow(n, 2.2);
            }
            if ( init == 1 ) { //ascending
                x = t / pow(n, 0.5); y = t / n; z = t / pow(n, 2);
            }
            if ( init == 2 ) { //random
                x = t / (n * log(n)); y = t / pow(n, 2); z = t / pow(n, 3);
            }
    }
    if (iterated == 1) {
        printf("%12d %20.3fms* %20.12f %20.12f %20.12f\n", n, t, x, y, z);
    } else {
        printf("%12d %20.3fms  %20.12f %20.12f %20.12f\n", n, t, x, y, z);
    }
}

double iterateAlgorithms (int alg, int v[], int n, double fIterations) {
    double t1 = 0, t2 = 0;
    int i;
    if (alg == 0) {
        t1 = microsegundos();
        for ( i = 0; i < fIterations; i++) {
            QuickSort(v, n);
        }
        t2 = microsegundos();
    }
    if (alg == 1) {
        t1 = microsegundos();
        for ( i = 0; i < fIterations; i++) {
            InsertionSort(v, n);
        }
        t2 = microsegundos();
    }
    return (t2 - t1) / fIterations;
}

void runQuickSort (int v[], int n, int initialization) {
    double t = 0, t1 = 0, t2 = 0, iterated = 0;
    t1 = microsegundos();
    QuickSort(v, n);
    t2 = microsegundos();
    t = t2-t1;
    if (t < 500) {
        t = iterateAlgorithms(0, v, n, iterations);
        iterated = 1;
    }
    printAlgorithms (t, n, 0, initialization, iterated);
}

void runInsertionSort (int v[], int n, int initialization) {
    double t = 0, t1 = 0, t2 = 0, iterated = 0;
    t1 = microsegundos();
    InsertionSort(v, n);
    t2 = microsegundos();
    t = t2-t1;
    if (t < 500) {
        t = iterateAlgorithms(1, v, n, iterations);
        iterated = 1;
    }
    printAlgorithms (t, n, 1, initialization, iterated);
}

void runAlgorithms () {
    printf("Quick Sort with descending initialization\n");
    printf("\tn\t\t\tTime\t    Underest.\t\tTight\t\t\tOverest.\n");
    for (int n = 500; n <= 32000; n = n*2) {
        int v[n]; descending_init(v, n);
        runQuickSort(v, n, 0);
    }
    printf("Quick Sort with ascending initialization\n");
    printf("\tn\t\t\tTime\t    Underest.\t\tTight\t\t\tOverest.\n");
    for (int n = 500; n <= 32000; n = n*2) {
        int v[n]; ascending_init(v, n);
        runQuickSort(v, n, 1);
    }
    printf("Quick Sort with unsorted initialization\n");
    printf("\tn\t\t\tTime\t    Underest.\t\tTight\t\t\tOverest.\n");
    for (int n = 500; n <= 32000; n = n*2) {
        int v[n]; random_init(v, n);
        runQuickSort(v, n, 2);
    }
    printf("Insertion Sort with descending initialization\n");
    printf("\tn\t\t\tTime\t    Underest.\t\tTight\t\t\tOverest.\n");
    for (int n = 500; n <= 32000; n = n*2) {
        int v[n]; descending_init(v, n);
        runInsertionSort(v, n, 0);
    }
    printf("Insertion Sort with ascending initialization\n");
    printf("\tn\t\t\tTime\t    Underest.\t\tTight\n\t\tOverest.\n");
    for (int n = 500; n <= 32000; n = n*2) {
        int v[n]; ascending_init(v, n);
        runInsertionSort(v, n, 1);
    }
    printf("Insertion Sort with unsorted initialization\n");
    printf("\tn\t\t\tTime\t    Underest.\t\tTight\t\t\tOverest.\n");
    for (int n = 500; n <= 32000; n = n*2) {
        int v[n]; random_init(v, n);
        runInsertionSort(v, n, 2);
    }
}

int main () {
    if ( checkAlg == 'y' ) {
        int a[length],b[length],c[length];
        test(a,b,c,length);
    }
    runAlgorithms();
}