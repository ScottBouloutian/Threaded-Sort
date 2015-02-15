/*
    Scott Bouloutian
    2/14/15
    Project 2
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Struct used to pass parameters
typedef struct {
    int *list;
    int size;
    int pivot;
} parameters;

void *sortThread(void *);
void merge_sort(int *, int);
void merge(int *, int, int);
void printList(int *, int);
void *mergeThread(void *);

int main() {
    // The list to be sorted
    int list[10] = {7,12,19,3,18,4,2,6,15,8};
    int n = sizeof(list)/sizeof(list[0]);
    int pivot = n/2;
    pthread_t tids[3];
    printf("Beginning to sort the list...\n");

    // Spawn a thread to sort the first half of the list
    int *firstHalf = list;
    parameters *data1 = (parameters *) malloc(sizeof(parameters));
    data1 -> list = firstHalf;
    data1 -> size = pivot;
    pthread_create(&tids[0], NULL, *sortThread, data1);

    // Spawn a thread to sort the second half of the list
    int *secondHalf = list + n/2;
    parameters *data2 = (parameters *) malloc(sizeof(parameters));
    data2 -> list = secondHalf;
    data2 -> size = n - pivot;
    pthread_create(&tids[1], NULL, *sortThread, data2);

    // Wait until both halves of the list are sorted
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);

    // Spawn a thread to merge the two sorted lists
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data -> list = list;
    data -> size = n;
    data -> pivot = pivot;
    pthread_create(&tids[2], NULL, *mergeThread, data);

    // Wait for the two sorted lists to be merged
    pthread_join(tids[2], NULL);

    // Print the sorted list
    printList(list, n);

    printf("...the list had finished sorting!\n");
    return 0;
}

// The method used by a thread to sort a list
void *sortThread(void *data){
    parameters *params = (parameters *) data;
    merge_sort(params -> list, params -> size);
    return NULL;
}

// The method used by a thread to merge a list
void *mergeThread(void *data) {
    parameters *params = (parameters *) data;
    merge(params -> list, params -> size, params -> pivot);
    return NULL;
}

// Performs a merge sort on a list of a given size
void merge_sort(int *list, int size) {
    if(size<2) {
        return;
    }
    int pivot = size/2;
    merge_sort(list, pivot);
    merge_sort(list + pivot, size-pivot);
    merge(list, size, pivot);
}

// Merges two sublists stored in an array of a given size separated by a given pivot
void merge (int *list, int size, int pivot) {
    int i,left,right;
    int *sorted = malloc(size * sizeof(list[0]));
    for (left = 0, right = pivot, i = 0; i < size; i++) {
        sorted[i] = right == size            ? list[left++]
                  : left == pivot            ? list[right++]
                  : list[right] < list[left] ? list[right++]
                  :                            list[left++];
    }
    for (i = 0; i < size; i++) {
        list[i] = sorted[i];
    }
    free(sorted);
}

// Prints a given list
void printList(int *list, int size) {
    int i;
    for(i=0;i<size;i++){
        printf("%d\n",list[i]);
    }
}
