#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

//DEFINES

//Check if the algorithms work y/n
#define checkAlg 'y'
//How many terms do we check
#define termsChecked 15
//What algorithm is calculated 0(all)/1/2/3
#define algCalculated 0
//In case only 1 algorithm is calculated for what value
#define algValue 2
//How many iterations the code does in case the time is less than 500
#define iterations 100000

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void InsertionSort ( int v[], int n ) {
    int i, x, j;
    for (i = 2; i < n; i++) {
        x = v[i];
        j = i-1;
        while (j > 0 && v[j] > x) {
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = x;
    }
}

void swap (int v[], int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void QuickSortAux ( int v[], int left, int right ) {
    int x, i, j, pivot;
    if ( left < right ) {
        x = rand() % (right - left + 1) + left; //es como ponia en la pagina web
        pivot = v[x];
        swap (left, v, x);   //we need to implement it
        i = left + 1;
        j = right;
        while (i <= j) {
            while (i <= right && v[i] < pivot ) {
                i = i+1;
            }
            while (v[j] > pivot) {
                j = j - 1;
            }
            if (i <= j) {
                swap (v, i, j);
                i = i+1;
                j = j+1;
            }
        }
        swap(v[left], v[j]);
        QuickSortAux(&v[left], left, j-1);
        QuickSortAux(&v[j+1], j+1, right);
    }
}

void QuickSort ( int v[], int n ) {
    QuickSortAux(v, v[0], n);
}


int checkAlgorithms() {
    int ok = 0;
    int i;
    printf("Insert Sort\t\tQuickSort");
    int randomArr[20];
    int descArr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    printf("Descending array: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", descArr[i]);
    }
    printf("\nRandom array: ");
    for (i = 0; i < 20; i++) {
        randomArr[i] = rand() % (20 + 20 + 1) - 20;
        printf("%d ", randomArr[i]);
    }
    printf("Insertion Sort:\n")
    for (i = 0 ; i < 10; i++)

        if ( ok == 1) {
            printf("\nAlgorithms do not work\n");
            return 1;
        }
    printf("\nAlgorithms work\n");
    return 0;
}

double iterateAlgorithms(int fAlgCalculated, int fAlgValue, int fIterations) {

    printf("\nNumber obtained by iterating %d times\n", fIterations);

    double t1, t2;

    if (fAlgCalculated == 1) {
        t1 = microsegundos();
        for (int i = 1; i <= fIterations; i++) {
            fib1(fAlgValue);
        }
        t2 = microsegundos();
    } else if (fAlgCalculated == 2) {
        t1 = microsegundos();
        for (int i = 1; i <= fIterations; i++) {
            fib2(fAlgValue);
        }
        t2 = microsegundos();
    } else {
        t1 = microsegundos();
        for (int i = 1; i <= fIterations; i++) {
            fib3(fAlgValue);
        }
        t2 = microsegundos();
    }

    return (t2 - t1) / fIterations;
}

void printResults1(double t, int fAlgValue) {
    double x, y, z;

    x = t / pow(1.1, fAlgValue);
    y = t / pow( ( ( 1 + sqrt(5) ) / 2 ), fAlgValue );
    z = t / pow( 2, fAlgValue );

    printf("Fibonacci value\t\tTime\tUnderest.\tTight\t\tOverest.\n");

    printf("%12d%15.3f%15.6f%15.6f%15.6f\n", fAlgValue, t, x, y, z);
}

void printResults2(double t, int fAlgValue) {
    double x, y, z;

    x = t / pow( fAlgValue, 0.8 );
    y =	t / fAlgValue;
    z = t / ( fAlgValue * log( fAlgValue ) );

    printf("Fibonacci value\t\tTime\tUnderest.\tTight\t\tOverest.\n");

    printf("%12d%15.3f%15.6f%15.6f%15.6f\n", fAlgValue, t, x, y, z);
}

void printResults3(double t, int fAlgValue) {

    double x, y, z;

    x = t / sqrt(log(fAlgValue));
    y = t / log(fAlgValue);
    z = t / pow(fAlgValue, 0.5);

    printf("Fibonacci value\t\tTime\tUnderest.\tTight\t\tOverest.\n");

    printf("%12d%15.3f%15.6f%15.6f%15.6f\n", fAlgValue, t, x, y, z);
}

int main(void) {

    if (checkAlg == 'y') {
        checkAlgorithms();
    }

    double t1, t2, t;

    if (algCalculated == 0) {
        printf("\nAlgorithm 1\n");
        for (int n = 2; n <= 32; n = n*2 ) {
            t1 = microsegundos();
            fib1(n);
            t2 = microsegundos();
            t = t2-t1;
            if (t < 500) {
                t = iterateAlgorithms(1, n, iterations);
            }

            printResults1(t, n);
        }
        printf("\nAlgorithm 2\n");
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
        printf("\nAlgorithm 3\n");
        for (int n = 1000; n <= 10000000; n = n*10 ) {
            t1 = microsegundos();
            fib3(n);
            t2 = microsegundos();
            t = t2-t1;
            if (t < 500) {
                t = iterateAlgorithms(3, n, iterations);
            }

            printResults3(t, n);
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
        } else if (algCalculated == 3) {
            t1 = microsegundos();
            fib3(algValue);
            t2 = microsegundos();
            t = t2-t1;

            if (t < 500) {
                t = iterateAlgorithms(2, algValue, iterations);
            }
            printf("\nTable 3\n");
            printResults3(t, algValue);
        }

    }

    return 0;
}
