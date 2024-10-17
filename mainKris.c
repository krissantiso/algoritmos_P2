#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

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

//no me sortea el primer elemento wtf
void insertionSort( int v[], int n ) {
    int x, i, j;
    for ( i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j > 0 && v[j] > x) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void quicksortAuxiliary(int v[], int left, int right ) {

}

void quicksort( int v[], int n ) {
    quicksortAuxiliary(v, 0, n - 1);
}

int checkSorted ( int v[], int n) {
    for (int i = 1; i < n; i++) {
        if ( v[i-1] > v[i] ) {
            return 0; //0 means not sorted
        }
    }
    return 1; //1 means sorted
}

void printArray(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
}

int checkInicialization (int inicialization[], int n, char alg ) {
    int sorted;
    printArray(inicialization, n);
    sorted = checkSorted(inicialization, n);
    printf("Sorted? %d\n", sorted);
    if ( sorted == 0 ) {
        printf("Sorting...\n");
        if ( alg == 'i' ) {
            insertionSort(inicialization, n);
        } else {
            quicksort(inicialization, n);
        }

        printArray(inicialization, n);
        sorted = checkSorted(inicialization, n);
        printf("Sorted? %d\n", sorted);
        if ( sorted == 0 ) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int checkAlgorithms () {
    int nR = 20;

    int descendingInicializationI[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int descendingInicializationQ[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    int randomInicializationI[nR];
    int randomInicializationQ[nR];

    for (int i = 0; i < nR; i++) {
        int x = rand() % 10;
        randomInicializationI[i] = x;
        randomInicializationQ[i] = x;
    }

    int ok = 0;

    printf("Insertion sort with random inicialization\n");
    if ( checkInicialization(randomInicializationI, 10, 'i') == 1) {
        ok = 1;
    }
    printf("Insertion sort with descending inicialization\n");
    if ( checkInicialization(descendingInicializationI, 10, 'i') == 1) {
        ok = 1;
    }
    printf("Quicksort with random inicialization\n");
    if ( checkInicialization(randomInicializationQ, nR, 'q') == 1) {
        ok = 1;
    }
    printf("Quicksort with descending inicialization\n");
    if ( checkInicialization(descendingInicializationQ, nR, 'q') == 1) {
        ok = 1;
    }

    if ( ok == 1) {
        printf("\nInsertion sort and quicksort do not work\n");
        return 1;
    }
    printf("\nInsertion sort and quicksort do work\n");
    return 0;
}
/*
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
}*/

int main () {
    checkAlgorithms();
}