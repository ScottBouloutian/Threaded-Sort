#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *sort(void *);
void merge_sort(int *, int);
void merge(int *, int, int);
void printList(int *, int);

int main() {
    int list[6] = {3,2,1,4,5,6};
    int n = sizeof(list)/sizeof(list[0]);
    int *firstHalf = list;
    int *secondHalf = list + n/2;
    pthread_t tid;
    printf("Before Thread\n");
    pthread_create(&tid, NULL, *sort, (void *)firstHalf);
    pthread_join(tid, NULL);
    printf("After Thread\n");
    return 0;
}

void *sort(void *list){
    printf("sorting the sublist\n");
    merge_sort(list, 3);
    printList(list,3);
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
    int *sorted = malloc(size * sizeof (int));
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
