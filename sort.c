#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

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
    int list[7] = {96,75,46,1,1009,75,74};
    int n = sizeof(list)/sizeof(list[0]);
    int pivot = n/2;
    int *firstHalf = list;
    int *secondHalf = list + n/2;
    pthread_t tids[3];
    printf("Before Thread\n");
    parameters *data1 = (parameters *) malloc(sizeof(parameters));
    data1 -> list = firstHalf;
    data1 -> size = pivot;
    pthread_create(&tids[0], NULL, *sortThread, data1);
    parameters *data2 = (parameters *) malloc(sizeof(parameters));
    data2 -> list = secondHalf;
    data2 -> size = n - pivot;
    pthread_create(&tids[1], NULL, *sortThread, data2);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data -> list = list;
    data -> size = n;
    data -> pivot = pivot;
    pthread_create(&tids[2], NULL, *mergeThread, data);
    pthread_join(tids[2], NULL);
    printList(list, n);
    printf("After Thread\n");
    return 0;
}

void *sortThread(void *data){
    parameters *params = (parameters *) data;
    merge_sort(params -> list, params -> size);
    return NULL;
}

void *mergeThread(void *data) {
    parameters *params = (parameters *) data;
    merge(params -> list, params -> size, params -> pivot);
    return NULL;
}

void merge_sort(int *list, int size) {
    if(size<2) {
        return;
    }
    int pivot = size/2;
    merge_sort(list + pivot, size-pivot);
    merge(list, size, pivot);
}

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

void printList(int *list, int size) {
    int i;
    for(i=0;i<size;i++){
        printf("%d\n",list[i]);
    }
}
